#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS 4
#define N 1000
#define MEGEXTRA 1000000	// 추가로 할당할 여유 메모리 (1MG)

pthread_attr_t attr;	// 스레드 속성 객체

void *dowork(void *threadid){

	// 1000 X 1000 double 배열 => 8,000,000 바이트(약 8MB) 차지
	// 원래라면 기본 스택 크기가 이것보다 작아서 세그멘테이션 오류 발생
	double A[N][N];
	int i, j;
	long tid;
	size_t mystacksize;

	tid = (long)threadid;

	// 현재 설정된 스택 사이즈 가져오기
	pthread_attr_getstacksize(&attr, &mystacksize);
	printf("Thread %ld: stack size = %li bytes \n", tid, mystacksize);
	
	// 메모리 사용 확인용 연산 수행
	for(i = 0; i<N;i++){
		for(j=0;j<N;j++)
			A[i][j] = ((i * j)/3.452) + (N - i);
	}
	pthread_exit(NULL);
}
int main(int argc, char* argv[]){
	
	pthread_t threads[NTHREADS];
	size_t stacksize;
	int rc;
	long t;

	pthread_attr_init(&attr);		// 1. 속성 객체 초기화	
	pthread_attr_getstacksize(&attr, &stacksize);	// 2. 기본 스택 크기 확인
	printf("Default stack size = %li\n", stacksize);
	
	// 3-1. 필요한 스택 크기 계산 -> 8MG(배열 크기) + 1MG(여유분)
	stacksize = sizeof(double)*N*N+MEGEXTRA;
	printf("Amount of stack needed per thread = %li\n", stacksize);
	
	// 3-2. 스레드 속성에 새로운 스택 크기 설정
	pthread_attr_setstacksize(&attr, stacksize);	// get이랑 set 매개변수 주의...

	printf("Creating threads with stack size = %li bytes\n", stacksize);
	for(t =0; t<NTHREADS; t++){
		rc = pthread_create(&threads[t], &attr, dowork, (void*)t);
		if(rc){
			printf("ERROR: return code from pthred_create() is %d\n", rc);
			exit(-1);
		}
	}
	printf("Created %ld threads. \n", t);
	pthread_exit(NULL);
}
