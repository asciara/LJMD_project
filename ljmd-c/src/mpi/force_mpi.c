#include <math.h> //pow,sqrt
#include "data.h"
#include "prototypes.h"

/* helper function: apply minimum image convention */
double pbc(double x, const double boxby2)
{
    while (x >  boxby2) x -= 2.0*boxby2;
    while (x < -boxby2) x += 2.0*boxby2;
    return x;
}


/* compute forces */
void force(mdsys_t *sys) 
{
    double r,ffac;
    double rx,ry,rz;
    int i,j;

    /* zero energy and forces */
    double epot=0.0;

    azzero(sys->cx,sys->natoms);
    azzero(sys->cy,sys->natoms);
    azzero(sys->cz,sys->natoms);

    // rank 0 broadcasts all updated positions to other ranks
    MPI_Bcast(sys->rx,sys->natoms,MPI_DOUBLE,0,sys->mpicomm);
    MPI_Bcast(sys->ry,sys->natoms,MPI_DOUBLE,0,sys->mpicomm);
    MPI_Bcast(sys->rz,sys->natoms,MPI_DOUBLE,0,sys->mpicomm);

    for(i=sys->mpirank; i < sys->natoms; i+=sys->nprocs) {
       
	for(j=i+1;j < (sys->natoms); ++j) {

            /* get distance between particle i and j */
            rx=pbc(sys->rx[i] - sys->rx[j], 0.5*sys->box);
            ry=pbc(sys->ry[i] - sys->ry[j], 0.5*sys->box);
            rz=pbc(sys->rz[i] - sys->rz[j], 0.5*sys->box);
            r = sqrt(rx*rx + ry*ry + rz*rz);
      
            /* compute force and energy if within cutoff */
            if (r < sys->rcut) {
                ffac = -4.0*sys->epsilon*(-12.0*pow(sys->sigma/r,12.0)/r +6*pow(sys->sigma/r,6.0)/r);
          
                epot += 4.0*sys->epsilon*(pow(sys->sigma/r,12.0) -pow(sys->sigma/r,6.0));

		//The c array contains, for every particle in the box, the sum of force contributions coming from particles in a given rank. We need to perform a reduction (MPI_Reduce) to sum the 
		//contributions coming from all ranks.
		
                sys->cx[i] += rx/r*ffac;
                sys->cy[i] += ry/r*ffac;
                sys->cz[i] += rz/r*ffac;
                
		sys->cx[j] -= rx/r*ffac;
                sys->cy[j] -= ry/r*ffac;
                sys->cz[j] -= rz/r*ffac;
	    }

	}
    }

	MPI_Reduce(sys->cx,sys->fx,sys->natoms,MPI_DOUBLE,MPI_SUM,0,sys->mpicomm);
	MPI_Reduce(sys->cy,sys->fy,sys->natoms,MPI_DOUBLE,MPI_SUM,0,sys->mpicomm);
	MPI_Reduce(sys->cz,sys->fz,sys->natoms,MPI_DOUBLE,MPI_SUM,0,sys->mpicomm);
   
	MPI_Reduce(&epot,&sys->epot,1,MPI_DOUBLE,MPI_SUM,0,sys->mpicomm);
            
}
