#ifndef PROTOTYPES_H
#define PROTOTYPES_H

/* helper function: read a line and then return
   the first string with whitespace stripped off */
static int get_a_line(FILE *fp, char *buf);

/* helper function: zero out an array */
static void azzero(double *d, const int n);

/* helper function: apply minimum image convention */
static double pbc(double x, const double boxby2);

/* compute kinetic energy */
static void ekin(mdsys_t *sys);

/* compute forces */
static void force(mdsys_t *sys);

/* velocity verlet - first part */
static void velverlet_first(mdsys_t *sys);

/* velocity verlet - second part */
static void velverlet_second(mdsys_t *sys);

/* velocity verlet */
static void velverlet(mdsys_t *sys);

/* append data to output. */
static void output(mdsys_t *sys, FILE *erg, FILE *traj);

#endif
