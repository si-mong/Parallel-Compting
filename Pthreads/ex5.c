#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUM_THREADS 4

// 스레드 수행 함수
void *BusyWork(void *t)
{
	int i;
	long tid;
	double result = 0.0;
	tid = (long)t;
	printf("Thread %ld starting...\n",tid);
	
	for (i = 0; i < 1000000; i++)
		result = result + sin(i) * tan(i);
	
	printf("Thread %ld done. Result = %e\n", tid, result);
	
	// 스레드 종료 시 자신의 ID를 상태값으로 반환
	pthread_exit((void*) t);
}

int main (int argc, char *argv[])
{
	pthread_t thread[NUM_THREADS];
	pthread_attr_t attr;
	int rc;
	long t;
	void *status;

	// 1.스레드 속성 초기화 및 detached 속성 설정
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	for(t = 0; t < NUM_THREADS; t++) {
		printf("Main: creating thread %ld\n", t);
		// 설정한 속성(&attr) 사용해서 스레드 생성
		rc = pthread_create(&thread[t], &attr, BusyWork, (void *)t);
		if (rc) {
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}
	// 2. 사용이 끝난 속성 객체 소멸 
	pthread_attr_destroy(&attr);
	
	// 3. 각 스레드가 종료될 때까지 대기하고 반환값 받기
	for(t = 0; t < NUM_THREADS; t++) {
		rc = pthread_join(thread[t], &status);	// 스레드가 끝날 때까지 대기
		if (rc) {
			printf("ERROR; return code from pthread_join() is %d\n", rc);
			exit(-1);
		}
		printf("Main: completed join with thread %ld having a status "\
		"of %ld\n", t, (long)status);
	}
	printf("Main: program completed. Exiting.\n");
	pthread_exit(NULL);
}
