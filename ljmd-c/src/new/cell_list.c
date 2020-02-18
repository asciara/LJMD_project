#include <stdlib.h>
#include <stdio.h>
#include "data.h"
#include <math.h>

void fill_cell_list(mdsys_t *sys){
	double mod=fmod(sys->box,sys->rcut);
	double div=sys->box/sys->rcut;
	double cell_len=sys->rcut + (double) mod/div;

	int N=sys->box/cell_len;
	sys->N=N;
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

void build_pairs(mdsys_t * sys){
	int N=sys->N;
	sys->npairs=13*N*N*N;
	sys->plist=(cell_t *) malloc(sys->npairs*2*sizeof(cell_t));
	for(int i=0;i<N*N*N;i++){
		sys->plist[26*i]=sys->clist[i];	
		sys->plist[26*i+1]=sys->clist[i+1];

		sys->plist[26*i+2]=sys->clist[i];	
		sys->plist[26*i+3]=sys->clist[i+N];
	
		sys->plist[26*i+4]=sys->clist[i];	
		sys->plist[26*i+5]=sys->clist[i+N+1];
	
		sys->plist[26*i+6]=sys->clist[i];	
		sys->plist[26*i+7]=sys->clist[i+N*N];

		sys->plist[26*i+8]=sys->clist[i];	
		sys->plist[26*i+9]=sys->clist[i+N*N+1];

		sys->plist[26*i+10]=sys->clist[i];	
		sys->plist[26*i+11]=sys->clist[i+N*N+N];

		sys->plist[26*i+12]=sys->clist[i];
		sys->plist[26*i+13]=sys->clist[i+N*N+N+1];

		sys->plist[26*i+14]=sys->clist[i+N*N];
		sys->plist[26*i+15]=sys->clist[i+1];

		sys->plist[26*i+16]=sys->clist[i+N*N];
		sys->plist[26*i+17]=sys->clist[i+N];

		sys->plist[26*i+18]=sys->clist[i+N*N];
		sys->plist[26*i+19]=sys->clist[i+N+1];

		sys->plist[26*i+20]=sys->clist[i+1];
		sys->plist[26*i+21]=sys->clist[i+N];

		sys->plist[26*i+22]=sys->clist[i+1];
		sys->plist[26*i+23]=sys->clist[i+N*N+N];

		sys->plist[26*i+24]=sys->clist[i+N];
		sys->plist[26*i+25]=sys->clist[i+N*N+1];
	
	}
}

/*void print_pairs(mdsys_t * sys){
	int N=sys->N;
        for (int i=0;i<sys->npairs*2;i++){                                                     
		
	}                                                                      
	printf("\n"); 
}*/

void print_cell_list(mdsys_t * sys){
	int N=sys->N;
	for (int i=0;i<N*N*N;i++){
		printf("Cell %d : ",i);
		for (int j=0;j<sys->clist[i].natoms;j++){
			printf("%d ",sys->clist[i].idxlist[j]);
		}
		printf("\n");
	}	

}



