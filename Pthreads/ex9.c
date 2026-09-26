#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex;
pthread_cond_t cond_var;

int count = 0;

// Thread A: 조건을 기다리는 역할
void* threadA(void* arg) {

	// 1. 조건 체크를 위해 뮤텍스 잠금
	pthread_mutex_lock(&mutex);

	// count가 10미만일 동안 계속 대기
	// 대기 중 깨어났을 떄 조건을 다시 확인하기 위해 루프 사용
	while (count < 10) {
		printf("Thread A: 대기 시작 (count = %d)...\n", count);
		
		//2. A는 조건이 만족될 때까지 대기.
		// => 이 함수는 mutex를 자동으로 해제하고, 조건을 만족하는 신호를 받을 때까지 대기
		pthread_cond_wait(&cond_var, &mutex); // 조건 만족할 때까지 대기

	}

	// 조건(count >= 10)이 만족되면 실행됨
	printf("Thread A: Count reached %d\n", count);
	pthread_mutex_unlock(&mutex);		// 작업 완료 후 뮤텍스 해제
	
	return NULL;
	
}


// Thread B: 조건을 만족시키고 신호를 보내는 역할
void* threadB(void* arg) {
	
	/* pthread_cond_signal(): Thread B 는 조건을 만족한 후,
	pthread_cond_signal()로 Thread A에게 신호를 전송
	*/
	
	pthread_mutex_lock(&mutex);
	count = 10; // Thread A가 기다리는 조건 만족 -> while문 조건식
	
	pthread_cond_signal(&cond_var); // Thread A에 신호 보내기
	printf("Thread B: Count updated to %d\n", count);
	
	pthread_mutex_unlock(&mutex);	// 뮤텍스를 풀어줘야 A가 깨어났을 때 루프를 돌 수 있음
	
	return NULL;

}

int main() {

	pthread_t tA, tB;
	
	/* 조건 변수는 효율적인 동기화 메커니즘을 제공하여, 불필요한 폴링을
	피하고 시스템 자원을 절약할 수 있게 함
	*/
	// 뮤텍스와 조건 변수 초기화
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond_var, NULL);
	
	// A 먼저 생성해서 대기 상태로 만든다.
	// B 생성해서 조건 충족시키기 
	pthread_create(&tA, NULL, threadA, NULL);
	pthread_create(&tB, NULL, threadB, NULL);
	
	// 스레드 종료 대기
	pthread_join(tA, NULL);
	pthread_join(tB, NULL);
	
	// 자원 해제
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond_var);
	
	return 0;

}



