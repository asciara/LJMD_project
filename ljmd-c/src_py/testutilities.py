# UTILITIES TESTS
# run as:
# python3 testutilities.py < argon_3.inp 

import data
from ctypes import *
from utilities import get_a_line
import sys

system = data.mdsys_t()
    
system.natoms = 3             # natoms
system.mass = 39.948          # mass in AMU
system.epsilon = 0.2379       # epsilon in kcal/mol     ;
system.sigma = 3.405          # sigma in angstrom
system.rcut = 8.5             # rcut in angstrom
system.box = 17.1580          # box length (in angstrom)
system.nsteps = 100             # nr MD steps
system.dt = 5.0               # MD time step (in fs)

str_rest = "argon_3.rest"
str_traj = "argon_3.xyz"    
str_ener = "argon_3.dat"
    
nprint = 100
      
tests = ["natoms", "mass", "epsilon", "sigma", "rcut", "box", "restart file", "trajectory file", "energy file", "nsteps", "dt", "nprint"]
values = [system.natoms, system.mass, system.epsilon, system.sigma, system.rcut, system.box, str_rest, str_traj, str_ener, system.nsteps, system.dt, nprint]
types = ["int", "float", "float", "float", "float", "float", "str", "str", "str", "int", "float", "int"]

print("\nBEGIN UTILITIES TESTS\n")

for line, test, value, typ in zip(sys.stdin.readlines(), tests, values, types):
    (R, read_value) = get_a_line(line)
    if R != 0:
        print("ERROR: problem reading input.")
        sys.exit(1)
    if value != eval(typ + "(read_value)"):
        print("ERROR: get_a_line read wrong " + test)
        sys.exit(-1)
    else:
        print("OK: get_a_line read correct " + test)
        
print("OK: all tests passed")

print("\nEND UTILITIES TESTS\n")
