#include <stdio.h>
#include <mpi.h>

int main() {
	int rank, a, inext, iprev, i;
	
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	a=rank+1;
	inext=rank+1, iprev=rank-1;

	if(rank==0) iprev=3;
	if(rank==3) inext=0;
	
	for(i = 0; i < 4; i++)
		if(rank==i) 
			printf("(Before) rank(%d), a=%d\n", rank, a);

	MPI_Sendrecv_replace(&a, 1, MPI_INT, inext, 0, iprev, 0,
					MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	
	for(i = 0; i < 4; i++)
		if(rank==i) 
			printf("(After ) rank(%d), a=%d\n", rank, a);

	MPI_Finalize();
	return 0;
}
