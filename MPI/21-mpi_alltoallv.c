#include <stdio.h>
#include <mpi.h>

int main() {
    int isend[6] = {1, 2, 2, 3, 3, 3}, irecv[9] = {0,};
    int iscnt[3] = {1, 2, 3}, isdsp[3] = {0, 1, 3}, ircnt[3], irdsp[3];
    int rank, size, i;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // 각 프로세스의 송신 데이터(isend) 초기화 (랭크별 오프셋 적용)
    for(i = 0; i < 6; i++) {
        isend[i] = size * rank + isend[i];
    }

    // 각 프로세스가 다른 프로세스들로부터 받을 데이터 개수(ircnt)와 시작 위치(irdsp) 설정
    for(i = 0; i < 3; i++) {
        if(rank == 0) {
            ircnt[i] = 1; 
            irdsp[i] = i;
        }
        else if(rank == 1) {
            ircnt[i] = 2; 
            irdsp[i] = 2 * i;
        }
        else if(rank == 2) {
            ircnt[i] = 3; 
            irdsp[i] = 3 * i;
        }
    }

    // 프로세스마다 서로 다른 크기와 불연속적인 위치의 데이터를 교환 (가변형 All-to-All)
    MPI_Alltoallv(isend, iscnt, isdsp, MPI_INT, irecv, ircnt, irdsp, MPI_INT, MPI_COMM_WORLD);

    printf("(After) rank(%d), irecv= ", rank);
    for(i = 0; i < 9; i++) {
        printf(" %d", irecv[i]);
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}
