#include <stdio.h>
#include <mpi.h>

int main() {
    int rank, ista, iend, i;
    double A[9] = {0.0,}, sum = 0.0, tsum = 0.0;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // 각 프로세스가 처리할 배열의 시작과 끝 인덱스 계산
    ista = rank * 3; 
    iend = ista + 2;

    for (i = ista; i < iend + 1; i++) A[i] = i + 1;
    sum = 0.0;

    for (i = ista; i < iend + 1; i++) sum += A[i];

    // 모든 프로세스의 sum을 더해서(MPI_SUM) 마스터(0번 랭크)의 tsum으로 취합
    MPI_Reduce(&sum, &tsum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) printf("(After) rank(%d), sum=%.2f\n", rank, tsum);

    MPI_Finalize();
    return 0;
}
