#include <stdio.h>
#include <omp.h>
#define N 20

void main(){
        int i, sum=0;
        int a[N], b[N], c[4];	// private 변수 도입

        for(i=0;i<N;i++){
                a[i] = i+1;
                b[i] = i+2;
        }
        omp_set_num_threads(4);
#pragma omp parallel
{
        int tid = omp_get_thread_num();	// 스레드별 private에 저장
	c[tid] = 0;

	#pragma omp for
        for(i=0;i<N;i++)
                c[tid] += a[i] * b[i];     // race condition
}
	for(i=0;i<4;i++)
		sum += c[i];		// 스레드별 변수 합산		

        printf("sum = %d\n", sum);
}
