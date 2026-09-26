#include <stdio.h>
#include <mpi.h>

int main() {
    int sendbuf[6] = {1, 2, 2, 3, 3, 3};
    int recvbuf[3] = {0,};
    
    // 각 프로세스가 최종적으로 나누어 받아갈 결과 데이터의 개수 (rank 0은 1개, rank 1은 2개, rank 2는 3개)
    int recvcnt[3] = {1, 2, 3};
    int rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // 모든 프로세스의 sendbuf를 원소별로 더한(MPI_SUM) 후, recvcnt에 지정된 크기만큼 잘라서 각 프로세스에 분배
    MPI_Reduce_scatter(sendbuf, recvbuf, recvcnt, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    printf("(After) rank(%d), recvbuf= %d %d %d\n", rank, recvbuf[0], recvbuf[1], recvbuf[2]);

    MPI_Finalize();
    return 0;
}
