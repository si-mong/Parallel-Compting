#include <stdio.h>
#include <omp.h>
#define N 200000

// 방법2: critical 도입하여 동기화 처리 
int main(){

        int i, sum = 0;
        int a[N], b[N];

        printf("[29-2. Use critical]\n");
       
	for(i=0; i<N; i++){
                a[i] = i+1;
                b[i] = i+2;
        }
        omp_set_num_threads(4);  

#pragma omp parallel
{
        #pragma omp for
        for(i=0; i<N; i++){
        
	// critical 을 사용하여 critical section 보호
	// race condition 해결
	#pragma omp critical
	        sum += a[i] * b[i];
        }

}
        printf("sum = %d\n", sum);
}
