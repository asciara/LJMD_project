/*
 * Test function for force function. 
 */

#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "prototypes.h"
#include <math.h>

int main(int argc, char **argv) {

    int  i;
    char restfile[BLEN], /*trajfile[BLEN], ergfile[BLEN],*/ line[BLEN];
    FILE *fp;//,*traj,*erg;
    mdsys_t sys;

    /* read input file */
    sys.natoms=3;
    sys.mass=39.948;
    sys.epsilon=0.2379;
    sys.sigma=3.405;
    sys.rcut=8.5;
    sys.box=17.1580;

    /* allocate memory */
    sys.rx=(double *)malloc(sys.natoms*sizeof(double));
    sys.ry=(double *)malloc(sys.natoms*sizeof(double));
    sys.rz=(double *)malloc(sys.natoms*sizeof(double));
    sys.fx=(double *)malloc(sys.natoms*sizeof(double));
    sys.fy=(double *)malloc(sys.natoms*sizeof(double));
    sys.fz=(double *)malloc(sys.natoms*sizeof(double));

    sprintf(restfile,"argon_3.rest");
    /* read restart */
    fp=fopen(restfile,"r");
    if(fp) {
        for (i=0; i<sys.natoms; ++i) {
            fscanf(fp,"%lf%lf%lf",sys.rx+i, sys.ry+i, sys.rz+i);
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

    for (int i=0;i<sys.natoms;i++){
	printf("Force on atom %d: (%f,%f,%f)\n",i,sys.fx[i],sys.fy[i],sys.fz[i]);
    }
    printf("\n");
}

