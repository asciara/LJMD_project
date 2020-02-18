#-*- Makefile -*-
#turn on debug to activate
debug := 
sequential := 
perf :=
ifdef sequential
FOPENMP=
else
FOPENMP=-fopenmp
endif

ifdef perf
FPERF=-fomit-frame-pointer
else
FPERF=
endif

SHELL=/bin/sh
CC=mpicc
ifdef debug
CFLAGS=-O0 -pg -g  $(FOPENMP) $(FPERF)
else
CFLAGS=-Wall -O3 -ffast-math $(FOPENMP) $(FPERF)
endif
LDLIBS=-lm
LIBCOMPIL_FLAGS  = -shared
OFLAGS=-D_MPI
# list of source files
SRC=main_mpi.c \
    energy.c \
    utilities.c \
    output.c \
    data.c \
    force_mpi.c \
    velverlet.c \

IPATH=../include/ 
VPATH=../src/new 

OBJ=$(SRC:%.c=%.o)
EXE=main_mpi.x

default: ../$(EXE)

clean:
	rm -f *.mod *.o *.so ../main_mpi.x

# linker rule
../$(EXE): $(OBJ)
	$(CC) -o $@ $(CFLAGS) $^ $(LDLIBS)

# compilation pattern rule for objects
%.o: %.c 
	$(CC) -c $(CFLAGS) $(OFLAGS) $< -I $(IPATH) 

force_mpi.o: force_mpi.c  data.c utilities.c
	$(CC) -fPIC -c $(CFLAGS) $(OFLAGS) $< -o force_mpi_fpic.o -I $(IPATH)
	$(CC) $(LIBCOMPIL_FLAGS) data_fpic.o utilities_fpic.o force_mpi_fpic.o -o libforce_mpi.so 
	$(CC) -c $(CFLAGS) $(OFLAGS) $< -I $(IPATH)

utilities.o: utilities.c
	$(CC) -fPIC -c $(CFLAGS) $< -o utilities_fpic.o -I $(IPATH)
	$(CC) $(LIBCOMPIL_FLAGS) utilities_fpic.o -o libutilities.so 
	$(CC) -c $(CFLAGS) $< -I $(IPATH)

data.o: data.c
	$(CC) -fPIC -c $(CFLAGS) $< -o data_fpic.o -I $(IPATH)
	$(CC) $(LIBCOMPIL_FLAGS) data_fpic.o -o libdata.so 
	$(CC) -c $(CFLAGS) $< -I $(IPATH)

#energy.o: energy.c  data.c
#	$(CC) -fPIC -c $(CFLAGS) $< -I $(IPATH)
#	$(CC) $(LIBCOMPIL_FLAGS) data.o energy.o -o libenergy.so 

velverlet.o: velverlet.c data.c utilities.c force_mpi.c
	$(CC) -fPIC -c $(CFLAGS) $(OFLAGS) $< -o velverlet_fpic.o -I $(IPATH)
	$(CC) $(LIBCOMPIL_FLAGS) velverlet_fpic.o data_fpic.o utilities_fpic.o force_mpi_fpic.o -o libvelverlet.so
	$(CC) -c $(CFLAGS) $(OFLAGS) $< -I $(IPATH)
	
# dependencies
%.o: $(IPATH)%.h
