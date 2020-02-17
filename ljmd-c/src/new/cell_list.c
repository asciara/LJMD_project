#include <stdlib.h>
#include "data.h"

void fill_cell_list(mdsys_t *sys){
	double mod=sys->box%sys->rcut;
	double div=sys_>box%sys->rcut;
	double cell_len=sys->rcut + (double) mod/div;

	int N=sys->box/cell_len;
	sys->clist= (cell_t *) malloc(N*N*N*sizeof(cell_t));
	cell_t c;
	for (int i=0;i<sys->natoms;i++){
		c=clist[(sys->rx[i]+N*sys->ry[i]+N*N*sys->rz[i])/cell_len];
		c.natoms ++;
		if (c.idxlist[0]){
			c.idxlist= (int *) realloc(c.idxist,c.natoms*sizeof(int));
		}
		else{
			c.idxlist= (int *) malloc(sizeof(int));
		}
		c.idxlist[c.natoms-1]=i;
	}

}



