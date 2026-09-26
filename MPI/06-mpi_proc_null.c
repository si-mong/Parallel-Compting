#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	int rank, size;
	int send_data = 100, recv_data = 0;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if (rank == 0) {
		/* Process 0 sends data to Process 1 and to MPI_PROC_NULL */
		MPI_Send(&send_data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Send(&send_data, 1, MPI_INT, MPI_PROC_NULL, 0, MPI_COMM_WORLD);
		printf("Rank(0) sent data to Rank(1) and MPI_PROC_NULL\n");
	} else if (rank == 1) {
		/* Process 1 receives data from Process 0 */
		MPI_Recv(&recv_data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		printf("Rank(1) received data %d from Rank(0)\n", recv_data);
	} else {
		/* Other processes receive data from MPI_PROC_NULL (no operation) */
		MPI_Recv(&recv_data, 1, MPI_INT, MPI_PROC_NULL, 0, MPI_COMM_WORLD, &status);
		printf("Rank(%d) received data from MPI_PROC_NULL\n", rank);
	}
	MPI_Finalize();
	return 0;
}
