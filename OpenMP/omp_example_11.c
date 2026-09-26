#include <stdio.h>
#include <omp.h>
#define N 20

int main()
{
	int tid, i;
	omp_set_num_threads(4);

#pragma omp parallel private(tid)
{
	tid = omp_get_thread_num();
#pragma omp for
	for(i=0;i<N;i++)
		printf("Hello World %d %d\n", tid, i);
}
}
