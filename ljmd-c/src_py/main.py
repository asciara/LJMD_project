import sys
from utilities import *
import data
from ctypes import *

def create_system(input_contents):
   S=data.mdsys_t()
   for count,line in enumerate(input_contents):
       (R,value)=get_a_line(line)
       if(R==0):
          if(  count== 0): S.natoms  = c_int(int(value))
          elif(count== 1): S.mass    = c_double(float(value))
          elif(count== 2): S.epsilon = c_double(float(value))
          elif(count== 3): S.sigma   = c_double(float(value))
          elif(count== 4): S.rcut    = c_double(float(value))
          elif(count== 5): S.box     = c_double(float(value))
          elif(count== 6): restfile  = value
          elif(count== 7): trajfile  = value
          elif(count== 8): ergfile   = value
          elif(count== 9): S.nsteps  = c_int(int(value))
          elif(count==10): S.dt      = c_double(float(value))
          elif(count==11): nprint    = int(value)
   return S,restfile,trajfile,ergfile,nprint


#system,restfile,trajfile,ergfile,nprint=create_system(sys.stdin)

f = open("../examples/argon_108.inp", "r")
system,restfile,trajfile,ergfile,nprint=create_system(f) 
f.close()

force_so = CDLL("../Obj-new/libforce.so")
force_so.force.argtypes =[POINTER(mdsys_t)] #Structure
force_so.force(system)
