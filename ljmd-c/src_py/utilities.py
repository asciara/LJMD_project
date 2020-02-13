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

