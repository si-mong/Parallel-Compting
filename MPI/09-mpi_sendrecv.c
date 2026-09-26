#include <stdio.h>
#include "mpi.h"
int main() {
	int rank, A[4]={0,},B[4]={0,},inext,iprev, i;
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	A[rank]=rank+1;
	inext=rank+1, iprev=rank-1;
	
	if(rank==0) 
		iprev=3;
	
	if(rank==3) 
		inext=0;

	for(i = 0; i < 4; i++) {
		if(rank==i) 
			printf("(Before) rank(%d), A=%d %d %d %d\n",rank,A[0],A[1],A[2],A[3]);
		MPI_Sendrecv(&A[rank],1,MPI_INT,inext,0,&B[rank],1,MPI_INT,iprev,0, 
				MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	}
	
	for(i = 0; i < 4; i++)
		if(rank==i)
			printf("(After ) rank(%d), B=%d %d %d %d\n",rank,B[0],B[1],B[2],B[3]);

	MPI_Finalize();
	return 0;
}
