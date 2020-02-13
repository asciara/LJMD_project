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

serial:
	$(MAKE) $(MFLAGS) -C Obj-$@

clean:
	$(MAKE) $(MFLAGS) -C Obj-serial clean
	$(MAKE) $(MFLAGS) -C examples clean
	$(MAKE) $(MFLAGS) -C Obj-new clean
	$(MAKE) $(MFLAGS) -C unit_testing/force clean


check: serial
	$(MAKE) $(MFLAGS) -C examples check
