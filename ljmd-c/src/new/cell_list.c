#include <stdlib.h>
#include <stdio.h>
#include "data.h"
#include <math.h>

void fill_cell_list(mdsys_t *sys, _Bool first){
	/*double mod=fmod(sys->box,sys->rcut);
	double div=sys->box/sys->rcut;
	double cell_len=sys->rcut + (double) mod/div;

	int N=sys->box/cell_len;
	sys->N=N;
	printf("cell_len: %f	/ N: %d\n",cell_len,N);
	sys->clist= (cell_t *) malloc(N*N*N*sizeof(cell_t));*/
	int N=sys->N;
	double cell_len=(double) sys->box/N;
	for (int i=0;i<N*N*N;i++){
		if (!first) free(sys->clist[i].idxlist);
		
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
	sys->plist=(int *) malloc(sys->npairs*2*sizeof(int));
	for(int i=0;i<N;++i){
		for (int j=0;j<N;++j){
			for (int k=0,k<N;++k){

			   if (i<N-1 && j<N-1 && k<N-1){
				sys->plist[26*(i*N*N+j*N+k)]=i*N*N+j*N+k;	
				sys->plist[26*(i*N*N+j*N+k)+1]=i*N*N+j*N+k+1;

				sys->plist[26*(i*N*N+j*N+k)+2]=i*N*N+j*N+k;	
				sys->plist[26*(i*N*N+j*N+k)+3]=i*N*N+(j+1)*N+k;
			
				sys->plist[26*(i*N*N+j*N+k)+4]=i*N*N+j*N+k;	
				sys->plist[26*(i*N*N+j*N+k)+5]=i*N*N+(j+1)*N+k+1;
						//
				sys->plist[26*(i*N*N+j*N+k)+6]=i*N*N+j*N+k;	
				sys->plist[26*(i*N*N+j*N+k)+7]=(i+1)*N*N+j*N+k;

				sys->plist[26*(i*N*N+j*N+k)+8]=i*N*N+j*N+k;	
				sys->plist[26*(i*N*N+j*N+k)+9]=(i+1)*N*N+j*N+k+1;

				sys->plist[26*(i*N*N+j*N+k)+10]=i*N*N+j*N+k;	
				sys->plist[26*(i*N*N+j*N+k)+11]=(i+1)*N*N+(j+1)*N+k;

				sys->plist[26*(i*N*N+j*N+k)+12]=i*N*N+j*N+k;
				sys->plist[26*(i*N*N+j*N+k)+13]=(i+1)*N*N+(j+1)*N+k+1;
						//
				sys->plist[26*(i*N*N+j*N+k)+14]=(i+1)*N*N+j*N+k;
				sys->plist[26*(i*N*N+j*N+k)+15]=i*N*N+j*N+k+1;

				sys->plist[26*(i*N*N+j*N+k)+16]=(i+1)*N*N+j*N+k;
				sys->plist[26*(i*N*N+j*N+k)+17]=i*N*N+(j+1)*N+k;

				sys->plist[26*(i*N*N+j*N+k)+18]=(i+1)*N*N+j*N+k;
				sys->plist[26*(i*N*N+j*N+k)+19]=i*N*N+(j+1)*N+k+1;

				sys->plist[26*(i*N*N+j*N+k)+20]=;
				sys->plist[26*(i*N*N+j*N+k)+21]=i+N;

				sys->plist[26*(i*N*N+j*N+k)+22]=i+1;
				sys->plist[26*(i*N*N+j*N+k)+23]=i+N*N+N;

				sys->plist[26*(i*N*N+j*N+k)+24]=i+N;
				sys->plist[26*(i*N*N+j*N+k)+25]=i+N*N+1;
			   }

			 if (i==N-1 && j==N-1 && k<N-1){
			    
			    sys->plist[26*(i*N*N+j*N+k)]=i*N*N+j*N+k;
			    sys->plist[26*(i*N*N+j*N+k)+1]=i*N*N+j*N+1;
			                                               
			    sys->plist[26*(i*N*N+j*N+k)+2]=i*N*N+j*N+k;	
			    sys->plist[26*(i*N*N+j*N+k)+3]=i*N*N+k;
			                                               
			    sys->plist[26*(i*N*N+j*N+k)+4]=i*N*N+j*N+k;	
			    sys->plist[26*(i*N*N+j*N+k)+5]=i*N*N+k+1;
			       // 4 zero with top                              
			    sys->plist[26*(i*N*N+j*N+k)+6]=i*N*N+j*N+k;	
			    sys->plist[26*(i*N*N+j*N+k)+7]=j*N+k;
			                                               
			    sys->plist[26*(i*N*N+j*N+k)+8]=i*N*N+j*N+k;	
			    sys->plist[26*(i*N*N+j*N+k)+9]=j*N;
			                                               
			    sys->plist[26*(i*N*N+j*N+k)+10]=i*N*N+j*N+k;	
			    sys->plist[26*(i*N*N+j*N+k)+11]=k;
			                                               
			    sys->plist[26*(i*N*N+j*N+k)+12]=i*N*N+j*N+k;
			    sys->plist[26*(i*N*N+j*N+k)+13]=0;
			        // top  with zero sides                                
			    sys->plist[26*(i*N*N+j*N+k)+14]=j*N+k;
			    sys->plist[26*(i*N*N+j*N+k)+15]=i*N*N+j*N;
			                                               
			    sys->plist[26*(i*N*N+j*N+k)+16]=j*N+k;
			    sys->plist[26*(i*N*N+j*N+k)+17]=i*N*N+k;
			                                               
			    sys->plist[26*(i*N*N+j*N+k)+18]=j*N+k;
			    sys->plist[26*(i*N*N+j*N+k)+19]=i*N*N;
			         //  sides with top sides                               
			    sys->plist[26*(i*N*N+j*N+k)+20]=i*N*N+j*N;
			    sys->plist[26*(i*N*N+j*N+k)+21]=j*N;
			                                               
			    sys->plist[26*(i*N*N+j*N+k)+22]=i*N*N+k;
			    sys->plist[26*(i*N*N+j*N+k)+23]=j*N+k;
			          // sides betweem them              
			    sys->plist[26*(i*N*N+j*N+k)+24]=i*N*N+j*N;
			    sys->plist[26*(i*N*N+j*N+k)+25]=i*N*N+k;
			 }

			 if (i<N-1 && j==N-1 && k==N-1){
                             sys->plist[26*(i*N*N+j*N+k)]=i*N*N+j*N+k;
                             sys->plist[26*(i*N*N+j*N+k)+1]=i*N*N+j*N;
                                                                        
                             sys->plist[26*(i*N*N+j*N+k)+2]=i*N*N+j*N+k;	
                             sys->plist[26*(i*N*N+j*N+k)+3]=i*N*N+k;
                                                                        
                             sys->plist[26*(i*N*N+j*N+k)+4]=i*N*N+j*N+k;	
                             sys->plist[26*(i*N*N+j*N+k)+5]=i*N*N;
                                // 4 zero with top                              
                             sys->plist[26*(i*N*N+j*N+k)+6]=i*N*N+j*N+k;	
                             sys->plist[26*(i*N*N+j*N+k)+7]=(i+1)*N*N+j*N+k;
                                                                        
                             sys->plist[26*(i*N*N+j*N+k)+8]=i*N*N+j*N+k;	
                             sys->plist[26*(i*N*N+j*N+k)+9]=(i+1)*N*N+j*N;
                                                                        
                             sys->plist[26*(i*N*N+j*N+k)+10]=i*N*N+j*N+k;	
                             sys->plist[26*(i*N*N+j*N+k)+11]=(i+1)*N*N+k;
                                                                        
                             sys->plist[26*(i*N*N+j*N+k)+12]=i*N*N+j*N+k;
                             sys->plist[26*(i*N*N+j*N+k)+13]=(i+1)*N*N;
                                 // top  with zero sides                                
                             sys->plist[26*(i*N*N+j*N+k)+14]=(i+1)*N*N+j*N+k;
                             sys->plist[26*(i*N*N+j*N+k)+15]=i*N*N+j*N;
                                                                        
                             sys->plist[26*(i*N*N+j*N+k)+16]=(i+1)*N*N+j*N+k;
                             sys->plist[26*(i*N*N+j*N+k)+17]=i*N*N+k;
                                                                        
                             sys->plist[26*(i*N*N+j*N+k)+18]=(i+1)*N*N+j*N+k;
                             sys->plist[26*(i*N*N+j*N+k)+19]=i*N*N;
                                  //  sides with top sides                               
                             sys->plist[26*(i*N*N+j*N+k)+20]=i*N*N+j*N;
                             sys->plist[26*(i*N*N+j*N+k)+21]=(i+1)*N*N+j*N;
                                                                        
                             sys->plist[26*(i*N*N+j*N+k)+22]=i*N*N+k;
                             sys->plist[26*(i*N*N+j*N+k)+23]=(i+1)*N*N+k;
                                   // sides betweem them              
                             sys->plist[26*(i*N*N+j*N+k)+24]=i*N*N+j*N;
                             sys->plist[26*(i*N*N+j*N+k)+25]=i*N*N+k;
                         }


			 if (i==N-1 && j<N-1 && k==N-1){
				 
                              sys->plist[26*(i*N*N+j*N+k)]=i*N*N+j*N+k;	
                              sys->plist[26*(i*N*N+j*N+k)+1]=i*N*N+j*N;
                                  // ....                                       
                              sys->plist[26*(i*N*N+j*N+k)+2]=i*N*N+j*N+k;	
                              sys->plist[26*(i*N*N+j*N+k)+3]=i*N*N+(j+1)*N+k;
                                                                      
                              sys->plist[26*(i*N*N+j*N+k)+4]=i*N*N+j*N+k;	
                              sys->plist[26*(i*N*N+j*N+k)+5]=i*N*N+(j+1)*N;
                                  // ....                               
                              sys->plist[26*(i*N*N+j*N+k)+6]=i*N*N+j*N+k;	
                              sys->plist[26*(i*N*N+j*N+k)+7]=j*N+k;
                                                                         
                             sys->plist[26*(i*N*N+j*N+k)+8]=i*N*N+j*N+k;	
                             sys->plist[26*(i*N*N+j*N+k)+9]=j*N;
                                                                        
                             sys->plist[26*(i*N*N+j*N+k)+10]=i*N*N+j*N+k;	
                             sys->plist[26*(i*N*N+j*N+k)+11]=k;
                                                                        
                             sys->plist[26*(i*N*N+j*N+k)+12]=i*N*N+j*N+k;
                             sys->plist[26*(i*N*N+j*N+k)+13]=0;
                                 // top  with zero sides                                
                             sys->plist[26*(i*N*N+j*N+k)+14]=j*N+k;
                             sys->plist[26*(i*N*N+j*N+k)+15]=i*N*N+j*N;
                                                                        
                             sys->plist[26*(i*N*N+j*N+k)+16]=j*N+k;
                             sys->plist[26*(i*N*N+j*N+k)+17]=i*N*N+k;
                                                                        
                             sys->plist[26*(i*N*N+j*N+k)+18]=j*N+k;
                             sys->plist[26*(i*N*N+j*N+k)+19]=i*N*N;
                                  //  sides with top sides                               
                             sys->plist[26*(i*N*N+j*N+k)+20]=i*N*N+j*N;
                             sys->plist[26*(i*N*N+j*N+k)+21]=j*N;
                                                                        
                             sys->plist[26*(i*N*N+j*N+k)+22]=i*N*N+k;
                             sys->plist[26*(i*N*N+j*N+k)+23]=j*N+k;
                                   // sides betweem them              
                             sys->plist[26*(i*N*N+j*N+k)+24]=i*N*N+j*N;
                             sys->plist[26*(i*N*N+j*N+k)+25]=i*N*N+k;
                         }



			 if (i==N-1 && j==N-1 && k==N-1){
				 // 3 zero with sides
                              sys->plist[26*(i*N*N+j*N+k)]=i*N*N+j*N+k;
                              sys->plist[26*(i*N*N+j*N+k)+1]=i*N*N+j*N;
                                                                         
                              sys->plist[26*(i*N*N+j*N+k)+2]=i*N*N+j*N+k;	
                              sys->plist[26*(i*N*N+j*N+k)+3]=i*N*N+k;
                                                                         
                              sys->plist[26*(i*N*N+j*N+k)+4]=i*N*N+j*N+k;	
                              sys->plist[26*(i*N*N+j*N+k)+5]=i*N*N;
                                 // 4 zero with top                              
                              sys->plist[26*(i*N*N+j*N+k)+6]=i*N*N+j*N+k;	
                              sys->plist[26*(i*N*N+j*N+k)+7]=j*N+k;
                                                                         
                              sys->plist[26*(i*N*N+j*N+k)+8]=i*N*N+j*N+k;	
                              sys->plist[26*(i*N*N+j*N+k)+9]=j*N;
                                                                         
                              sys->plist[26*(i*N*N+j*N+k)+10]=i*N*N+j*N+k;	
                              sys->plist[26*(i*N*N+j*N+k)+11]=k;
                                                                         
                              sys->plist[26*(i*N*N+j*N+k)+12]=i*N*N+j*N+k;
                              sys->plist[26*(i*N*N+j*N+k)+13]=0;
                                  // top  with zero sides                                
                              sys->plist[26*(i*N*N+j*N+k)+14]=j*N+k;
                              sys->plist[26*(i*N*N+j*N+k)+15]=i*N*N+j*N;
                                                                         
                              sys->plist[26*(i*N*N+j*N+k)+16]=j*N+k;
                              sys->plist[26*(i*N*N+j*N+k)+17]=i*N*N+k;
                                                                         
                              sys->plist[26*(i*N*N+j*N+k)+18]=j*N+k;
                              sys->plist[26*(i*N*N+j*N+k)+19]=i*N*N;
                                   //  sides with top sides                               
			      sys->plist[26*(i*N*N+j*N+k)+20]=i*N*N+j*N;
                              sys->plist[26*(i*N*N+j*N+k)+21]=j*N;
                                                                         
                              sys->plist[26*(i*N*N+j*N+k)+22]=i*N*N+k;
                              sys->plist[26*(i*N*N+j*N+k)+23]=j*N+k;
                                    // sides betweem them              
                              sys->plist[26*(i*N*N+j*N+k)+24]=i*N*N+j*N;
                              sys->plist[26*(i*N*N+j*N+k)+25]=i*N*N+k;
                         }


			if (i<N-1 && j<N-1 && k==N-1){
                            sys->plist[26*(i*N*N+j*N+k)]=i*N*N+j*N+k;
                            sys->plist[26*(i*N*N+j*N+k)+1]=i*N*N+j*N;
                                                                       
                            sys->plist[26*(i*N*N+j*N+k)+2]=i*N*N+j*N+k;	
                            sys->plist[26*(i*N*N+j*N+k)+3]=i*N*N+(j+1)+k;
                                                                       
                            sys->plist[26*(i*N*N+j*N+k)+4]=i*N*N+j*N+k;	
                            sys->plist[26*(i*N*N+j*N+k)+5]=i*N*N+(j+1);
                               // 4 zero with top                              
                            sys->plist[26*(i*N*N+j*N+k)+6]=i*N*N+j*N+k;	
                            sys->plist[26*(i*N*N+j*N+k)+7]=(i+1)*N*N+j*N+k;
                                                                       
                            sys->plist[26*(i*N*N+j*N+k)+8]=i*N*N+j*N+k;	
                            sys->plist[26*(i*N*N+j*N+k)+9]=(i+1)*N*N+j*N+k+1;
                                                                       
                            sys->plist[26*(i*N*N+j*N+k)+10]=i*N*N+j*N+k;	
                            sys->plist[26*(i*N*N+j*N+k)+11]=(i+1)*N*N+(j+1)*N+k;
                                                                       
                            sys->plist[26*(i*N*N+j*N+k)+12]=i*N*N+j*N+k;
                            sys->plist[26*(i*N*N+j*N+k)+13]=(i+1)*N*N+(j+1)*N+k+1;
                                // top  with zero sides                                
                            sys->plist[26*(i*N*N+j*N+k)+14]=(i+1)*N*N+j*N+k;
                            sys->plist[26*(i*N*N+j*N+k)+15]=i*N*N+j*N;
                                                                       
                            sys->plist[26*(i*N*N+j*N+k)+16]=(i+1)*N*N+j*N+k;
                            sys->plist[26*(i*N*N+j*N+k)+17]=i*N*N+k;
                                                                       
                            sys->plist[26*(i*N*N+j*N+k)+18]=(i+1)*N*N+j*N+k;
                            sys->plist[26*(i*N*N+j*N+k)+19]=i*N*N;
                                 //  sides with top sides                               
                            sys->plist[26*(i*N*N+j*N+k)+20]=i*N*N+j*N;
                            sys->plist[26*(i*N*N+j*N+k)+21]=(i+1)*N*N+j*N+k+1;
                                                                       
                            sys->plist[26*(i*N*N+j*N+k)+22]=i*N*N+k;
                            sys->plist[26*(i*N*N+j*N+k)+23]=(i+1)*N*N+(j+1)*N+k;
                                  // sides betweem them              
                            sys->plist[26*(i*N*N+j*N+k)+24]=i*N*N+j*N;
                            sys->plist[26*(i*N*N+j*N+k)+25]=i*N*N+k;
                        }


			if (i<N-1 && j==N-1 && k<N-1){
                            sys->plist[26*(i*N*N+j*N+k)]=i*N*N+j*N+k;
                            sys->plist[26*(i*N*N+j*N+k)+1]=i*N*N+j*N;
                                                                       
                            sys->plist[26*(i*N*N+j*N+k)+2]=i*N*N+j*N+k;	
                            sys->plist[26*(i*N*N+j*N+k)+3]=i*N*N+k;
                                                                       
                            sys->plist[26*(i*N*N+j*N+k)+4]=i*N*N+j*N+k;	
                            sys->plist[26*(i*N*N+j*N+k)+5]=i*N*N;
                               // 4 zero with top                              
                            sys->plist[26*(i*N*N+j*N+k)+6]=i*N*N+j*N+k;	
                            sys->plist[26*(i*N*N+j*N+k)+7]=(i+1)*N*N+j*N+k;
                                                                       
                            sys->plist[26*(i*N*N+j*N+k)+8]=i*N*N+j*N+k;	
                            sys->plist[26*(i*N*N+j*N+k)+9]=(i+1)*N*N+j*N+k+1;
                                                                       
                            sys->plist[26*(i*N*N+j*N+k)+10]=i*N*N+j*N+k;	
                            sys->plist[26*(i*N*N+j*N+k)+11]=(i+1)*N*N+(j+1)*N+k;
                                                                       
                            sys->plist[26*(i*N*N+j*N+k)+12]=i*N*N+j*N+k;
                            sys->plist[26*(i*N*N+j*N+k)+13]=(i+1)*N*N+(j+1)*N+k+1;
                                // top  with zero sides                                
                            sys->plist[26*(i*N*N+j*N+k)+14]=(i+1)*N*N+j*N+k;
                            sys->plist[26*(i*N*N+j*N+k)+15]=i*N*N+j*N;
                                                                       
                            sys->plist[26*(i*N*N+j*N+k)+16]=(i+1)*N*N+j*N+k;
                            sys->plist[26*(i*N*N+j*N+k)+17]=i*N*N+k;
                                                                       
                            sys->plist[26*(i*N*N+j*N+k)+18]=(i+1)*N*N+j*N+k;
                            sys->plist[26*(i*N*N+j*N+k)+19]=i*N*N;
                                 //  sides with top sides                               
                            sys->plist[26*(i*N*N+j*N+k)+20]=i*N*N+j*N;
                            sys->plist[26*(i*N*N+j*N+k)+21]=(i+1)*N*N+j*N+k+1;
                                                                       
                            sys->plist[26*(i*N*N+j*N+k)+22]=i*N*N+k;
                            sys->plist[26*(i*N*N+j*N+k)+23]=(i+1)*N*N+(j+1)*N+k;
                                  // sides betweem them              
                            sys->plist[26*(i*N*N+j*N+k)+24]=i*N*N+j*N;
                            sys->plist[26*(i*N*N+j*N+k)+25]=i*N*N+k;
                        }


			 if (i==N-1 && j<N-1 && k<N-1){
                        	 
                              sys->plist[26*(i*N*N+j*N+k)]=i*N*N+j*N+k;	
                              sys->plist[26*(i*N*N+j*N+k)+1]=i*N*N+j*N;
                                                                         
                              sys->plist[26*(i*N*N+j*N+k)+2]=i*N*N+j*N+k;	
                              sys->plist[26*(i*N*N+j*N+k)+3]=i*N*N+(j+1)*N+k;
                                  // ....                                      
                              sys->plist[26*(i*N*N+j*N+k)+4]=i*N*N+j*N+k;	
                              sys->plist[26*(i*N*N+j*N+k)+5]=i*N*N+(j+1)*N+k+1;
                                  // ....                               
                              sys->plist[26*(i*N*N+j*N+k)+6]=i*N*N+j*N+k;	
                              sys->plist[26*(i*N*N+j*N+k)+7]=j*N+k;
                                                                         
                             sys->plist[26*(i*N*N+j*N+k)+8]=i*N*N+j*N+k;	
                             sys->plist[26*(i*N*N+j*N+k)+9]=j*N;
                                                                        
                             sys->plist[26*(i*N*N+j*N+k)+10]=i*N*N+j*N+k;	
                             sys->plist[26*(i*N*N+j*N+k)+11]=k;
                                                                        
                             sys->plist[26*(i*N*N+j*N+k)+12]=i*N*N+j*N+k;
                             sys->plist[26*(i*N*N+j*N+k)+13]=0;
                                 // top  with zero sides                                
                             sys->plist[26*(i*N*N+j*N+k)+14]=j*N+k;
                             sys->plist[26*(i*N*N+j*N+k)+15]=i*N*N+j*N;
                                                                        
                             sys->plist[26*(i*N*N+j*N+k)+16]=j*N+k;
                             sys->plist[26*(i*N*N+j*N+k)+17]=i*N*N+k;
                                                                        
                             sys->plist[26*(i*N*N+j*N+k)+18]=j*N+k;
                             sys->plist[26*(i*N*N+j*N+k)+19]=i*N*N;
                                  //  sides with top sides                               
                             sys->plist[26*(i*N*N+j*N+k)+20]=i*N*N+j*N;
                             sys->plist[26*(i*N*N+j*N+k)+21]=j*N;
                                                                        
                             sys->plist[26*(i*N*N+j*N+k)+22]=i*N*N+k;
                             sys->plist[26*(i*N*N+j*N+k)+23]=j*N+k;
                                   // sides betweem them              
                             sys->plist[26*(i*N*N+j*N+k)+24]=i*N*N+j*N;
                             sys->plist[26*(i*N*N+j*N+k)+25]=i*N*N+k;
                         }




			}
		}	
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



