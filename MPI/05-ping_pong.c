#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
	int rank, size, ROOT = 0;
	int send = -1, recv = -1;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == ROOT) {
		printf("Before : rank(%d) send = %d, recv = %d\n", rank, send, recv);
		send = 7;	
		MPI_Send(&send, 1, MPI_INT, 1, 55, MPI_COMM_WORLD);
		MPI_Recv(&recv, 1, MPI_INT, 1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		printf("After : rank(%d) send = %d, recv = %d\n", rank, send, recv);
	}
	else {
		MPI_Recv(&recv, 1, MPI_INT, ROOT, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		printf("After : rank(%d) send = %d, recv = %d\n", rank, send, recv);
		send=recv;
		MPI_Send(&send, 1, MPI_INT, ROOT, 88, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}
