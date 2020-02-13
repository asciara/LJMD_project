# -*- Makefile -*-
SHELL=/bin/sh
############################################
# derived makefile variables
OBJ_SERIAL=$(SRC:src/%.f90=Obj-serial/%.o)
############################################

default: new

new: 
	$(MAKE) $(MFLAGS) -C Obj-$@

test:
	$(MAKE) $(MFLAGS) -C unit_testing/force check
	$(MAKE) $(MFLAGS) -C unit_testing/verlet check
	$(MAKE) $(MFLAGS) -C unit_testing/energy check
	$(MAKE) $(MFLAGS) -C unit_testing/utilities check

serial:
	$(MAKE) $(MFLAGS) -C Obj-$@

mpi:
	$(MAKE) $(MFLAGS) -C Obj-$@


clean:
	$(MAKE) $(MFLAGS) -C Obj-serial clean
	$(MAKE) $(MFLAGS) -C examples clean
	$(MAKE) $(MFLAGS) -C Obj-new clean
	$(MAKE) $(MFLAGS) -C Obj-mpi clean
	$(MAKE) $(MFLAGS) -C unit_testing/force clean
	$(MAKE) $(MFLAGS) -C unit_testing/verlet clean
	$(MAKE) $(MFLAGS) -C unit_testing/energy clean
	$(MAKE) $(MFLAGS) -C unit_testing/utilities clean


check: new
	$(MAKE) $(MFLAGS) -C examples check
