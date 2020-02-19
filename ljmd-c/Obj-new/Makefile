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
FPERF +=-g
else
FPERF=
endif

SHELL=/bin/sh
CC=gcc
ifdef debug
CFLAGS=-O0 -pg -g  $(FOPENMP) $(FPERF)
else
CFLAGS=-Wall -O3 -ffast-math -march=native -mavx2  $(FOPENMP) $(FPERF)
endif

LDLIBS=-lm
LIBCOMPIL_FLAGS  = -shared $(FOPENMP)

# list of source files
SRC=main.c \
    data.c \
    energy.c \
    utilities.c \
    output.c \
    force.c \
    velverlet.c \

IPATH=../include/ 
VPATH=../src/new 

OBJ=$(SRC:%.c=%.o)
EXE=main.x

default: ../$(EXE)

clean:
	rm -f *.mod *.o *.so ../main.x ../src_py/argon_108.* ../src_py/argon_2916.*
	rm -rf ../src_py/__pycache__

# linker rule
../$(EXE): $(OBJ)
	$(CC) -o $@ $(CFLAGS) $^ $(LDLIBS) 

# compilation pattern rule for objects
%.o: %.c 
	$(CC) -c $(CFLAGS) $< -I $(IPATH) 

force.o: force.c  data.c utilities.c
	$(CC) -fPIC -c $(CFLAGS) $< -o force_fpic.o -I $(IPATH)
	$(CC) $(LIBCOMPIL_FLAGS) data_fpic.o utilities_fpic.o force_fpic.o -o libforce.so 
	$(CC) -c $(CFLAGS) $< -I $(IPATH)

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

velverlet.o: velverlet.c data.c utilities.c force.c
	$(CC) -fPIC -c $(CFLAGS) $< -o velverlet_fpic.o -I $(IPATH)
	$(CC) $(LIBCOMPIL_FLAGS) velverlet_fpic.o data_fpic.o utilities_fpic.o force_fpic.o -o libvelverlet.so
	$(CC) -c $(CFLAGS) $< -I $(IPATH)

# dependencies
%.o: $(IPATH)%.h
