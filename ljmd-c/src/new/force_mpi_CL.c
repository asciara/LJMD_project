#include <math.h> //pow,sqrt
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

    /* zero energy */
    double epot=0.0;


    // define temporary variables for avoiding using power and sqrt in cycle
    c12 = 4.0 * sys->epsilon*pow(sys->sigma, 12.0);
    c6 = 4.0 * sys->epsilon*pow(sys->sigma, 6.0);
    rcsq = sys->rcut * sys->rcut;

    // rank 0 broadcasts all updated positions to other ranks
    MPI_Bcast(sys->rx,sys->natoms,MPI_DOUBLE,0,sys->mpicomm);
    MPI_Bcast(sys->ry,sys->natoms,MPI_DOUBLE,0,sys->mpicomm);
    MPI_Bcast(sys->rz,sys->natoms,MPI_DOUBLE,0,sys->mpicomm);

#if defined (_OPENMP)
#pragma omp parallel reduction(+:epot)
#endif
    {
       double rx,ry,rz;
       double *cx,*cy,*cz;
       double rsq,ffac;
       double epot_priv=0.0;
       int i;
#if defined (_OPENMP)
       int tid=omp_get_thread_num();
#else
       int tid=0;
#endif
       /*assign address of thread-private-pointers and zero forces */
       cx=sys->cx + (tid*sys->natoms); azzero(cx,sys->natoms); 
       cy=sys->cy + (tid*sys->natoms); azzero(cy,sys->natoms); 
       cz=sys->cz + (tid*sys->natoms); azzero(cz,sys->natoms); 

       for(i=sys->mpirank; i < sys->npairs ; i+=sys->nprocs) {
         if(((i-sys->mpirank)/sys->nprocs)%sys->nthreads!=tid) continue; // divide work among threads
         cell_t *c1, *c2;

	 c1= sys->clist + sys->plist[2*i];
	 c2= sys->clist + sys->plist[2*i+1];

	 for(int j= 0 ; j < c1->natoms; ++j) {
	    int ii=c1->idxlist[j];

	    double rx1=sys->rx[ii];
	    double ry1=sys->ry[ii];
	    double rz1=sys->rz[ii];
	    for (int k=0; k<c2->natoms;++k){
             int jj=c2->idxlist[k];  
            /* get distance between particle i and j */
            	rx=pbc(rx1 - sys->rx[jj], 0.5*sys->box);
            	ry=pbc(ry1 - sys->ry[jj], 0.5*sys->box);
            	rz=pbc(rz1 - sys->rz[jj], 0.5*sys->box);
            	rsq = rx*rx + ry*ry + rz*rz;
      
            /* compute force and energy if within cutoff */
            	if (rsq<rcsq) {
			double r6,rinv;
			rinv=1.0/rsq;
                	r6 = rinv * rinv * rinv;

                	ffac = (12.0 * c12 * r6 -6.0*c6) * r6 *rinv;
                	epot_priv += r6 *(c12*r6 -c6);
                

		//The c array contains, for every particle in the box, the sum of force contributions coming from particles in a given rank. We need to perform a reduction (MPI_Reduce) to sum the 
		//contributions coming from all ranks.
		
               		 cx[i] += rx*ffac;
               		 cy[i] += ry*ffac;
               		 cz[i] += rz*ffac;
               		 
	       		 cx[j] -= rx*ffac;
               		 cy[j] -= ry*ffac;
               		 cz[j] -= rz*ffac;
	    	}
	    }
	 }
       }
       epot += epot_priv;  // omp reduction of epot
#if defined (_OPENMP)
#pragma omp barrier
#endif
       i = 1 + (sys->natoms / sys->nthreads);
       int fromidx = tid * i;
       int toidx = fromidx + i;
       if (toidx > sys->natoms) toidx = sys->natoms;
       for (i=1; i < sys->nthreads; ++i) {
         int offs = i*sys->natoms;
         for (int j=fromidx; j < toidx; ++j) {
           sys->cx[j] += sys->cx[offs+j];
           sys->cy[j] += sys->cy[offs+j];
           sys->cz[j] += sys->cz[offs+j];
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
