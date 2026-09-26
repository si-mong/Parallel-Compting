#include <stdio.h>
#include <omp.h>

void main(){
        int x = 1, y = 10, z = 20, tid;
        omp_set_nested(1);      // nest 활성화
        omp_set_num_threads(4);

#pragma omp parallel private(y, tid)
{
        tid = omp_get_thread_num();
	x++; y=12; z=22;
        
	#pragma omp parallel num_threads(2) private(x, tid)
        {
        	tid = omp_get_thread_num();
		x = 10; y++; z++;
		printf("\t tid=%d x=%d y=%d z=%d\n", tid, x, y, z);
	
	}
	printf("tid=%d x=%d y=%d z=%d\n", tid, x, y, z);

}
	printf("\n");
	printf("x=%d y=%d z=%d\n", x, y, z);
}
