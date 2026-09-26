#include <pthread.h>
#include <stdio.h>
pthread_mutex_t mutex;
pthread_cond_t cond_var;
int count = 0;

void* threadA(void* arg) {
	pthread_mutex_lock(&mutex);

	// A는 대기중, pthread_cond_wait 호출 시 뮤텍스를 자동으로 풀고 잠듦
	// 신호를 받으면 다시 뮤텍스 획득 시도를 위해 깨어남	
	while (count < 10)
		pthread_cond_wait(&cond_var, &mutex); // 조건 만족할 때까지 대기
	
	printf("Thread A: Count reached %d\n", count);
	pthread_mutex_unlock(&mutex);
	return NULL;
}
void* threadB(void* arg) {
	
	pthread_mutex_lock(&mutex);		// 뮤텍스 잠금
	count = 10; 				// Thread A가 기다리는 조건 만족
	pthread_cond_signal(&cond_var); 	// Thread A에 신호 보내기
	printf("Thread B: Count updated to %d\n", count);
	
	// 잠금해제를 하지 않은 경우 -> ThreadA는 블로킹됨
	// B가 뮤텍스를 가진 채로 종료됨 -> 뮤덱스 반납을 못하고 종료
	// pthread_mutex_unlock(&mutex);

	return NULL;
}
int main(){
	
	/* - pthread_cond_wait(), pthread_cond_signal(), pthread_cond_broadcast()는 
	     조건 변수의 핵심적인 동기화 메커니즘
	   - 조건 변수 대기 시 mutex는 자동으로 해제되고, 신호를 받은 후에는 자동으로 다시 잠금
	   - 조건 변수 관련 함수 사용 시 mutex 잠금/해제 및 대기 조건 검사에 대한 올바른 처리 필수
	*/

	pthread_t tA, tB;
	
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond_var, NULL);

	pthread_create(&tA, NULL, threadA, NULL);
	pthread_create(&tB, NULL, threadB, NULL);

	pthread_join(tA, NULL);
	pthread_join(tB, NULL);

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond_var);
	
}
