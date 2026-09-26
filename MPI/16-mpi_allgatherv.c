#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int i, rank, tmp;
    int isend[3], irecv[6];
    int iscnt;
    int ircnt[3] = {1, 2, 3};
    int idisp[3] = {0, 1, 3};

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for (i = 0; i < rank + 1; i++)
        isend[i] = rank + 1;

    iscnt = rank + 1;

    MPI_Allgatherv(isend, iscnt, MPI_INT, irecv, ircnt, idisp, MPI_INT, MPI_COMM_WORLD);

    printf("(After) rank(%d), irecv=", rank);
    for (i = 0; i < 6; i++)
        printf(" %d", irecv[i]);
    printf("\n");


    tmp = (rank + 1) * 10;

    if (rank == 0)
        irecv[0] = tmp;

    if (rank == 1)
        irecv[1] = irecv[2] = tmp;

    if (rank == 2)
        irecv[3] = irecv[4] = irecv[5] = tmp;

    MPI_Allgatherv(MPI_IN_PLACE, iscnt, MPI_INT, irecv, ircnt, idisp, MPI_INT, MPI_COMM_WORLD);

    printf("(After, IN_PLACE) rank(%d), irecv=", rank);
    for (i = 0; i < 6; i++)
        printf(" %d", irecv[i]);
    printf("\n");

    MPI_Finalize();
    return 0;
}
