#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int i, rank;
    int isend[6] = {1, 2, 2, 3, 3, 3};
    int irecv[3] = {0,};
    int isndcnt[3] = {1, 2, 3};
    int idisp[3] = {0, 1, 3};
    int rcvcnt;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    rcvcnt = rank + 1;

    /* 각 rank가 서로 다른 개수의 데이터를 받음 */
    MPI_Scatterv(isend, isndcnt, idisp, MPI_INT, irecv, rcvcnt, MPI_INT, 0, MPI_COMM_WORLD);

    printf("(After) rank(%d), irecv=", rank);
    for (i = 0; i < 3; i++)
        printf("%d ", irecv[i]);
    printf("\n");

    for (i = 0; i < 3; i++)
        irecv[i] = 0;

    if (rank == 0)
    {
        isend[0] = 10;
        isend[1] = 20;
        isend[2] = 20;
        isend[3] = 30;
        isend[4] = 30;
        isend[5] = 30;

        /* root는 자기 데이터 복사 없이 사용 */
        irecv[0] = isend[0];

        MPI_Scatterv(isend, isndcnt, idisp, MPI_INT, MPI_IN_PLACE, rcvcnt, MPI_INT, 0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Scatterv(isend, isndcnt, idisp, MPI_INT, irecv, rcvcnt, MPI_INT, 0, MPI_COMM_WORLD);
    }

    printf("(After, IN_PLACE), rank(%d), IRECV=", rank);
    for (i = 0; i < 3; i++)
        printf("%d ", irecv[i]);
    printf("\n");

    MPI_Finalize();
    return 0;
}
