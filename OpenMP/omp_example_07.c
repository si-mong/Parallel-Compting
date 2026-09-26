#include <stdio.h>
#include <omp.h>

int main()
{
	int tid;
	omp_set_num_threads(4);

#pragma omp parallel private(tid)	// private 속성의 tid는 메인과는 별개의 변수
{
	tid = omp_get_thread_num(); 	
	printf("I am %d tid = %d\n", omp_get_thread_num(), tid);
}
// 병렬 영역이 끝나면 private tid는 모두 사라지며, 메인 영역의 tid에는 영향도 주지 못함
}
