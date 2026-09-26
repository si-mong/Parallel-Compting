#include <mpi.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // 0번 랭크 프로세스에만 일부러 3초 지연을 주어 동기화 효과를 실험
    if (rank == 0) sleep(3);

    printf("Before barrier: rank %d\n", rank);

    // 모든 프로세스가 이 지점에 도착할 때까지 더 이상 진행하지 않고 대기 (동기화)
    MPI_Barrier(MPI_COMM_WORLD);

    printf("After barrier: rank %d\n", rank);

    MPI_Finalize();
    return 0;
}
