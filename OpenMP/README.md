# OpenMP 실습

병렬컴퓨팅 수업의 **OpenMP** 실습 자료입니다.
공유 메모리 환경에서 컴파일러 지시어(`#pragma omp`)와 런타임 라이브러리(`omp_*`)를 이용해
멀티스레드 병렬 프로그램을 작성하고, 데이터 스코프·동기화·성능 이슈를 단계별로 다룹니다.

> 참고 강의자료: `강의자료/Lab-OpenMP.pdf`, `OpenMP-1.pdf`, `OpenMP-2.pdf`

---

## 실습 환경

- **OS**: Rocky Linux 10 (VirtualBox 가상머신, CPU 8코어로 설정)
- **패키지 설치**: `sudo dnf install -y gcc libomp-devel`
- **컴파일**: `gcc omp_example_XX.c -fopenmp -o omp_example_XX.x`
- **실행**: `./omp_example_XX.x`
- **스레드 수 지정**: `export OMP_NUM_THREADS=8` (또는 코드 내 `omp_set_num_threads()`, 지시어 `num_threads()`)
- **코어 수 확인**: `cat /proc/cpuinfo | grep "processor" | wc -l`

> `.x` 파일은 컴파일된 실행 바이너리입니다. `_OPENMP` 매크로는 `-fopenmp` 옵션이 있을 때만 정의되어, 조건부 컴파일에 활용할 수 있습니다.

### OpenMP 구성요소

| 구성요소 | 형태 |
|----------|------|
| 컴파일러 지시어 | `#pragma omp <directive>` |
| 런타임 라이브러리 | `omp_...` (예: `omp_get_thread_num()`) |
| 환경 변수 | `OMP_...` (예: `OMP_NUM_THREADS`) |

---

## 예제 목록 (`omp_example_01.c` ~ `omp_example_40.c`)

### 1. 기초

| 파일 | 주제 | 핵심 내용 |
|------|------|-----------|
| `omp_example_01.c` | Hello World | `#pragma omp parallel`로 스레드별 출력, 실행 순서는 비결정적 |
| `omp_example_02.c` | `_OPENMP` 매크로 | `#ifdef _OPENMP`로 OpenMP 활성화 여부에 따른 조건부 컴파일 |
| `omp_example_03.c` | 스레드 개수 지정 | 기본 스레드 수 / `omp_set_num_threads()` / `num_threads()` 세 가지 방법 (`03-1`은 변형) |

### 2. 데이터 스코프 (private / shared)

| 파일 | 주제 | 핵심 내용 |
|------|------|-----------|
| `omp_example_04.c` | 공유 변수 이슈 | 병렬 영역 밖에서 선언한 `tid`를 공유해 접근 시점에 따라 값이 변함 |
| `omp_example_05.c` | Race Condition 확인 | `sleep(5)`로 경쟁 상태 유도 → 마지막에 업데이트한 스레드 값으로 모두 출력 |
| `omp_example_06.c` | Race Condition 제거 | 병렬 영역 **내부**에서 변수 선언 → 자동으로 private |
| `omp_example_07.c` | `private` 절 | `private(tid)`로 스레드별 독립 변수 확보 |
| `omp_example_08.c` | `private` 배열 | private 배열은 스레드별 별도 메모리 → 메인 영역 배열에 영향 없음(결과 0) |
| `omp_example_09.c` | `shared` 배열 | `shared(a)`로 배열을 공유 → 각 스레드가 자기 인덱스에 기록, 메인 영역에 반영 |
| `omp_example_10.c` | `firstprivate` | private 변수를 메인 영역 초기값으로 초기화. 병렬 영역 밖 `tid`는 쓰레기 값 |

### 3. Worksharing (작업 분할)

| 파일 | 주제 | 핵심 내용 |
|------|------|-----------|
| `omp_example_11.c` | `for` | 반복문을 스레드에 자동 분배 (`#pragma omp for`) |
| `omp_example_12.c` | `sections` | 서로 다른 코드 블록(`section`)을 스레드에 각각 할당 |
| `omp_example_13.c` | `single` | 팀 중 한 스레드만 실행, 나머지는 암시적 barrier에서 대기 |
| `omp_example_14.c` | `master` | 마스터 스레드만 실행 (암시적 barrier 없음) |

### 4. 동기화 (Synchronization)

