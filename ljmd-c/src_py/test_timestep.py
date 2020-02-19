# TIMESTEP TEST
# run as:
# python3 test_timestep.py 

import sys
from utilities import *
import data
from ctypes import *
from output import *
import velverlet

#******************************************************************************

# MAIN

system=data.mdsys_t()

system.natoms=3;             ## natoms
system.mass=39.948;          ## mass in AMU
system.epsilon=0.2379;       ## epsilon in kcal/mol     ;
system.sigma=3.405;          ## sigma in angstrom
system.rcut=8.5;             ## rcut in angstrom
system.box=17.1580;          ## box length (in angstrom)
system.nsteps=1;             ## nr MD steps
system.dt=5.0;               ## MD time step (in fs)
      
# allocate memory

system.rx = (c_double * system.natoms)()
system.ry = (c_double * system.natoms)()
system.rz = (c_double * system.natoms)()
system.vx = (c_double * system.natoms)()
system.vy = (c_double * system.natoms)()
system.vz = (c_double * system.natoms)()
system.fx = (c_double * system.natoms)()
system.fy = (c_double * system.natoms)()
system.fz = (c_double * system.natoms)()

# setting manually restart values
system.rx[0]=  2.08000000000000;     
system.ry[0]= -3.33432278188177;    
system.rz[0]= -2.59038677851747;  
system.rx[1]=  1.06574058650169;           
system.ry[1]= -3.33432278188177;
system.rz[1]= -2.59038677851747;
system.rx[2]= -1.78412295775301;               
system.ry[2]= -16.5259458407765;
system.rz[2]=  4.61680014503288;

# doing manually azzero's and force's jobs
system.fx[0]=23064909.177077 ;
system.fy[0]=0.000000        ;
system.fz[0]=0.000000        ;
system.fx[1]=-23064909.177077;
system.fy[1]=0.000000        ;
system.fz[1]=0.000000        ;
system.fx[2]=0.000000        ;
system.fy[2]=0.000000        ;
system.fz[2]=0.000000        ;

 
# main MD loop 
 
for i in range(0,system.natoms):
  print("BEFORE : Positions of atom %d : (%f,%f,%f)" % (i,system.rx[i],system.ry[i],system.rz[i]))
for system.nfi in range(0, system.nsteps):
    velverlet.first(system)
    velverlet.second(system)
for i in range(0,system.natoms):
  print("AFTER : Positions of atom %d: (%f,%f,%f)" % (i,system.rx[i],system.ry[i],system.rz[i]))
#**************************************************

# clean up: close files
    
print("Simulation Done.");


#******************************************************************************
