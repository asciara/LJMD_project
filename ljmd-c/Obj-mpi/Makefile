#-*- Makefile -*-
SHELL=/bin/sh
CC=mpicc
CFLAGS=-Wall -g -O3 -ffast-math -fomit-frame-pointer
LDLIBS=-lm

# list of source files
SRC=main_mpi.c \
    energy.c \
    utilities.c \
    output.c \
    velverlet.c \
    data.c \
    force_mpi.c \

IPATH=../include/
VPATH=../src ../src/mpi

OBJ=$(SRC:%.c=%.o)
EXE=main_mpi.x

default: ../$(EXE)

clean:
	rm -f *.mod *.o ../main_mpi.x

# linker rule
../$(EXE): $(OBJ)
	$(CC) -o $@ $(CFLAGS) $^ $(LDLIBS)

# compilation pattern rule for objects
%.o: %.c 
	$(CC) -c $(CFLAGS) $< -I $(IPATH)

# dependencies
%.o: $(IPATH)%.h
