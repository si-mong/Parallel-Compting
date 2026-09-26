#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int isend;
    int irecv[3] = {0,};
    int rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    isend = rank + 1;
    printf("Rank(%d), isend: %d\n", rank, isend);

    MPI_Allgather(&isend, 1, MPI_INT, irecv, 1, MPI_INT, MPI_COMM_WORLD);
    
    printf("(After) rank(%d), irecv= %d %d %d\n",
           rank, irecv[0], irecv[1], irecv[2]);

    /* MPI_IN_PLACE 사용 예제 */
    isend = (rank + 1) * 10;
    irecv[rank] = isend;

    MPI_Allgather(MPI_IN_PLACE,1,MPI_INT,irecv, 1,
		MPI_INT,MPI_COMM_WORLD);
   
    printf("(After, IN_PLACE) rank(%d), irecv= %d %d %d\n",
           rank, irecv[0], irecv[1], irecv[2]);

    MPI_Finalize();
    return 0;
}
