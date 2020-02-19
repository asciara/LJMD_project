#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include <stdio.h>
#include "data.h"

/* helper function: read a line and then return
   the first string with whitespace stripped off */
int get_a_line(FILE *fp, char *buf);

/* helper function: zero out an array */
void azzero(double *d, const int n);


/* compute kinetic energy */
void ekin(mdsys_t *sys);

/* compute forces */
void force(mdsys_t *sys);

/* velocity verlet - first part */
void velverlet_first(mdsys_t *sys);

/* velocity verlet - second part */
void velverlet_second(mdsys_t *sys);

/* velocity verlet */
void velverlet(mdsys_t *sys);

/* append data to output. */
void output(mdsys_t *sys, FILE *erg, FILE *traj);


void fill_cell_list(mdsys_t * sys,_Bool first);

void build_pairs(mdsys_t * sys);

void print_cell_list(mdsys_t * sys);
#endif
