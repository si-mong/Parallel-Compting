#include <stdio.h>
#include <omp.h>

int main(){

#pragma omp parallel num_threads(4)
{
	int id = omp_get_thread_num();

	printf("Thread %d: step 1\n", id);

	#pragma omp barrier // 모든 스레드들이 barrier에 도달할 때까지 대기
	
	printf("Thread %d: step 2\n", id);
}

return 0;
}
