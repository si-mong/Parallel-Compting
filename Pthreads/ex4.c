#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_THREADS	8

void *PrintHello(void *threadid){
	long taskid;
	sleep(1);

	taskid = *(long *)threadid;
	printf("Hello from thread %ld\n", taskid);

	pthread_exit(NULL);

}

int main(int argc, char *argv[])
{
	pthread_t threads[NUM_THREADS];
	int rc;
	long t;

	for(t=0;t<NUM_THREADS;t++) {

		printf("Creating thread %ld\n", t);
		
		// 변수 t의 값이 아닌 주소를 전달하고 있음
		// 이러면 모든 스레드고 동일한 값을 사용하게 되므로 잘못된 인자 전달 방식
		// 배열을 만들어서 사용하거나 값 자체를 전달하는 방법으로 바꿔야함
		rc = pthread_create(&threads[t], NULL, PrintHello, (void *) &t);

		if (rc) {
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}
	pthread_exit(NULL);

}
