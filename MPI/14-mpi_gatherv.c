#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main() {
    int i, rank;
    int isend[3], *irecv;
    int iscnt, ircnt[3] = {1, 2, 3}, idisp[3] = {0, 1, 3};

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // 마스터 프로세스(rank 0)만 최종 데이터를 담을 총 6개 크기의 수신 버퍼 동적 할당
    if(rank == 0) irecv = (int*)malloc(6 * sizeof(int));

    // 각 프로세스의 랭크에 따라 송신할 데이터 개수(iscnt)와 내용(isend)을 다르게 초기화
    iscnt = rank + 1;
    for(i = 0; i < rank + 1; i++) {
        isend[i] = rank + 1;
    }

    // 각 프로세스로부터 서로 다른 개수의 데이터를 모아 마스터(0)의 지정된 위치로 수집
    MPI_Gatherv(isend, iscnt, MPI_INT, irecv, ircnt, idisp, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0) {
        printf("(After ) rank(%d), irecv=", rank);
        for(i = 0; i < 6; i++) {
            printf(" %d", irecv[i]);
        }
        printf("\n");
        free(irecv);
    }

    MPI_Finalize();
    return 0;
}
