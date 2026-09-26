#include <stdio.h>
#include <omp.h>

void main(){
        int tid, level;
        omp_set_nested(1);      // nest 활성화
        omp_set_num_threads(4);

#pragma omp parallel private(tid, level)
{
        tid = omp_get_thread_num();
	level = omp_get_level();
        printf("tid id = %d level = %d\n", tid, level);

        if( tid == 1){
                #pragma omp parallel private(tid) num_threads(tid+2)
                {
                        tid = omp_get_thread_num();
                        printf("\t tid = %d ancestor_thread_num(%d) = %d\n", 
				tid, level, omp_get_ancestor_thread_num(level));
                }
        }
}
}
