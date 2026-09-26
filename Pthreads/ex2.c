#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_THREADS 8
char *messages[NUM_THREADS];

// 스레드가 수행할 함수
void *PrintHello(void *threadid)
{
	long taskid;
	sleep(1);

	// void 형으로 넘어온 거 타입 변환
	taskid = (long) threadid;

	// 각 스레드 번호에 맞는 문장을 출력
	printf("Thread %ld: %s\n", taskid, messages[taskid]);
	pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
	pthread_t threads[NUM_THREADS];
	long taskids[NUM_THREADS];	// 각 스레드에게 넘겨줄 ID 저장 배열
	int rc, t;
	
	// 인덱싱을 통해 각 스레드가 출력할 문자열 저장 -> 전역변수로 사용해서 접
	messages[0] = "English: Hello World!";
	messages[1] = "French: Bonjour, le monde!";
	messages[2] = "Spanish: Hola al mundo";
	messages[3] = "Klingon: Nuq neH!";
	messages[4] = "German: Guten Tag, Welt!";
	messages[5] = "Russian: Zdravstvuy, mir!";
	messages[6] = "Korea: Annyeong Chingooya!";
	messages[7] = "Latin: Orbis, te saluto!";

	for(t=0;t<NUM_THREADS;t++){
		taskids[t]=t;
		printf("Creating thread %d\n", t);
		rc = pthread_create(&threads[t], NULL, PrintHello, (void *)taskids[t]);
		if(rc){
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}
	pthread_exit(NULL);	// 메인 스레드 종료
}
