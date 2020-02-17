/*
 * Test function for utilities functions.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "prototypes.h"
#include <math.h>

int main(int argc, char **argv) {
    
    char line[BLEN];
    
    char str_rest[BLEN];
    sprintf(str_rest, "argon_3.rest");
    char str_traj[BLEN]; 
    sprintf(str_traj, "argon_3.xyz");
    
    char str_ener[BLEN];
    sprintf(str_ener, "argon_3.dat");
    
    int nr = 100;
    int nprint = 100;
    
    
    mdsys_t sys;
    
    sys.natoms=3;             // natoms
    sys.mass=39.948;          // mass in AMU
    sys.epsilon=0.2379;       // epsilon in kcal/mol     ;
    sys.sigma=3.405;          // sigma in angstrom
    sys.rcut=8.5;             // rcut in angstrom
    sys.box=17.1580;          // box length (in angstrom)
    sys.nsteps=1;             // nr MD steps
    sys.dt=5.0;               // MD time step (in fs)
    
    
    
    sys.rx=(double *)malloc(sys.natoms*sizeof(double));
    sys.ry=(double *)malloc(sys.natoms*sizeof(double));
    sys.rz=(double *)malloc(sys.natoms*sizeof(double));
    sys.vx=(double *)malloc(sys.natoms*sizeof(double));
    sys.vy=(double *)malloc(sys.natoms*sizeof(double));
    sys.vz=(double *)malloc(sys.natoms*sizeof(double));
    sys.fx=(double *)malloc(sys.natoms*sizeof(double));
    sys.fy=(double *)malloc(sys.natoms*sizeof(double));
    sys.fz=(double *)malloc(sys.natoms*sizeof(double));


    
    sys.rx[0]=  2.08000000000000;     
    sys.ry[0]= -3.33432278188177;    
    sys.rz[0]= -2.59038677851747;  
    sys.rx[1]=  1.06574058650169;           
    sys.ry[1]= -3.33432278188177;
    sys.rz[1]= -2.59038677851747;
    sys.rx[2]= -1.78412295775301;               
    sys.ry[2]= -16.5259458407765;
    sys.rz[2]=  4.61680014503288;
    
    
    if(get_a_line(stdin,line)) return 1;
    if(sys.natoms!=atoi(line)){
      printf("Error, get_a_line read wrong natom.");
      return -1;
    }
    
    if(get_a_line(stdin,line)) return 1;
    if(sys.mass!=atof(line)){
      printf("Error, get_a_line read wrong mass.");
      return -1;
    }
    
    if(get_a_line(stdin,line)) return 1;
    if(sys.epsilon!=atof(line)){
      printf("Error, get_a_line read wrong epsilon.");
      return -1;
    }

    if(get_a_line(stdin,line)) return 1;
    if(sys.sigma!=atof(line)){
      printf("Error, get_a_line read wrong sigma.");
      return -1;
    }

    if(get_a_line(stdin,line)) return 1;
    if(sys.rcut!=atof(line)){
      printf("Error, get_a_line read wrong rcut.");
      return -1;
    }
    if(get_a_line(stdin,line)) return 1;
    if(sys.box!=atof(line)){
      printf("Error, get_a_line read wrong box.");
      return -1;
    }
    
    
    if(get_a_line(stdin,line)) return 1;
    if(strcmp(str_rest, line)){
      printf("Error, get_a_line read wrong restart file.");
      return -1;
    }
    
    if(get_a_line(stdin,line)) return 1;
    if(strcmp(str_traj, line)){
      printf("Error, get_a_line read wrong trajectory file.");
      return -1;
    }
    
    if(get_a_line(stdin,line)) return 1;
    if(strcmp(str_ener, line)){
      printf("Error, get_a_line read wrong energy file.");
      return -1;
    }
    
    if(get_a_line(stdin,line)) return 1;
    if(nr!=atoi(line)){
      printf("Error, get_a_line read nr.");
      return -1;
    }
    
    if(get_a_line(stdin,line)) return 1;
    if(sys.dt!=atof(line)){
      printf("Error, get_a_line read wrong dt.");
      return -1;
    }
    
    if(get_a_line(stdin,line)) return 1;
    if(nprint!=atoi(line)){
      printf("Error, get_a_line read wrong nprint.");
      return -1;
    }
    
    else
      printf("System inputs read successfully\n");
    
    return 0;
}
    
