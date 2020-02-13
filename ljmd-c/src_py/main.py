from utilities import *
import data

trial=data.mdsys_t()
trial.init_from_stdin()
print trial.epsilon
print trial.natoms
print trial.nfi 
print trial.nsteps
print trial.dt
print trial.mass
print trial.epsilon
print trial.sigma
print trial.box 
print trial.rcut
print trial.ekin
print trial.epot
print trial.temp
