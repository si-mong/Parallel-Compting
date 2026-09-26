#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int i, rank;
    int isend[3] = {0,};
    int irecv = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /* root(rank 0)만 전송 버퍼를 초기화 */
    if (rank == 0)
        for (i = 0; i < 3; i++)
            isend[i] = i + 1;

    /* root의 데이터를 각 rank에 1개씩 분배 */
    MPI_Scatter(isend, 1, MPI_INT, &irecv, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("(After) rank(%d), irecv= %d\n", rank, irecv);

    /* MPI_IN_PLACE 예제 */
    if (rank == 0)
    {
        for (i = 0; i < 3; i++)
            isend[i] = (i + 1) * 10;
    }
    else
    {
        for (i = 0; i < 3; i++)
            isend[i] = 0;
    }

    irecv = 0;

    if (rank == 0)
    {
        /* root는 자기 데이터를 직접 사용 */
        irecv = isend[0];
        MPI_Scatter(isend, 1, MPI_INT, MPI_IN_PLACE, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }
    else
    {
        MPI_Scatter(isend, 1, MPI_INT, &irecv, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }

    printf("(After, IN_PLACE) rank(%d), IRECV=%d\n", rank, irecv);

    MPI_Finalize();
    return 0;
}
