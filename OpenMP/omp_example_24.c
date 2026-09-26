#include <stdio.h>
#include <omp.h>
#define N 20

void main(){
	int i, sum=0;
	int a[N], b[N];
	for(i=0;i<N;i++){
		a[i] = i+1;
		b[i] = i+2;
	}
	omp_set_num_threads(4);
#pragma omp parallel
{
	#pragma omp for
	for(i=0;i<N;i++)
		sum += a[i] * b[i];	// race condition
}
	printf("sum = %d\n", sum);
}
