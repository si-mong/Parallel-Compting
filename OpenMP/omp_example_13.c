#include <stdio.h>
#include <omp.h>

int main()
{
	omp_set_num_threads(4);
#pragma omp parallel
{
	#pragma omp single
	{
		printf("hello world\n");
	}
}
}
