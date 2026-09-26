#include <stdio.h>
#include <omp.h>
#define N 200000

// 방법1: 스레드 별  임시 변수를 사용하여 마지막에 합산하는 방법
int main(){

	int i, sum = 0;
	int a[N], b[N], c[4];	//스레드 별 사용할 수 있는 배열 c
	
	printf("Use temporal value\n");
	for(i=0; i<N; i++){
		a[i] = i+1;
		b[i] = i+2;
	}
	
	omp_set_num_threads(4);	 

#pragma omp parallel
{
	int tid = omp_get_thread_num();
	c[tid] = 0;
	
	#pragma omp for
 	for(i=0; i<N; i++){
		c[tid] += a[i] * b[i];
	}
	
}
	for(i=0;i<8;i++)
		sum += c[i];

	printf("sum = %d\n", sum);
}
