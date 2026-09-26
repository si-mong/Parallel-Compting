#include <stdio.h>
#include <omp.h>

int main(){
	int a[10], tid, i;
	for(i = 0; i<10; i++)
		a[i] = 0;
	omp_set_num_threads(4);

#pragma omp parallel private(a) private(tid)
{
	/* private 속성을 받은 병렬 영역의 배열 a는
	   메인 영역의 a와는 다른 각 스레드들이 
	   서로 다른 메모리 공간에 할당
	*/
	tid = omp_get_thread_num();
	a[tid] = tid + 1;	// 각 스레드는 a[10]를 각각의 메모리에 할당 및 접근
}
	for(i=0; i<4;i++)
		printf("a[%d] = %d\n", i, a[i]);

}
