#include <stdio.h>
#include <omp.h> // 런타임 라이브러리 위한 헤더 파일

int main()
{
#pragma omp parallel // 컴파일러 지시어
{
	printf("Hello World %d\n", omp_get_thread_num()); // 런타임 라이브러리
}
}
