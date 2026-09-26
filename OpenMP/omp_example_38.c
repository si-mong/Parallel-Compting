#include <stdio.h>
#include <omp.h>
#define N 1000

void main()
{
        printf("===수동 진행===\n");
        int a[N][N], i, j;

        for(i=0; i<N; i++)
                for(j=0; j<N; j++)
                        a[i][j] = 1;

        omp_set_num_threads(4);

#pragma omp parallel for
        for(i=0; i<N*N; i++)
                a[i/N][i%N] = a[i/N][i%N] * 2;

        printf("a[%d][%d]=%d\n", N-1, N-1, a[N-1][N-1]);
}
