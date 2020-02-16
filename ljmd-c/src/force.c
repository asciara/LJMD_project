#include <math.h> //pow,sqrt
#include "data.h"
#include "prototypes.h"

/* compute forces */
void force(mdsys_t *sys) 
{
    double r,ffac;
    double rx,ry,rz;
    int i,j;

    /* zero energy and forces */
    sys->epot=0.0;

    azzero(sys->fx,sys->natoms);
    azzero(sys->fy,sys->natoms);
    azzero(sys->fz,sys->natoms);

    azzero(sys->cx,sys->natoms);
    azzero(sys->cy,sys->natoms);
    azzero(sys->cz,sys->natoms);

    MPI_Broadcast(sys->rx,sys->natoms,MPI_DOUBLE,0,sys->mpicomm)
    for(i=sys->nsize*sys->mpirank; i < (sys->natoms); ++i) {
        for(j=0; j < (sys->natoms); ++j) {

            /* particles have no interactions with themselves */
            if (i==j) continue;
            
            /* get distance between particle i and j */
            rx=pbc(sys->rx[i] - sys->rx[j], 0.5*sys->box);
            ry=pbc(sys->ry[i] - sys->ry[j], 0.5*sys->box);
            rz=pbc(sys->rz[i] - sys->rz[j], 0.5*sys->box);
            r = sqrt(rx*rx + ry*ry + rz*rz);
      
            /* compute force and energy if within cutoff */
            if (r < sys->rcut) {
                ffac = -4.0*sys->epsilon*(-12.0*pow(sys->sigma/r,12.0)/r
                                         +6*pow(sys->sigma/r,6.0)/r);
          
	  	MPI_Reduce(sys->cx,sys)
                sys->epot += 0.5*4.0*sys->epsilon*(pow(sys->sigma/r,12.0)
                                               -pow(sys->sigma/r,6.0));

                sys->fx[i] += rx/r*ffac;
                sys->fy[i] += ry/r*ffac;
                sys->fz[i] += rz/r*ffac;
            }
        }
    }
}
