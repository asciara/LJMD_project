#-*- Makefile -*-
SHELL=/bin/sh
CC=gcc
CFLAGS=-Wall -g -O3 -ffast-math -fomit-frame-pointer
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
VPATH=.

OBJ=$(SRC:%.c=%.o)
EXE=main.x

default: main.x

clean:
	rm -f *.mod *.o main.x

# linker rule
$(EXE): $(OBJ)
	$(CC) -o $@ $(CFLAGS) $^ $(LDLIBS)

# compilation pattern rule for objects
%.o: %.c 
	$(CC) -c $(CFLAGS) $< -I $(IPATH)

# dependencies
%.o: $(IPATH)%.h
