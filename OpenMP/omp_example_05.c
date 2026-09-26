#include <stdio.h>
#include <omp.h>
#include <unistd.h>

int main()
{
	int tid;
	omp_set_num_threads(4);
#pragma omp parallel
{
	// race condition을 확인할 수 있도록 sleep 추가

	tid=omp_get_thread_num();
	sleep(5);
	printf("I am %d tid = %d\n", omp_get_thread_num(), tid);
}
}
