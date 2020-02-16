import data
from energy import *
from ctypes import *

# MAIN

# define inputs

system = data.mdsys_t()

system.natoms = 4;
system.mass = 39.948;

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

# initialize forces and energies

system.nfi = 0

ekin(system)

print("Kinetic energy on %d atoms: %f" % (system.natoms, system.ekin))
print("Temperature: %f" % (system.temp));
