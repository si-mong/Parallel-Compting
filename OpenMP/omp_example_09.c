#include <stdio.h>
#include <omp.h>

int main(){
	int a[10], tid, i;
	omp_set_num_threads(4);
#pragma omp parallel shared(a) private(tid)
{
	/* shared 속성을 갖는 병렬 영역의
           배열 a는 메인 영역의 a와 같은 메모리 주소를 갖는
	   같은 변수이며 스레드 간 공유
	*/

	tid = omp_get_thread_num();
	a[tid] = tid + 1;
}
	for(i=0; i<4; i++)
		printf("a[%d] = %d\n", i, a[i]);
}
