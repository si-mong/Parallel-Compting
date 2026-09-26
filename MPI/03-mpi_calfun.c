#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
	int rank, size;
	double x,y;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	x = (double)rank;
	y = x*x+x+1;
	printf("process %d: x*x+x+1 = %f, x = %f \n", rank , y, x);
	
	MPI_Finalize();
	return 0;
}
