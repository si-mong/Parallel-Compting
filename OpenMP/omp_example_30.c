#include <stdio.h>
#include <omp.h>
#define N 20

int main(){

        int i, sum = 0;
        int a[N], b[N];
       
        for(i=0; i<N; i++){
                a[i] = i+1;
                b[i] = i+2;
        }
        omp_set_num_threads(4);
	
	omp_lock_t lock;
	omp_init_lock(&lock);  

#pragma omp parallel
{
        #pragma omp for
        for(i=0; i<N; i++){
		omp_set_lock(&lock); // 락 획득
                sum += a[i] * b[i];
		omp_unset_lock(&lock); // 락 해제
        }

}
	omp_destroy_lock(&lock);
        printf("sum = %d\n", sum);
}
