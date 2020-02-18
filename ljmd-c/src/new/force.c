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
    double c12, c6;

    /* zero energy and forces */
    double epot=0.0;

    // define temporary variables for avoiding using power and sqrt in cycle
    c12 = 4.0 * sys->epsilon*pow(sys->sigma, 12.0);
    c6 = 4.0 * sys->epsilon*pow(sys->sigma, 6.0);
    rcsq = sys->rcut * sys->rcut;

#if defined (_OPENMP)
#pragma omp parallel reduction(+:epot)
#endif
    {
       double rx,ry,rz;
       double *fx,*fy,*fz;
       double rsq,ffac;
       double epot_priv=0.0;
       int i;
#if defined (_OPENMP)
       int tid=omp_get_thread_num();
#else
       int tid=0;
#endif
       fx=sys->fx + (tid*sys->natoms); azzero(fx,sys->natoms);
       fy=sys->fy + (tid*sys->natoms); azzero(fy,sys->natoms);
       fz=sys->fz + (tid*sys->natoms); azzero(fz,sys->natoms);
       //for(i=0; i < (sys->natoms) -1 ; i+=sys->nthreads) {
       //    int ii = i + tid;
       //    if (ii >= (sys->natoms -1)) break;
       for(i=tid; i < (sys->natoms) -1 ; i+=sys->nthreads) {
           for(int j= i+1 ; j < (sys->natoms); ++j) {
               
               /* get distance between particle i and j */
               rx=pbc(sys->rx[i] - sys->rx[j], 0.5*sys->box);
               ry=pbc(sys->ry[i] - sys->ry[j], 0.5*sys->box);
               rz=pbc(sys->rz[i] - sys->rz[j], 0.5*sys->box);
               rsq = rx*rx + ry*ry + rz*rz;
         
               /* compute force and energy if within cutoff */
               if (rsq < rcsq) {
                   double r6, rinv;
                   rinv= 1.0/rsq;
                   r6 = rinv * rinv * rinv;
      
                   ffac = (12.0 * c12 * r6 -6.0*c6) * r6 *rinv;
                   epot_priv += r6 *(c12*r6 -c6);
      
                   fx[i] += rx*ffac;
                   fy[i] += ry*ffac;
                   fz[i] += rz*ffac;
                   fx[j] -= rx*ffac;
           	   fy[j] -= ry*ffac;
           	   fz[j] -= rz*ffac;
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
           sys->fx[j] += sys->fx[offs+j];
           sys->fy[j] += sys->fy[offs+j];
           sys->fz[j] += sys->fz[offs+j];
         }
       }
    } // end of parallel region
    sys->epot  =epot;
}
