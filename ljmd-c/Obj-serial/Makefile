# -*- Makefile -*-
SHELL=/bin/sh
CC=gcc
CFLAGS=-Wall -g -O3 -ffast-math -fomit-frame-pointer
LDLIBS=-lm
EXE=ljmd-serial.x


# list of source files
SRC=ljmd.c
VPATH=../src
OBJ=$(SRC:%.c=%.o)

default: ../$(EXE)

clean:
	rm -f *.mod *.o ../ljmd-serial.x

# linker rule
../$(EXE): $(OBJ)
	$(CC) -o $@ $(CFLAGS) $^ $(LDLIBS)

# compilation pattern rule for objects
%.o: %.c
	$(CC) -c $(CFLAGS) $<

# dependencies
ljmd.o: ljmd.c
