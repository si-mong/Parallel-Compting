#include <stdio.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
    int rank, size, tag, i;
    double x, y, buff;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // 각 프로세스별 독립적인 수식 연산 수행
    x = (double)rank;
    y = x * x + x + 1;
    tag = 1;

    // 마스터 프로세스(rank 0)는 다른 프로세스들의 값을 받아 수집 및 평균 계산
    if (rank == 0) {
        for (i = 1; i < size; i++) {
            // 다른 모든 프로세스(i)로부터 계산된 y 값을 받아와 buff에 저장
            MPI_Recv(&buff, 1, MPI_DOUBLE, i, tag, MPI_COMM_WORLD, &status);
            y = y + buff;
        }
        y = y / size;
        printf("Rank(%d) The average value of y is %f\n", rank, y);
    }
    // 나머지 프로세스들은 자신이 계산한 y 값을 마스터 프로세스(0)로 전송
    else {
        MPI_Send(&y, 1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
