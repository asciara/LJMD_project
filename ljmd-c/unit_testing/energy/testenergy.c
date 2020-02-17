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
    char restfile[BLEN]/*, trajfile[BLEN], ergfile[BLEN], line[BLEN]*/;
    FILE *fp;//,*traj,*erg;
    mdsys_t sys;

    /* read input file */
    sys.natoms=4;
    sys.mass=39.948;
    
    /* allocate memory */
    sys.vx=(double *)malloc(sys.natoms*sizeof(double));
    sys.vy=(double *)malloc(sys.natoms*sizeof(double));
    sys.vz=(double *)malloc(sys.natoms*sizeof(double));

    /* read restart */
    sprintf(restfile, "argon_4.rest");
    fp=fopen(restfile,"r");
    if(fp) {
        for (i=0; i<sys.natoms; ++i) {
            fscanf(fp,"%lf%lf%lf",sys.vx+i, sys.vy+i, sys.vz+i);
        }
        fclose(fp);
    } else {
        perror("cannot read restart file");
        return 3;
    }

    /* initialize forces and energies.*/
    sys.nfi=0;
    ekin(&sys);

	printf("Kinetic energy on %d atoms: %f\n",sys.natoms,sys.ekin);
    printf("Temperature: %f\n",sys.temp);
    printf("\n");
}

