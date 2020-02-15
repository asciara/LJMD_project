#-*- Makefile -*-
SHELL=/bin/sh
CC=gcc
CFLAGS=-Wall -g -O3 -ffast-math -fomit-frame-pointer
LDLIBS=-lm
LIBCOMPIL_FLAGS  = -shared

# list of source files
SRC=main.c \
    data.c \
    energy.c \
    utilities.c \
    output.c \
    force.c \
    velverlet.c \

IPATH=../include/
VPATH=../src

OBJ=$(SRC:%.c=%.o)
EXE=main.x

default: ../$(EXE)

clean:
	rm -f *.mod *.o *.so ../main.x

# linker rule
../$(EXE): $(OBJ)
	$(CC) -o $@ $(CFLAGS) $^ $(LDLIBS)

# compilation pattern rule for objects
%.o: %.c 
	$(CC) -c $(CFLAGS) $< -I $(IPATH)

force.o: force.c  data.c utilities.c
	$(CC) -c $(CFLAGS) $< -I $(IPATH)
	$(CC) $(LIBCOMPIL_FLAGS) data.o utilities.o force.o -o libforce.so 

#utilities.o: utilities.c
#	$(CC) -fPIC -c $(CFLAGS) $< -I $(IPATH)
#	$(CC) $(LIBCOMPIL_FLAGS) utilities.o -o libutilities.so 

#data.o: data.c
#	$(CC) -fPIC -c $(CFLAGS) $< -I $(IPATH)
#	$(CC) $(LIBCOMPIL_FLAGS) data.o -o libdata.so 

#energy.o: energy.c  data.c
#	$(CC) -fPIC -c $(CFLAGS) $< -I $(IPATH)
#	$(CC) $(LIBCOMPIL_FLAGS) data.o energy.o -o libenergy.so 

#velverlet.o: velverlet.c data.c utilities.c force.c
#	$(CC) -fPIC -c $(CFLAGS) $< -I $(IPATH)
#	$(CC) $(LIBCOMPIL_FLAGS) velverlet.o data.o utilities.o force.o -o libvelverlet.so

# dependencies
%.o: $(IPATH)%.h
