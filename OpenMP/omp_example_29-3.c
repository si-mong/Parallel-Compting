#include <stdio.h>
#include <omp.h>
#define N 200000

// 방법3: atomic  도입하여 
int main(){

        int i, sum = 0;
        int a[N], b[N];

        printf("[29-3. Use atomic]\n");
       
        for(i=0; i<N; i++){
                a[i] = i+1;
                b[i] = i+2;
        }
        omp_set_num_threads(4);  

#pragma omp parallel
{
	#pragma omp for
        for(i=0; i<N; i++){
		
		#pragma omp atomic	//CPU가 한 번에 처리-한 줄만 가능
                sum += a[i] * b[i];
        }

}
        printf("sum = %d\n", sum);
}
