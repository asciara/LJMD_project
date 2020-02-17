#include <stdio.h>
#include <math.h> // fabs
#include <stdlib.h> // malloc
#include "prototypes.h"
#include "data.h"
/* main */
int main(int argc, char **argv) 
{
    mdsys_t sys;
    double eps_position=0.00001;
    /* read input file */
    sys.natoms=3;             // natoms
    sys.mass=39.948;          // mass in AMU
    sys.epsilon=0.2379;       // epsilon in kcal/mol     ;
    sys.sigma=3.405;          // sigma in angstrom
    sys.rcut=8.5;             // rcut in angstrom
    sys.box=17.1580;          // box length (in angstrom)
    sys.nsteps=1;             // nr MD steps
    sys.dt=5.0;               // MD time step (in fs)

    /* allocate memory */
    sys.rx=(double *)malloc(sys.natoms*sizeof(double));
    sys.ry=(double *)malloc(sys.natoms*sizeof(double));
    sys.rz=(double *)malloc(sys.natoms*sizeof(double));
    sys.vx=(double *)malloc(sys.natoms*sizeof(double));
    sys.vy=(double *)malloc(sys.natoms*sizeof(double));
    sys.vz=(double *)malloc(sys.natoms*sizeof(double));
    sys.fx=(double *)malloc(sys.natoms*sizeof(double));
    sys.fy=(double *)malloc(sys.natoms*sizeof(double));
    sys.fz=(double *)malloc(sys.natoms*sizeof(double));

    /* setting manually restart values */
    sys.rx[0]=  2.08000000000000;     
    sys.ry[0]= -3.33432278188177;    
    sys.rz[0]= -2.59038677851747;  
    sys.rx[1]=  1.06574058650169;           
    sys.ry[1]= -3.33432278188177;
    sys.rz[1]= -2.59038677851747;
    sys.rx[2]= -1.78412295775301;               
    sys.ry[2]= -16.5259458407765;
    sys.rz[2]=  4.61680014503288;

    /* doing manually azzero's job */
    sys.fx[0]=23064909.177077 ;
    sys.fy[0]=0.000000        ;
    sys.fz[0]=0.000000        ;
    sys.fx[1]=-23064909.177077;
    sys.fy[1]=0.000000        ;
    sys.fz[1]=0.000000        ;
    sys.fx[2]=0.000000        ;
    sys.fy[2]=0.000000        ;
    sys.fz[2]=0.000000        ;

    /* initialize forces and energies.*/
    sys.nfi=0;
    
  //printf("Starting simulation with %d atoms for %d steps.\n",sys.natoms, sys.nsteps);

  //for (int i=0;i<sys.natoms;i++){
  //    printf("BEFORE : Positions of atom %d: (%f,%f,%f)\n",i,sys.rx[i],sys.ry[i],sys.rz[i]);
  //}
  //printf("\n");
    /**************************************************/
    /* main MD loop */
    for(sys.nfi=1; sys.nfi <= sys.nsteps; ++sys.nfi) {
        /* propagate system and recompute energies */
        velverlet_first(&sys);
        velverlet_second(&sys);
    }
    /**************************************************/

  //for (int i=0;i<sys.natoms;i++){
  //    printf("AFTER : Positions of atom %d: (%f,%f,%f)\n",i,sys.rx[i],sys.ry[i],sys.rz[i]);
  //}
  //printf("\n");
  //for (int i=0;i<sys.natoms;i++){
  //    printf("Velocities of atom %d: (%f,%f,%f)\n",i,sys.vx[i],sys.vy[i],sys.vz[i]);
  //}
  //printf("\n");

    if((fabs(sys.rx[0]-(3021.742436 ))>eps_position) ||
       (fabs(sys.ry[0]-(-3.334323   ))>eps_position) ||
       (fabs(sys.rz[0]-(-2.590387   ))>eps_position) ||
       (fabs(sys.rx[1]-(-3018.596695))>eps_position) ||
       (fabs(sys.ry[1]-(-3.334323   ))>eps_position) ||
       (fabs(sys.rz[1]-(-2.590387   ))>eps_position) ||
       (fabs(sys.rx[2]-(-1.784123   ))>eps_position) ||
       (fabs(sys.ry[2]-(-16.525946  ))>eps_position) ||
       (fabs(sys.rz[2]-(4.616800    ))>eps_position) ){
       printf("Error, velvertlet function returned wrong positions\n");
       return -1;
       }
    printf("Velverlet function tested successfully\n");
    /* clean up: close files, free memory */
    free(sys.rx);
    free(sys.ry);
    free(sys.rz);
    free(sys.vx);
    free(sys.vy);
    free(sys.vz);
    free(sys.fx);
    free(sys.fy);
    free(sys.fz);

    return 0;
}
