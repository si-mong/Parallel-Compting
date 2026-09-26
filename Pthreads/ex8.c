#include <pthread.h>
#include <stdio.h>

#define SIZE 1000
pthread_mutex_t mutex; 	// Mutex 선언
int A[SIZE], B[SIZE]; 	// 벡터 A와 B
int result = 0; 	// 결과값 저장

void* dot_product(void* arg) {
	int start = *(int*)arg;
	int partial_result = 0;

	// 3. 각 쓰레드는 데이터의 일부만 처리
	// => 각 쓰레드는 tid에 따라 처리 구간이 다름 - 서로 독립적인 구간
	for (int i = start; i < start + SIZE/4; i++)
		partial_result += A[i] * B[i];
	
	// 4. 결과를 공유하는 변수에 접근 시 Mutex로 보호
	// => result는 각 스레드가 모두 공유하는 변수이므로 보호해야함
	pthread_mutex_lock(&mutex);	// 락 걸기
	result += partial_result;	// 임계 구역
	pthread_mutex_unlock(&mutex);	// 락 해제
	
	return NULL;
}

int main() {
	pthread_t threads[4]; 	// 4개의 쓰레드
	int indices[4] = {0, SIZE/4, SIZE/2, 3*SIZE/4};	 // 각 스레드의 작업 시작 위치 
	
	// 벡터 초기화 작업	
	for (int i = 0; i < SIZE; i++) {
		A[i] = 1;
		B[i] = 2;
	}
	pthread_mutex_init(&mutex, NULL); // Mutex 초기화
	
	// 1. 각 쓰레드가 dot_product 함수 실행
	for (int i = 0; i < 4; i++)
		pthread_create(&threads[i], NULL, dot_product, (void*)&indices[i]);
	
	
	// 2. 모든 쓰레드가 작업을 마칠 때까지 대기
	// 스레드마다 각 구역을 나눠서 대기했다가 종료해야됨
	for (int i = 0; i < 4; i++)
		pthread_join(threads[i], NULL);

	
	// 최종 결과 출력
	printf("Dot product result: %d\n", result);
	pthread_mutex_destroy(&mutex); 		// Mutex 파괴
	
	return 0;
}

