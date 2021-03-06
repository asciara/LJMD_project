#ifndef DATA_H
#define DATA_H
#ifdef _MPI 
#include <mpi.h>
#endif
/* generic file- or pathname buffer length */
#define BLEN 200

/* a few physical constants */
extern const double kboltz;     /* boltzman constant in kcal/mol/K */
extern const double mvsq2e; /* m*v^2 in kcal/mol */

/* structure to hold the complete information 
 * about the MD system */
struct _mdsys {
    int natoms,nfi,nsteps;
    double dt, mass, epsilon, sigma, box, rcut;
    double ekin, epot, temp;
    double *rx, *ry, *rz;
    double *vx, *vy, *vz;
    double *fx, *fy, *fz;
    /*OPENMP data*/
    int nthreads;
    /*MPI data*/
    double *cx, *cy, *cz;
#ifdef _MPI
    MPI_Comm mpicomm;
#endif
    int nprocs;
    int mpirank;
    //int nsize;

};
typedef struct _mdsys mdsys_t;

#endif
