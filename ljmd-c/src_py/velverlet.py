from data import mvsq2e

# velocity verlet first part using numpy arrays, call it with:
#velverlet.first(system,np_rx,np_ry,np_rz,np_vx,np_vy,np_vz,np_fx,np_fy,np_fz)

#def first(SYST,rx,ry,rz,vx,vy,vz,fx,fy,fz):
#   vx += 0.5*SYST.dt / mvsq2e * fx / SYST.mass
#   vy += 0.5*SYST.dt / mvsq2e * fy / SYST.mass
#   vz += 0.5*SYST.dt / mvsq2e * fz / SYST.mass
#   rx += SYST.dt*vx
#   ry += SYST.dt*vy
#   rz += SYST.dt*vz

# velocity verlet first part
def first(SYST):
   for i in range(0,SYST.natoms):
       SYST.vx[i] += 0.5*SYST.dt / mvsq2e * SYST.fx[i] / SYST.mass
       SYST.vy[i] += 0.5*SYST.dt / mvsq2e * SYST.fy[i] / SYST.mass
       SYST.vz[i] += 0.5*SYST.dt / mvsq2e * SYST.fz[i] / SYST.mass
       SYST.rx[i] += SYST.dt*SYST.vx[i]
       SYST.ry[i] += SYST.dt*SYST.vy[i]
       SYST.rz[i] += SYST.dt*SYST.vz[i]

# velocity verlet second part 
def second(SYST):
    # second part: propagate velocities by another half step */
    for i in range(0,SYST.natoms):
        SYST.vx[i] += 0.5*SYST.dt / mvsq2e * SYST.fx[i] / SYST.mass
        SYST.vy[i] += 0.5*SYST.dt / mvsq2e * SYST.fy[i] / SYST.mass
        SYST.vz[i] += 0.5*SYST.dt / mvsq2e * SYST.fz[i] / SYST.mass
    


