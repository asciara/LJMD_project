#-*- Makefile -*-

#turn on debug to activate
debug := 

SHELL=/bin/sh
CC=gcc
ifdef debug
CFLAGS=-O0 -pg -g 
else
CFLAGS=-Wall -O3 -ffast-math -fexpensive-optimizations -msse3 -fomit-frame-pointer
endif

LDLIBS=-lm 

# list of source files
SRC=main.c \
    energy.c \
    utilities.c \
    output.c \
    velverlet.c \
    data.c \
    force.c \

IPATH=../include/ 
VPATH=../src/new 

OBJ=$(SRC:%.c=%.o)
EXE=main.x

default: ../$(EXE)

clean:
	rm -f *.mod *.o ../main.x

# linker rule
../$(EXE): $(OBJ)
	$(CC) -o $@ $(CFLAGS) $^ $(LDLIBS) 

# compilation pattern rule for objects
%.o: %.c 
	$(CC) -c $(CFLAGS) $< -I $(IPATH) -I /opt/openmpi/include

# dependencies
%.o: $(IPATH)%.h
