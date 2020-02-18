from data import *

def ekin(system):

    system.ekin = 0.0;

    for i in range(system.natoms):
        system.ekin += 0.5 * mvsq2e * system.mass * (system.vx[i] * system.vx[i] + system.vy[i] * system.vy[i] + system.vz[i] * system.vz[i])

    system.temp = 2.0 * system.ekin / (3.0 * system.natoms - 3.0) / kboltz
