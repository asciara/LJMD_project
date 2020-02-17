# helper function: apply minimum image convention 
def pbc(x,boxby2):
    while(x > boxby2):
        x -= 2.0 * boxby2
    #   print " >> ",x
    #rint " -- ",x," < ",-boxby2
    while(x< -boxby2):
        x += 2.0 * boxby2
        print(" << ",x)
    return x

# helper function: read a line and then return
# the first string with whitespace stripped off 
def get_a_line(line):
     stripped = line.strip()
     if not stripped:
        return (-1,val)
     val = line.split()[0]
     if(val=='' or "#" in val):
        print("problem reading input")
        return (-1,val)
     else:
        return (0,val)

