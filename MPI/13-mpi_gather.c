#include <stdio.h>
#include <mpi.h>

int main() {
	int isend,irecv[4]={0,},recvdata[4]={0,},size,rank;
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	isend=rank+1;
	printf("Rank(%d), isend: %d\n",rank,isend);
	MPI_Gather(&isend,1,MPI_INT,irecv,1,MPI_INT,0,MPI_COMM_WORLD);

	if(rank==0) printf("(After ) rank(%d), recv: %d %d %d %d\n", rank,irecv[0],irecv[1],irecv[2],irecv[3]);

	recvdata[0] = isend*10;

	if(rank==0) {
		MPI_Gather(MPI_IN_PLACE,1,MPI_INT,recvdata,1,MPI_INT,0,MPI_COMM_WORLD);	
	} else {
		MPI_Gather(recvdata,1,MPI_INT,recvdata,1,MPI_INT,0,MPI_COMM_WORLD);
	}
	if(rank==0) 
		printf("(After, IN_PLACE) rank(%d), recv: %d %d %d %d\n", 
			rank, recvdata[0], recvdata[1], recvdata[2], recvdata[3]);
	
	MPI_Finalize();
	return 0;
}
