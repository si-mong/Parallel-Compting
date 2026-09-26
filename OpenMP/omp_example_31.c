#include <stdio.h>
#include <omp.h>
#define N 20

int main(){

        omp_nest_lock_t lock;
        omp_init_nest_lock(&lock);  

#pragma omp parallel num_threads(2)
{
	int id = omp_get_thread_num(); // 스레드 아이디 가져오기
	
	// 락을 여러 번 잠글 수 있음
	// 잠근 만큼 해제하면 됨
	omp_set_nest_lock(&lock);
	printf("Thread %d acquired lock (1)\n", id); 
	
	omp_set_nest_lock(&lock);
	printf("Thread %d acquired lock (2)\n", id);

	omp_unset_nest_lock(&lock);
	omp_unset_nest_lock(&lock);
}

        omp_destroy_nest_lock(&lock);
}
