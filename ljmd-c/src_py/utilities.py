# helper function: apply minimum image convention 
def pbc(x,boxby2):
    while(x > boxby2):
        x -= 2.0 * boxby2
    #   print " >> ",x
    #rint " -- ",x," < ",-boxby2
    while(x< -boxby2):
        x += 2.0 * boxby2
        print " << ",x
    return x

# helper function: read a line and then return
# the first string with whitespace stripped off 
def get_a_line(line,string):
     stripped = line.strip()
     if not stripped:
        return -1
     string= line.split()[0]
     if(string=='' or "#" in string):
        print "problem reading input"
        return -1
     else:
        return 0

