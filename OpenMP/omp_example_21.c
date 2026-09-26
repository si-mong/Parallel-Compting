#include <stdio.h>
#include <omp.h>

int main(){
#pragma omp parallel
{
	int id = omp_get_thread_num();
	#pragma omp for nowait
	for(int i=0; i<4; i++){
		printf("Thread %d doing loop %d\n", id, i);
	}
	printf("Thread %d continues immediately\n", id);
}
	return 0;

}
