#include <stdio.h>
#include "mpi.h"

int main()
{
	int rank,size,count,i;
	float data[100], value[100];
	MPI_Request ireq[100];
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	
	if(rank==0){
		for(i = 0; i < 100; i++) {
			data[i]=1.0*(i+1);
			MPI_Isend(&data[i],1,MPI_FLOAT,1,i,MPI_COMM_WORLD, &ireq[i]);
		}
	} else if(rank==1) {
		for(i = 0; i < 100; i++)
			MPI_Irecv(&value[i],1,MPI_FLOAT,0,i,MPI_COMM_WORLD,&ireq[i]);
	}
	MPI_Waitall(100,ireq,MPI_STATUSES_IGNORE);
	if(rank==1) 
		printf("Rank(%d) value[99]:%f\n",rank, value[99]);
	
	MPI_Finalize();
	return 0;

}
