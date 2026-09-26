#include <stdio.h>
#include <omp.h>

int main(void)
{
#ifdef _OPENMP // 컴파일 시 -fopenmp option 없으면 주석 처리
	#pragma omp parallel
	{
		printf("Hello World! %d\n", omp_get_thread_num()); // 현재 스레드 번호 출력
	}
#else
	printf("Hello World! 0\n");
#endif
}
