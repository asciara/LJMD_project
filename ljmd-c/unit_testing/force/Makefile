#-*- Makefile -*-
SHELL=/bin/sh
CC=mpicc
CFLAGS=-Wall -g -O3 -ffast-math -fomit-frame-pointer
LDLIBS=-lm
OFLAGS=-D_MPI
# list of source files
SRC=testforce_mpi.c utilities.c force_mpi.c

IPATH=../../include/
VPATH=../../src/mpi ../../src/new

OBJ=$(SRC:%.c=%.o)
EXE=main.x

default: $(EXE)

clean:
	rm -f *.mod *.o main.x

# linker rule
$(EXE): $(OBJ)
	$(CC) -o $@ $(CFLAGS) $^ $(LDLIBS)

# compilation pattern rule for objects
%.o: %.c 
	$(CC) -c $(CFLAGS) $(OFLAGS) $< -I $(IPATH)

# dependencies
%.o: $(IPATH)%.h

check: $(EXE) 
	./$(EXE) 
