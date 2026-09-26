#include <stdio.h>
#include <omp.h>

int main(){
#pragma omp parallel // 디폴트 스레드의 수만큼 스레드 생성
{
	printf("Hello World! %d\n", omp_get_thread_num());
}
	printf("\n");
	omp_set_num_threads(4);	// 라이브러리 이용하여 생성

#pragma omp parallel
{
	printf("Hello World! %d\n", omp_get_thread_num());
}
	printf("\n");

#pragma omp parallel num_threads(2)	// 지시어 사용하여 생성
{
	printf("Hello World %d\n", omp_get_thread_num());
}

}
