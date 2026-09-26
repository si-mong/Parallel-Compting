#include <stdio.h>
#include <omp.h>

int main()
{
	int tid;
	omp_set_num_threads(4);
#pragma omp parallel
{
	// tid 라는 공유 변수에 스레드가 랜덤한 순서로 접근함
	// 랜덤하게 tid를 출력할 것으로 기대되지만 실제 상황은 더 복잡함
	tid = omp_get_thread_num();
	printf("I am %d tid = %d\n", omp_get_thread_num(), tid);
}
}
