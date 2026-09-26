#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 5

// 각 스레드가 할 작업
void *PrintHello(void *threadid)
{
	long tid;
	tid = (long)threadid;

    	// 스레드 번호와 함께 출력
	printf("Hello World! It's me, thread #%ld!\n", tid);
    	pthread_exit(NULL);
}
int main (int argc, char *argv[]) {

    	pthread_t threads[NUM_THREADS];
    	int rc;
    	long t;

    	for(t = 0; t < NUM_THREADS; t++) {
        	printf("In main: creating thread %ld\n", t);
        	
		// 스레드 생성 -> 스레드 함수와 인자 전달
		rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
		
		// 리턴값이 0이 아니면 생성 실패함
    		if (rc) {
        		printf("ERROR; return code from pthread_create() is %d\n", rc);
        		exit(-1);
    		}

	}

    	/* Last thing that main() should do */
   	 pthread_exit(NULL);
}
