#include <stdio.h>
#include <omp.h>
#include <unistd.h>

int main()
{
	omp_set_num_threads(4);

#pragma omp parallel
{
	int tid = omp_get_thread_num(); // 병렬 영역 내에 선언하면 private

	sleep(5);
	printf("I am %d tid = %d\n", omp_get_thread_num(), tid);
}
}
