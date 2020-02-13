import sys
from utilities import *
for line in sys.stdin:
    (R,value)=get_a_line(line)
    if(R==0):print value
