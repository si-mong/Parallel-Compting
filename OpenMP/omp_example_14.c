#include <stdio.h>
#include <omp.h>
#include <unistd.h>

int main()
{
	omp_set_num_threads(4);
#pragma omp parallel
{
	#pragma omp master
	{
		sleep(1);
		printf("hello world\n");
	}
	printf("tid = %d\n", omp_get_thread_num());
}
}
