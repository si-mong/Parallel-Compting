#include <stdio.h>
#include <omp.h>

void main(){
	int tid;
	omp_set_nested(1);	// nest 활성화
	omp_set_num_threads(2);

#pragma omp parallel private(tid)
{
	tid = omp_get_thread_num();
	printf("thread id = %d\n", tid);
	if( tid == 1){
		#pragma omp parallel private(tid)
		{
			tid = omp_get_thread_num();
			printf("\t thread id = %d\n", tid);
		}
	}
}
}
