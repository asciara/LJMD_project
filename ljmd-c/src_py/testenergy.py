# ENERGY TEST
# run as:
# python3 testenergy.py 

import data
from energy import *
from ctypes import *
import sys

system = data.mdsys_t()

system.natoms = 4;
system.mass = 39.948;

print("\nBEGIN ENERGY TESTS\n")

# allocate memory

system.vx = (c_double * system.natoms)()
system.vy = (c_double * system.natoms)()
system.vz = (c_double * system.natoms)()

# read restart

fp = open("../unit_testing/energy/argon_4.rest", "r")

for i in range(system.natoms):
    vx, vy, vz = fp.readline().split()
    system.vx[i] = c_double(float(vx))
    system.vy[i] = c_double(float(vy))
    system.vz[i] = c_double(float(vz))

fp.close()

# compute kinetic energy and temperature

system.nfi = 0

ekin(system)

print("Kinetic energy on %d atoms: %f" % (system.natoms, system.ekin))
if abs(system.ekin - 0.989665) < 1e-5:
    print("OK: correct kinetic energy")
else:
    print("ERROR: wrong kinetic energy")
    sys.exit(-1)
    
print("\nTemperature: %f" % (system.temp))
if abs(system.temp - 110.670746) < 1e-5:
    print("OK: correct temperature")
else:
    print("ERROR: wrong temperature")
    sys.exit(-1)
    
print("\nOK: energy tests passed")

print("\nEND ENERGY TESTS\n")
