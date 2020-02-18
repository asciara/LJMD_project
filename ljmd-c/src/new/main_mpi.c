/* 
 * simple lennard-jones potential MD code with velocity verlet.
 * units: Length=Angstrom, Mass=amu; Energy=kcal
 *
 * baseline c version.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "data.h"
#include "prototypes.h"

double seconds(){

    struct timeval tmp;
    double sec;
    gettimeofday( &tmp, (struct timezone *)0 );
    sec = tmp.tv_sec + ((double)tmp.tv_usec)/1000000.0;
    return sec;
}

/* main */
int main(int argc, char **argv) 
{
    int nprint, i;
    double t, t_tmp, t_max;
    char restfile[BLEN], trajfile[BLEN], ergfile[BLEN], line[BLEN];
    FILE *fp,*traj,*erg;
    mdsys_t sys;

#if defined (_OPENMP)
    sys.nthreads = omp_get_num_threads();
#else
    sys.nthreads = 1;
#endif

    sys.mpicomm=MPI_COMM_WORLD;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(sys.mpicomm,&sys.mpirank);
    MPI_Comm_size(sys.mpicomm,&sys.nprocs);

    /* read input file */
    if (sys.mpirank==0){
    	if(get_a_line(stdin,line)) return 1;
    	sys.natoms=atoi(line);
    	if(get_a_line(stdin,line)) return 1;
    	sys.mass=atof(line);
    	
	if(get_a_line(stdin,line)) return 1;
    	sys.epsilon=atof(line);

    	
    	if(get_a_line(stdin,line)) return 1;
    	sys.sigma=atof(line);
    	
    	
	if(get_a_line(stdin,line)) return 1;
    	sys.rcut=atof(line);
    	
    	
	if(get_a_line(stdin,line)) return 1;
    	sys.box=atof(line);
    	

	if(get_a_line(stdin,restfile)) return 1;
    	if(get_a_line(stdin,trajfile)) return 1;
    	if(get_a_line(stdin,ergfile)) return 1;
    	if(get_a_line(stdin,line)) return 1;
    	sys.nsteps=atoi(line);
	if(get_a_line(stdin,line)) return 1;
    	sys.dt=atof(line);	
    	
	if(get_a_line(stdin,line)) return 1;
    	nprint=atoi(line);

    	
    }

	MPI_Bcast(&sys.dt,1,MPI_DOUBLE,0,sys.mpicomm);
	MPI_Bcast(&sys.nsteps,1,MPI_DOUBLE,0,sys.mpicomm);
	MPI_Bcast(&sys.box,1,MPI_DOUBLE,0,sys.mpicomm);
	MPI_Bcast(&sys.rcut,1,MPI_DOUBLE,0,sys.mpicomm);
	MPI_Bcast(&sys.natoms,1,MPI_DOUBLE,0,sys.mpicomm); 
	MPI_Bcast(&sys.sigma,1,MPI_DOUBLE,0,sys.mpicomm);
	MPI_Bcast(&sys.epsilon,1,MPI_DOUBLE,0,sys.mpicomm);
	MPI_Bcast(&sys.mass,1,MPI_DOUBLE,0,sys.mpicomm);
    

	/*sys.natoms=108;
	sys.mass=39.948;
	sys.epsilon=0.2379;
	sys.sigma=3.405;
	sys.rcut=8.5;
	sys.box=17.1580;
	sys.dt=5.0;
	sys.nsteps=1000;	

	sprintf(restfile,"argon_108.rest");
	
	sys.nsize=sys.natoms/sys.nprocs;*/
 
    /* allocate memory */
    sys.rx=(double *)malloc(sys.natoms*sizeof(double));
    sys.ry=(double *)malloc(sys.natoms*sizeof(double));
    sys.rz=(double *)malloc(sys.natoms*sizeof(double));
    sys.vx=(double *)malloc(sys.natoms*sizeof(double));
    sys.vy=(double *)malloc(sys.natoms*sizeof(double));
    sys.vz=(double *)malloc(sys.natoms*sizeof(double));
   
    // Buffer for Broadcast
    sys.cx=(double *)malloc(sys.natoms*sizeof(double));
    sys.cy=(double *)malloc(sys.natoms*sizeof(double));
    sys.cz=(double *)malloc(sys.natoms*sizeof(double));
	if (sys.mpirank==0){
    		sys.fx=(double *)malloc(sys.natoms*sizeof(double));
    		sys.fy=(double *)malloc(sys.natoms*sizeof(double));
    		sys.fz=(double *)malloc(sys.natoms*sizeof(double));
	}


    /* read restart */
    if (sys.mpirank==0){
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
    }
	MPI_Barrier(sys.mpicomm);
    /* initialize forces and energies.*/
    sys.nfi=0;
    force(&sys);

/*if (sys.mpirank==0){
	for (int i=0;i<sys.natoms;i++){
		printf("Force on atom %d: (%f,%f,%f)\n",i,sys.fx[i],sys.fy[i],sys.fz[i]);
	}
	printf("\n");
} */  
   if (sys.mpirank==0){ 
    	erg=fopen(ergfile,"w");
    	traj=fopen(trajfile,"w");
    	ekin(&sys);
    
    printf("Starting simulation with %d atoms for %d steps.\n",sys.natoms, sys.nsteps);
    printf("     NFI            TEMP            EKIN                 EPOT              ETOT\n");
    output(&sys, erg, traj);
   }

    /**************************************************/
    /* main MD loop */
    
    t = 0.0;
    
    for(sys.nfi=1; sys.nfi <= sys.nsteps; ++sys.nfi) {

        /* write output, if requested */
        if ((sys.nfi % nprint) == 0 && sys.mpirank==0)
            output(&sys, erg, traj);
        
        t_tmp = seconds();
        
        /* propagate system and recompute energies */
        if (sys.mpirank==0)
		velverlet_first(&sys);

	    force(&sys);

        if (sys.mpirank==0){
		velverlet_second(&sys);
        	ekin(&sys);    
	    }
	    
	    t = seconds() - t_tmp;
    }
    
    
    printf("Time process %d: %.6f\n", sys.mpirank, t);
    MPI_Reduce( &t, &t_max, 1, MPI_DOUBLE, MPI_MAX, 0, sys.mpicomm );
    if(sys.mpirank==0){
        printf("Evolve time: %.6f\n", t_max);
    }
    
    /**************************************************/

    /* clean up: close files, free memory */
    
if (sys.mpirank==0){
    printf("Simulation Done.\n");
    fclose(erg);
    fclose(traj);

    free(sys.fx);
    free(sys.fy);
    free(sys.fz);
}
    free(sys.rx);
    free(sys.ry);
    free(sys.rz);
    free(sys.vx);
    free(sys.vy);
    free(sys.vz);
    

    MPI_Finalize();
    return 0;
}
