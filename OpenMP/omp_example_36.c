#include <stdio.h>
#include <omp.h>

void main() {
#pragma omp parallel num_threads(32) /* 32 threads */
{
        #pragma omp single
        {
                printf("A tid=%d\n", omp_get_thread_num() );

                #pragma omp task /* task 1 */
                {
                        printf("B tid=%d\n", omp_get_thread_num() );
                }
                #pragma omp task /* task 2 */
                {
                        printf("C tid=%d\n", omp_get_thread_num() );
                }
		#pragma omp taskwait
                printf("D tid=%d\n", omp_get_thread_num() );
        }
}
}
