#include <math.h> //pow,sqrt
#include <stdlib.h> //allocation
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

    /* zero energy and forces */
    double epot=0.0;

    // define temporary variables for avoiding using power and sqrt in cycle
    c12 = 4.0 * sys->epsilon*pow(sys->sigma, 12.0);
    c6 = 4.0 * sys->epsilon*pow(sys->sigma, 6.0);
    rcsq = sys->rcut * sys->rcut;
    half_box = 0.5*sys->box;
    
    double * R;
    
    R=(double *)malloc(3 * sys->natoms*sizeof(double));
       
    for(int i=0; i<sys->natoms; ++i){
        int ii = 3 * i;
        R[ ii ] = sys->rx[i];
        R[ ii + 1 ] = sys->ry[i];
        R[ ii + 2 ] = sys->rz[i];   
    }
    
    // adding
    
    double * F;  
    
    F=(double *)malloc(3*sys->nthreads*sys->natoms*sizeof(double));
    
    azzero(sys->fx,sys->natoms);
    azzero(sys->fy,sys->natoms);
    azzero(sys->fz,sys->natoms);
    
#if defined (_OPENMP)
#pragma omp parallel reduction(+:epot)
#endif
    {
       double r[3];
       double *f;
       double rsq,ffac;
       double epot_priv=0.0;
       int i;
#if defined (_OPENMP)
       int tid=omp_get_thread_num();
#else
       int tid=0;
#endif 
       int global_id = tid * sys->natoms;
       f = F + (3 * tid * sys->natoms);
       azzero(f, 3 * sys->natoms);  

       for(i=tid; i < (sys->natoms) -1 ; i+=sys->nthreads) {
           for(int j= i+1 ; j < (sys->natoms); ++j) {
               int ii = 3 * i;
               int jj = 3* j;
               /* get distance between particle i and j */
               r[0]=pbc( R[ ii ] - R[ jj ], half_box);
               r[1]=pbc(R[ ii + 1 ] - R[ jj + 1 ], half_box);
               r[2]=pbc(R[ ii + 2 ] - R[ jj + 2 ], half_box);
               rsq = r[0]*r[0] + r[1]*r[1] + r[2]*r[2];
         
               /* compute force and energy if within cutoff */
               if (rsq < rcsq) {
                   double r6, rinv;
                   rinv= 1.0/rsq;
                   r6 = rinv * rinv * rinv;
      
                   ffac = (12.0 * c12 * r6 -6.0*c6) * r6 *rinv;
                   epot_priv += r6 *(c12*r6 -c6);
      
                   f[ ii ] += r[0]*ffac;
           	       f[ ii + 1 ] += r[1]*ffac;
           	       f[ ii + 2 ] += r[2]*ffac;
           	       f[ jj ] -= r[0]*ffac;
           	       f[ jj + 1 ] -= r[1]*ffac;
           	       f[ jj + 2 ] -= r[2]*ffac;
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
       
       // NOTE: THIS IS A DIFFERENT i!!!!!!!!!!!!!!!
       for (i=0; i < sys->nthreads; ++i) {
         int offs =  3 * i* sys->natoms;
         
         for (int j=fromidx; j < toidx; ++j) {  
           int jj = 3 * j;
           sys->fx[j] +=  F[ offs + jj];
           sys->fy[j] +=  F[ offs + jj + 1];
           sys->fz[j] +=  F[ offs + jj + 2];
         
         }
       }
    } // end of parallel region
    
    sys->epot = epot;
}
