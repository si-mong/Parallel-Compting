#include <stdio.h>
#include <omp.h>
#define N 1000000000

void main() {
	long sum=0, a[4] = { 0 }, i, tid;
	omp_set_num_threads(4);
#pragma omp parallel private(tid)
{
	tid = omp_get_thread_num();
	#pragma omp for
		for(i=1; i<=N; i++)
			a[tid] += i;

	#pragma omp atomic
	sum += a[tid];
}
	printf("sum = %ld\n", sum);
}
