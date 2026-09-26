#include <stdio.h>
#include <omp.h>
#define N 1000000000

int main() {
	long sum=0, a[4*8] = { 0 }, i, tid;

	omp_set_num_threads(4);
#pragma omp parallel private(tid)
{
	tid = omp_get_thread_num();
	#pragma omp for
	for(i=1; i<=N; i++)
		a[tid*8] += i;
	#pragma omp atomic
	sum += a[tid*8];
}
	printf("sum = %ld\n", sum);
}
