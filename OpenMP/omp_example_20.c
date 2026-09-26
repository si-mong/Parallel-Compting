#include <stdio.h>
#include <omp.h>

int main(){
	int i, a[10];
	omp_set_num_threads(4);

#pragma omp parallel private(i)
{
	#pragma omp for ordered
	for(i=0;i<10;i++){
		a[i] = i * 2;
		#pragma omp ordered
		printf("a[%d] = %d\n", i, a[i]);
	}
}
}
