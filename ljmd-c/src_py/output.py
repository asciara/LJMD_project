from data import * 

def output(system, erg, traj):
    
    print("%8d %20.8f %20.8f %20.8f %20.8f\n" % (system.nfi, system.temp, system.ekin, system.epot, system.ekin + system.epot))
    
    erg.write("%8d %20.8f %20.8f %20.8f %20.8f\n" % (system.nfi, system.temp, system.ekin, system.epot, system.ekin + system.epot))
    
    traj.write("%d\n nfi=%d etot=%20.8f\n" % (system.natoms, system.nfi, system.ekin + system.epot))
    
    for i in range(system.natoms):
        traj.write("Ar  %20.8f %20.8f %20.8f\n" % (system.rx[i], system.ry[i], system.rz[i]))