| 파일 | 주제 | 핵심 내용 |
|------|------|-----------|
| `omp_example_15.c` | Race Condition | `sum += i`에서 경쟁 상태 → 실행마다 결과 다름 |
| `omp_example_16.c` | `critical` | 임계 영역을 한 번에 하나의 스레드만 실행 (올바른 결과 45) |
| `omp_example_17.c` | `atomic` | 단일 읽기/쓰기 연산 원자적 처리 (`{}` 사용 불가) |
| `omp_example_18.c` | `critical` vs `atomic` 성능 | 1억 회 반복 비교 → atomic(~3.4s)이 critical(~9.3s)보다 빠름 |
| `omp_example_19.c` | `barrier` | 모든 스레드가 barrier에 도달할 때까지 대기 |
| `omp_example_20.c` | `ordered` | 루프는 병렬 실행, 특정 부분은 반복 순서대로 출력 (`for ordered` 필요) |
| `omp_example_21.c` | `nowait` | 암시적 barrier 제거 → 먼저 끝난 스레드는 대기 없이 진행 |
| `omp_example_22.c` / `23.c` | `nowait` 성능 비교 | 독립적인 두 for 루프에서 nowait로 동기화 오버헤드 감소 (`nowait1.x`, `nowait2.x`) |
| `omp_example_24.c` | 내적 Race Condition | 공유 변수 `sum` 누적 시 경쟁 상태 (정답 3080) |
| `omp_example_25.c` | reduction 방법①: 임시 변수 | 스레드별 배열 `c[tid]`에 부분합 후 합산 (`29-1`과 동일 계열) |
| `omp_example_26.c` | reduction 방법②: `critical` | critical로 누적 보호 |
| `omp_example_27.c` | reduction 방법③: `atomic` | atomic으로 누적 보호 |
| `omp_example_28.c` | reduction 방법④: `reduction` | `reduction(+:sum)`으로 스레드별 부분합 자동 결합 (가장 간결·효율적) |
| `omp_example_29.c` | 순차 버전 기준 | 성능 비교용 순차 프로그램. `29-1`~`29-4`는 임시변수/critical/atomic/reduction 병렬 버전 |

### 5. 저 수준 동기화 (Lock)

| 파일 | 주제 | 핵심 내용 |
|------|------|-----------|
| `omp_example_30.c` | Simple Lock | `omp_lock_t` — `omp_init/set/unset/destroy_lock` |
| `omp_example_31.c` | Nested Lock | `omp_nest_lock_t` — 재귀 함수·중첩 임계영역에서 동일 스레드가 반복 획득 |

### 6. 중첩 병렬 & 라이브러리 함수

| 파일 | 주제 | 핵심 내용 |
|------|------|-----------|
| `omp_example_32.c` | 중첩 스레드 생성 | `omp_set_nested(1)`로 병렬 영역 내 병렬 영역 생성 |
| `omp_example_33.c` | 라이브러리 함수 | `omp_get_level()`, `omp_get_ancestor_thread_num()` 등 |
| `omp_example_34.c` | 데이터 유효범위 | 중첩 병렬에서 `private`/`shared` 변수 스코프 동작 확인 |

### 7. 태스크 (Task)

| 파일 | 주제 | 핵심 내용 |
|------|------|-----------|
| `omp_example_35.c` | `task` | `single` 안에서 `#pragma omp task`로 작업 생성 (task 간 동기화 없음) |
| `omp_example_36.c` | `taskwait` | `#pragma omp taskwait`로 하위 task 완료까지 대기 후 진행 |

### 8. 루프 최적화 & False Sharing

| 파일 | 주제 | 핵심 내용 |
|------|------|-----------|
| `omp_example_37.c` | `collapse` | 이중 루프를 `collapse(2)`로 하나로 합쳐 병렬화 |
| `omp_example_38.c` | `collapse` 등가 코드 | `for(i<N*N)` + `a[i/N][i%N]` 로 collapse와 동일한 효과 |
| `omp_example_39.c` | False Sharing | 인접한 `a[tid]`가 같은 캐시라인 공유 → 캐시 일관성 오버헤드로 느려짐(~10s) |
| `omp_example_40.c` | False Sharing 해결 | `a[tid*8]`로 간격을 두어 캐시라인 분리 → 성능 개선(~3.3s) |

---

## 예제 코드

### `omp_example_01.c` — 기본 병렬 영역
```c
#include <stdio.h>
#include <omp.h>

int main() {
#pragma omp parallel
    {
        printf("Hello World %d\n", omp_get_thread_num());
    }
}
```

### `omp_example_28.c` — reduction (권장 방식)
```c
#pragma omp parallel
{
    #pragma omp for reduction(+:sum)
    for(i = 0; i < N; i++)
        sum += a[i] * b[i];
}
```

---

## 컴파일 & 실행

```bash
# 스레드 수 설정
export OMP_NUM_THREADS=8

# 컴파일 (-fopenmp 필수)
gcc omp_example_01.c -fopenmp -o omp_example_01.x

# 실행
./omp_example_01.x

# 성능 측정 예제(39/40 등)는 스택 제한 조정이 필요할 수 있음
ulimit -s 512000
time ./omp_example_40.c.x
```
