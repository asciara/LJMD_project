#include <stdlib.h>
#include <stdio.h>
#include "data.h"
#include <math.h>

void fill_cell_list(mdsys_t *sys){
	double mod=fmod(sys->box,sys->rcut);
	double div=sys->box/sys->rcut;
	double cell_len=sys->rcut + (double) mod/div;

	int N=sys->box/cell_len;
	sys->CpD=N;
	printf("cell_len: %f	/ N: %d\n",cell_len,N);
	sys->clist= (cell_t *) malloc(N*N*N*sizeof(cell_t));
	for (int i=0;i<N*N*N;i++){
		sys->clist[i].check=0;
		sys->clist[i].natoms=0;
	}
	cell_t *c;
	int * reall;
	double boxby2=(double) sys->box/2;
	for (int i=0;i<sys->natoms;i++){
		printf("(x,y,z):(%f,%f,%f)\n",sys->rx[i],sys->ry[i],sys->rz[i]);
		int idx=(int) (fmod(sys->rx[i],boxby2)+boxby2)/cell_len;
		int idy=(int) (fmod(sys->ry[i],boxby2)+boxby2)/cell_len;
		int idz=(int) (fmod(sys->rz[i],boxby2)+boxby2)/cell_len;
		
		printf("(idx',idy',idz'): (%d,%d,%d)\n",idx,idy,idz);
		int index=(int)(idx +N*idy +N*N*idz);

		printf("clist index: %d\n",index);
		
		c=&sys->clist[index];
		c->natoms ++;
		printf("cell address: %p\tnatoms: %d\n",c,c->natoms);
		if (c->check){ 
			reall= (int *) realloc((void *) c->idxlist,(size_t) c->natoms*sizeof(int));
			if (reall==NULL){ exit;}
			else { c->idxlist=reall;}
		}
		else{
			c->idxlist= (int *) malloc(sizeof(int));
			c->check=1;
		}
		c->idxlist[c->natoms-1]=i;
	}

}

void update_cell_list(){

}

void print_cell_list(mdsys_t * sys){
	int N=sys->CpD;
	for (int i=0;i<N*N*N;i++){
		printf("Cell %d : ",i);
		for (int j=0;j<sys->clist[i].natoms;j++){
			printf("%d ",sys->clist[i].idxlist[j]);
		}
		printf("\n");
	}	

}



