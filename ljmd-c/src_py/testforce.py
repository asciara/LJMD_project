# FORCE TEST
# run as:
# python3 testforce.py 

import data
from ctypes import *

system = data.mdsys_t()

system.natoms = 3;
system.mass = 39.948;
system.epsilon = 0.2379;
system.sigma = 3.405;
system.rcut = 8.5;
system.box = 17.1580;
system.nthreads=1

print("\nBEGIN FORCE TESTS\n")

system.rx = (c_double * system.natoms)()
system.ry = (c_double * system.natoms)()
system.rz = (c_double * system.natoms)()
system.fx = (c_double * system.natoms)()
system.fy = (c_double * system.natoms)()
system.fz = (c_double * system.natoms)()

fp = open("argon_3.rest", "r")

for i in range(system.natoms):
    rx, ry, rz = fp.readline().split()
    system.rx[i] = c_double(float(rx))
    system.ry[i] = c_double(float(ry))
    system.rz[i] = c_double(float(rz))

fp.close()

system.nfi = 0

fso = CDLL("../Obj-new/libforce.so" )
fso.force.argtypes =[POINTER(data.mdsys_t)] #Structure

fso.force(system)

for i in range(system.natoms):
	print("Force on atom %d: (%f,%f,%f)" % (i, system.fx[i], system.fy[i], system.fz[i]))

print("\nEND FORCE TESTS\n")
