#include <stdio.h>
#include <mpi.h>

int main() {
    int rank, sendbuf[3] = {1, 2, 3}, recvbuf, RECVBUF1[3] = {1, 2, 3};

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // 모든 프로세스의 데이터를 더한(MPI_SUM) 후, 각 프로세스에 동일한 크기(1개씩)로 나누어 분배
    MPI_Reduce_scatter_block(sendbuf, &recvbuf, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    printf("(After) rank(%d), recvbuf= %d\n", rank, recvbuf);

    // MPI_IN_PLACE를 사용하여 별도의 송신 버퍼 없이 RECVBUF1 내에서 제자리 축약 및 분배 진행
    MPI_Reduce_scatter_block(MPI_IN_PLACE, RECVBUF1, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    printf("(After, IN_PLACE) rank(%d),  RECVBUF= %d\n", rank, RECVBUF1[0]);

    MPI_Finalize();
    return 0;
}
