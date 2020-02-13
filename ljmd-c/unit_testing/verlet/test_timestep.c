#include <stdio.h>
/* main */
int main(int argc, char **argv) 
{
    int nprint, i;
    char restfile[BLEN];
    FILE *fp,*traj,*erg;
    mdsys_t sys;

    /* read input file */
    sys.natoms=3;               # natoms
    sys.mass=39.948;            # mass in AMU
    sys.epsilon=0.2379;            # epsilon in kcal/mol     ;
    sys.sigma=3.405;             # sigma in angstrom
    sys.rcut=8.5;               # rcut in angstrom
    sys.box=17.1580;           # box length (in angstrom)
    sys.nsteps=1;             # nr MD steps
    sys.dt=5.0;               # MD time step (in fs)
    nprint=100;               # output print frequency

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

    /* read restart */
    fp=fopen(restfile,"r");
    if(fp) {
        for (i=0; i<sys.natoms; ++i) {
            fscanf(fp,"%lf%lf%lf",sys.rx+i, sys.ry+i, sys.rz+i);
        }
        for (i=0; i<sys.natoms; ++i) {
            fscanf(fp,"%lf%lf%lf",sys.vx+i, sys.vy+i, sys.vz+i);
        }
        fclose(fp);
        azzero(sys.fx, sys.natoms);
        azzero(sys.fy, sys.natoms);
        azzero(sys.fz, sys.natoms);
    } else {
        perror("cannot read restart file");
        return 3;
    }

    /* initialize forces and energies.*/
    sys.nfi=0;
    force(&sys);
    
    printf("Starting simulation with %d atoms for %d steps.\n",sys.natoms, sys.nsteps);

    for (int i=0;i<sys.natoms;i++){
	printf("BEFORE : Positions of atom %d: (%f,%f,%f)\n",i,sys.rx[i],sys.ry[i],sys.rz[i]);
    }
    printf("\n");
    /**************************************************/
    /* main MD loop */
    for(sys.nfi=1; sys.nfi <= sys.nsteps; ++sys.nfi) {
        /* propagate system and recompute energies */
        velverlet_first(&sys);
        velverlet_second(&sys);
    }
    /**************************************************/

    for (int i=0;i<sys.natoms;i++){
	printf("Velocities of atom %d: (%f,%f,%f)\n",i,sys.vx[i],sys.vy[i],sys.vz[i]);
	printf("AFTER : Positions of atom %d: (%f,%f,%f)\n",i,sys.rx[i],sys.ry[i],sys.rz[i]);
    }
    printf("\n");

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
