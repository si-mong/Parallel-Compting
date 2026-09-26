// 예제3: 구조체를 통한 인자 전달
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 3

// 1. 각 스레드에 대한 데이터를 저장하기 위한 구조체
struct thread_data {
	int thread_id;
	int sum;
	char *message;
};
struct thread_data thread_data_array[NUM_THREADS];	// 전역변수로 구조체 생성
char *messages[NUM_THREADS] = {"Thread 0", "Thread 1", "Thread 2"};

// 2. 스레드 함수
void *PrintHello(void *threadarg) {
	struct thread_data *my_data;
	my_data = (struct thread_data *) threadarg; 	// 2-1. 구조체 포인터로 캐스팅
	
	printf("Thread ID: %d, Message: %s, Sum: %d\n",	
	my_data->thread_id, my_data->message, my_data->sum);	// 구조체 접근 후 출력
	
	pthread_exit(NULL);
}
int main(int argc, char*argv[]){
	pthread_t threads[NUM_THREADS];
	int rc, t, sum = 0;
	
	for(t=0; t<NUM_THREADS;t++){
		sum+=t;
		// 3. 각 스레드의 고유 데이터 초기화
		thread_data_array[t].thread_id = t;
		thread_data_array[t].sum = sum;
		thread_data_array[t].message = messages[t];
		
		printf("Main: creating thread %d\n", t);

		// 4. 특정 구조체 배열 요소의 주소(포인터)를 인자로 전달
		rc = pthread_create(&threads[t], NULL, PrintHello, (void*)&thread_data_array[t]);
		
		if(rc){
			printf("Error: return code from pthread_create() is %d\n", rc);
			exit(-1);
		
		}
	}
	// 5. 스레드 종료될 때까지 대기
	for(t=0; t<NUM_THREADS; t++){
		pthread_join(threads[t], NULL);
	}
	printf("Main: program completed.\n");
	return 0;

}
