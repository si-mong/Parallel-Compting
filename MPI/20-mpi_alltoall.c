#include <stdio.h>
#include <mpi.h>

int main() {
    int isend[3], irecv[3];
    int i, size, rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // 각 프로세스의 송신 데이터(isend) 초기화
    for(i = 0; i < size; i++) {
        isend[i] = 1 + i + size * rank;
    }
    printf("(Before) rank(%d) isend= %d %d %d\n", rank, isend[0], isend[1], isend[2]);

    // 모든 프로세스가 서로 데이터를 주고받는 전체 대 전체(All-to-All) 통신
    MPI_Alltoall(isend, 1, MPI_INT, irecv, 1, MPI_INT, MPI_COMM_WORLD);
    printf("(After ) rank(%d) irecv= %d %d %d\n", rank, irecv[0], irecv[1], irecv[2]);

    for(i = 0; i < 3; i++) {
        irecv[i] = isend[i];
    }
    
    // MPI_IN_PLACE를 사용하여 별도의 송신 버퍼 없이 수신 버퍼(irecv) 내에서 제자리 교환
    MPI_Alltoall(MPI_IN_PLACE, 1, MPI_INT, irecv, 1, MPI_INT, MPI_COMM_WORLD);
    printf("(After, IN_PLACE) rank(%d)  RECV= %d %d %d\n", rank, irecv[0], irecv[1], irecv[2]);

    MPI_Finalize();
    return 0;
}
