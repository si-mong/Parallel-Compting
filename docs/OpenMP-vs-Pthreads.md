# OpenMP vs Pthreads

> 둘 다 공유 메모리에서 스레드로 병렬화하는데, 무엇이 다른가?

## 핵심

- **Pthreads** — 스레드를 **직접 만들고 관리하는** 저수준 API. "어떻게" 병렬화할지를 코드로 작성한다.
- **OpenMP** — 컴파일러에게 **"여기를 병렬로 돌려라"라고 지시**하는 고수준 모델. "어디를" 병렬화할지만 선언한다.
- OpenMP 런타임도 Linux에서는 내부적으로 pthread 위에서 동작한다.

## 비교

| 항목 | Pthreads | OpenMP |
|------|----------|--------|
| 형태 | 라이브러리 함수 (`pthread_*`) | 컴파일러 지시어 (`#pragma omp`) |
| 컴파일 | `-lpthread` | `-fopenmp` |
| 작업 분할 | 인덱스 범위를 직접 계산 | `#pragma omp for`가 자동 분배 |
| 동기화 | `mutex`, 조건 변수 | `critical`, `atomic`, `reduction`, `barrier` |
| 순차 코드와의 관계 | 스레드 함수 중심으로 다시 작성 | 지시어만 추가하면 됨. `-fopenmp`를 빼면 그대로 순차 실행 |
| 잘 맞는 곳 | 스레드마다 역할이 다른 구조, 세밀한 제어 | 반복문 중심의 데이터 병렬 |

## 공통점

추상화 수준만 다를 뿐 **공유 메모리의 문제는 똑같이** 생긴다.

- Race condition — Pthreads `ex7.c`, OpenMP `omp_example_15.c`
- 해결 방법도 같은 개념 — Pthreads는 mutex로 부분합을 합치고(`ex8.c`), OpenMP는 `reduction`이 이를 자동으로 해 준다(`omp_example_28.c`).

## 정리

빠르고 간단하게 병렬화하려면 **OpenMP**, 스레드를 세밀하게 제어해야 하면 **Pthreads**.
둘 다 **한 노드 안에서만** 동작하며, 여러 노드로 확장하려면 **MPI**가 필요하다.
