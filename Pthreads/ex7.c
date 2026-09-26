#include <pthread.h>
#include <stdio.h>

pthread_t tid[2];
int counter =0;

/* 동기화가 이뤄지지 않으면 경쟁 상태(Race condition)이 발생하여 예측 불가능한 결과가
   나타날 수 있다. 예를 들면 두 개의 스레드가 동일한 카운터를 동시에 업데이트 할 경우,
   잘못된 값이 생성될 수 있다.
*/
void* trythis (void* arg) {
    
	// 1. 공유 변수 업데이트 (동기화 처리가 안 된 예제)
	// 두 스레드가 동시에 이 줄을 실행하면 경쟁 상태 발생
    	counter += 1; 

    	printf ("Job %d started\n", counter);

  	// CPU 붙잡아 두기 위한 반복문
    	for (unsigned long i = 0; i < 0xFFFFFFFF; i++); 

    	// 3. 종료 출력
    	// 출력 시점의 counter 값을 읽어오는데, 다른 스레드가 그 사이에 변수 값 변경 가능.
    	printf ("Job %d finished\n", counter);

    	return NULL;
}

int main () {

    // 2개의 스레드 생성
    for (int i = 0; i < 2; i++)
        pthread_create (&tid[i], NULL, trythis, NULL);
    

    // 각 스레드가 끝날 때까지 대기
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    return 0;
}
