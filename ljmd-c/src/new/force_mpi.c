#include <math.h> //pow,sqrt
#include <stdlib.h> //malloc
#if defined (_OPENMP)
#include <omp.h>
#endif
#include "data.h"
#include "prototypes.h"

/* helper function: apply minimum image convention */
static inline __attribute__((always_inline)) double pbc(double x, const double boxby2)
{
    while (x >  boxby2) x -= 2.0*boxby2;
    while (x < -boxby2) x += 2.0*boxby2;
    return x;
}

/* compute forces */
void force(mdsys_t *sys) 
{
    double rcsq;
    double c12,c6;
    double half_box;

    /* zero energy */
    double epot=0.0;


    // define temporary variables for avoiding using power and sqrt in cycle
    c12 = 4.0 * sys->epsilon*pow(sys->sigma, 12.0);
    c6 = 4.0 * sys->epsilon*pow(sys->sigma, 6.0);
    rcsq = sys->rcut * sys->rcut;
    half_box = 0.5*sys->box;


    // rank 0 broadcasts all updated positions to other ranks
    MPI_Bcast(sys->rx,sys->natoms,MPI_DOUBLE,0,sys->mpicomm);
    MPI_Bcast(sys->ry,sys->natoms,MPI_DOUBLE,0,sys->mpicomm);
    MPI_Bcast(sys->rz,sys->natoms,MPI_DOUBLE,0,sys->mpicomm);
    
    double * R;
    
    R=(double *)malloc(3 * sys->natoms*sizeof(double));
       
    for(int i=0; i<sys->natoms; ++i){
        int ii = 3 * i;
        R[ ii ] = sys->rx[i];
        R[ ii + 1 ] = sys->ry[i];
        R[ ii + 2 ] = sys->rz[i];   
    }
    
    double * C;  
    
    C = (double *)malloc(3*sys->nthreads*sys->natoms*sizeof(double));
    
#if defined (_OPENMP)
#pragma omp parallel reduction(+:epot)
#endif
    {
       double r[3];
       double *c;
       double rsq,ffac;
       double epot_priv=0.0;
       int i;
#if defined (_OPENMP)
       int tid=omp_get_thread_num();
#else
       int tid=0;
#endif
       
       c = C + (3 * tid * sys->natoms);
       azzero(c, 3 * sys->natoms);  
       
       /*assign address of thread-private-pointers and zero forces */
       
       azzero(sys->cx + (tid*sys->natoms), sys->natoms);
       azzero(sys->cy + (tid*sys->natoms), sys->natoms);
       azzero(sys->cz + (tid*sys->natoms), sys->natoms);
       
       for(i=sys->mpirank; i < sys->natoms -1 ; i+=sys->nprocs) {
       if(((i-sys->mpirank)/sys->nprocs)%sys->nthreads!=tid) continue;
        
        
         for(int j= i+1 ; j < (sys->natoms); ++j) {
             
             /* get distance between particle i and j */
             int ii = 3 * i;
             int jj = 3* j;
             
             /* get distance between particle i and j */
             r[0]=pbc( R[ ii ] - R[ jj ], half_box);
             r[1]=pbc(R[ ii + 1 ] - R[ jj + 1 ], half_box);
             r[2]=pbc(R[ ii + 2 ] - R[ jj + 2 ], half_box);
             rsq = r[0]*r[0] + r[1]*r[1] + r[2]*r[2];
               

            /* compute force and energy if within cutoff */
           if (rsq<rcsq) {
		       
		       double r6,rinv;
		       rinv=1.0/rsq;
               
               r6 = rinv * rinv * rinv;
                
               ffac = (12.0 * c12 * r6 -6.0*c6) * r6 *rinv;
               epot_priv += r6 *(c12*r6 -c6);
               
               
		//The c array contains, for every particle in the box, the sum of force contributions coming from particles in a given rank. We need to perform a reduction (MPI_Reduce) to sum the 
		//contributions coming from all ranks.
		        
      
               c[ ii ] += r[0]*ffac;
           	   c[ ii + 1 ] += r[1]*ffac;
           	   c[ ii + 2 ] += r[2]*ffac;
           	   c[ jj ] -= r[0]*ffac;
           	   c[ jj + 1 ] -= r[1]*ffac;
           	   c[ jj + 2 ] -= r[2]*ffac;
           	                    
	       }   
	     }   
       }  
       epot += epot_priv;  // omp reduction of epot
#if defined (_OPENMP)
#pragma omp barrier
#endif
       
       
       // define ranges for the various threads
       i = 1 + (sys->natoms / sys->nthreads);
       int fromidx = tid * i;
       int toidx = fromidx + i;
       if (toidx > sys->natoms) toidx = sys->natoms;
       
       // update force with array spread contributions
       for (i=0; i < sys->nthreads; ++i) {
         
         int offs = 3 * i * sys->natoms;
         
         for (int j=fromidx; j < toidx; ++j) {
           
           int jj = 3 * j;
                      
           sys->cx[j] += C[ offs + jj ];
           sys->cy[j] += C[ offs + jj + 1 ];
           sys->cz[j] += C[ offs + jj + 2 ];
           
         }
       }
    } // end of parallel region
    sys->epot  =epot;

    // (only first natoms elements will be reduced)
    MPI_Reduce(sys->cx,sys->fx,sys->natoms,MPI_DOUBLE,MPI_SUM,0,sys->mpicomm);
    MPI_Reduce(sys->cy,sys->fy,sys->natoms,MPI_DOUBLE,MPI_SUM,0,sys->mpicomm);
    MPI_Reduce(sys->cz,sys->fz,sys->natoms,MPI_DOUBLE,MPI_SUM,0,sys->mpicomm);
   
    MPI_Reduce(&epot,&sys->epot,1,MPI_DOUBLE,MPI_SUM,0,sys->mpicomm);
            
}
