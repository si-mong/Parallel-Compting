# Pthreads 실습

병렬컴퓨팅 수업의 **POSIX Threads(pthread)** 실습 자료입니다.
공유 메모리 환경에서 `pthread` 라이브러리로 스레드를 생성·관리하고,
인자 전달·동기화(Mutex, 조건 변수)·경쟁 상태(Race Condition)를 단계별로 다룹니다.

> 참고 강의자료: `강의자료/Lab-Pthreads.pdf`, `PThreads 기반 병렬처리.pdf`

---

## 실습 환경 & 컴파일

- **OS**: Rocky Linux (VirtualBox 가상머신)
- **컴파일**: `gcc exN.c -lpthread -o exN` (일부 예제는 `-lm` 필요 — `ex5`)
- **실행**: `./exN`

```bash
gcc ex1.c -lpthread -o ex1
./ex1

gcc ex5.c -lpthread -lm -o ex5   # sin/tan 사용 → 수학 라이브러리 링크
./ex5
```

> 확장자 없는 `ex1`~`ex10` 파일은 컴파일된 실행 바이너리입니다.

---

## 예제 목록 (`ex1.c` ~ `ex10.c`)

| 파일 | 주제 | 핵심 내용 |
|------|------|-----------|
| `ex1.c` | 스레드 생성 기본 | `pthread_create`로 5개 스레드 생성, 스레드 번호를 인자로 전달 후 출력 |
| `ex2.c` | 전역 배열 활용 | 전역 `messages[]` 배열에서 스레드 번호에 맞는 문자열 출력 |
| `ex3.c` | 구조체로 인자 전달 | `struct`로 여러 값(id/sum/message)을 묶어 전달, `pthread_join`으로 종료 대기 |
| `ex4.c` | 잘못된 인자 전달 | 반복 변수 `&t`의 **주소**를 전달 → 모든 스레드가 같은 값을 공유하는 문제 예시 |
| `ex5.c` | 스레드 속성 & 반환값 | `pthread_attr_t`(JOINABLE) 설정, `pthread_join`으로 각 스레드의 상태값 회수 |
| `ex6.c` | 스택 크기 조정 | `pthread_attr_setstacksize`로 큰 지역 배열(`8MB`) 처리를 위한 스택 확장 |
| `ex7.c` | Race Condition | 동기화 없이 공유 변수 `counter` 증가 → 예측 불가능한 결과 |
| `ex8.c` | Mutex 동기화 | 벡터 내적을 4스레드로 분할 계산, `pthread_mutex`로 공유 결과 변수 보호 |
| `ex9.c` | 조건 변수 | `pthread_cond_wait`/`pthread_cond_signal`로 스레드 간 조건 기반 동기화 |
| `ex10.c` | 조건 변수 - 오류 사례 | 신호 후 mutex unlock을 누락하면 대기 스레드가 블로킹되는 문제 확인 |

---

## 핵심 개념 흐름

1. **스레드 생성/종료** (`ex1`~`ex3`): `pthread_create`, `pthread_join`, `pthread_exit`, 인자 전달 방법
2. **인자 전달 함정** (`ex4`): 값 vs 주소 전달의 차이
3. **스레드 속성** (`ex5`, `ex6`): `pthread_attr_t`, JOINABLE, 스택 크기
4. **동기화** (`ex7`~`ex10`):
   - `ex7`: 동기화가 없으면 왜 문제인가 (Race Condition)
   - `ex8`: **Mutex**(`pthread_mutex_lock/unlock`)로 임계 구역 보호
   - `ex9`, `ex10`: **조건 변수**(`pthread_cond_*`)로 스레드 간 신호 전달, 올바른 mutex 처리의 중요성

---

## 예제 코드

### `ex8.c` — Mutex로 임계 구역 보호 (벡터 내적)
```c
pthread_mutex_lock(&mutex);   // 락 획득
result += partial_result;     // 임계 구역: 공유 변수 갱신
pthread_mutex_unlock(&mutex); // 락 해제
```

### `ex9.c` — 조건 변수
```c
// Thread A: 조건 대기
pthread_mutex_lock(&mutex);
while (count < 10)
    pthread_cond_wait(&cond_var, &mutex);  // mutex 자동 해제 후 신호 대기
pthread_mutex_unlock(&mutex);

// Thread B: 조건 충족 후 신호 전송
pthread_mutex_lock(&mutex);
count = 10;
pthread_cond_signal(&cond_var);
pthread_mutex_unlock(&mutex);
```
