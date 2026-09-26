#include <stdio.h>
#include <omp.h>

int main()
{
	omp_set_num_threads(4);
	int i = 10, tid;
#pragma omp parallel private(tid) firstprivate(i)
{
	tid = omp_get_thread_num();
	printf("tid = %d i = %d\n", tid, i);
	i = 20;
}
	printf("tid = %d i = %d\n", tid, i);
}
