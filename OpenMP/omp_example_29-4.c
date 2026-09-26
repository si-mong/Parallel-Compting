#include <stdio.h>
#include <omp.h>
#define N 200000

// 방법4: reduction 사용
int main(){

        int i, sum = 0;
        int a[N], b[N];

        printf("[29-4. reduction]\n");
       
        for(i=0; i<N; i++){
                a[i] = i+1;
                b[i] = i+2;
        }
        omp_set_num_threads(4);  

#pragma omp parallel
{
	/* reduction은 1번 방식을 OpenMP가 알아서 해준다.
           thread가 private sum 생성 -> loop 계산 -> 마지막에 모든 값 결합
	*/	
	#pragma omp for reduction (+:sum)	
        for(i=0; i<N; i++){
                sum += a[i] * b[i];
        }

}
        printf("sum = %d\n", sum);
}
