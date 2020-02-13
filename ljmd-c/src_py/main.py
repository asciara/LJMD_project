import sys
from utilities import *
import data

def create_system(input_contents):
   S=data.mdsys_t()
   for count,line in enumerate(input_contents):
       (R,value)=get_a_line(line)
       if(R==0):
          if(  count== 0): S.natoms  = int(value)
          elif(count== 1): S.mass    = float(value)
          elif(count== 2): S.epsilon = float(value)
          elif(count== 3): S.sigma   = float(value)
          elif(count== 4): S.rcut    = float(value)
          elif(count== 5): S.box     = float(value)
          elif(count== 6): restfile  = value
          elif(count== 7): trajfile  = value
          elif(count== 8): ergfile   = value
          elif(count== 9): S.nsteps  = int(value)
          elif(count==10): S.dt      = float(value)
          elif(count==11): nprint    = int(value)
   return S,restfile,trajfile,ergfile,nprint


#system,restfile,trajfile,ergfile,nprint=create_system(sys.stdin)

f = open("../examples/argon_108.inp", "r")
system,restfile,trajfile,ergfile,nprint=create_system(f) 
f.close()

print system.epsilon
print system.natoms  
print system.nfi     
print system.nsteps  
print system.dt      
print system.mass    
print system.epsilon 
print system.sigma   
print system.box     
print system.rcut    
print system.ekin    
print system.epot    
print system.temp    
