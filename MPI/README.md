# MPI 실습 (OpenMPI)

병렬컴퓨팅 수업의 **MPI(Message Passing Interface)** 실습 자료입니다.
여러 노드(프로세스)가 메시지를 주고받으며 협력하는 분산 메모리 병렬 프로그래밍을 다룹니다.
점대점 통신부터 집합 통신, 동기화, 병렬 파일 I/O까지 단계별 예제로 구성됩니다.

> 참고 강의자료: `강의자료/Lab-MPI.pdf`
> 실습은 NFS로 공유한 작업 디렉터리(`/scratch`)에서 컴파일·실행합니다.

---

## 실습 환경

VirtualBox 위에 Rocky Linux VM **5대**(main + work1~4)로 클러스터를 구성하고,
OpenMPI로 노드 간 병렬 작업을 수행합니다.

| 역할 | 호스트네임 | IP |
|------|-----------|-----|
| main (NFS 서버, 컴파일/실행) | `main.supercom.org` | 192.168.56.101 |
| work #1 | `work1.supercom.org` | 192.168.56.102 |
| work #2 | `work2.supercom.org` | 192.168.56.103 |
| work #3 | `work3.supercom.org` | 192.168.56.104 |
| work #4 | `work4.supercom.org` | 192.168.56.105 |

### 구축 요약

1. **VM 준비** — Clean Rocky Linux VM을 복제(main, work1~4), 호스트네임/IP/`/etc/hosts` 설정, 방화벽 비활성화
2. **패스워드 없는 SSH** — main에서 `ssh-keygen` 후 `ssh-copy-id`로 work 노드에 공개키 배포
3. **NFS 공유** — main에 `/scratch`를 NFS 서버로 export(`/etc/exports`), work 노드는 `/etc/fstab`으로 마운트 → 모든 노드가 `/scratch`를 공유
4. **OpenMPI 설치** — 모든 노드에 소스 빌드(`./configure --prefix=... && make all install`), `PATH`/`LD_LIBRARY_PATH` 등록. 버전 5.0.9 확인

### 컴파일 & 실행

```bash
# main 노드의 /scratch 디렉터리에서 진행 (NFS로 모든 노드가 공유)
cd /scratch

# 컴파일
mpicc mpi_example.c -o mpi_example.x

# 실행 (-np: 프로세스 수, -hostfile: 실행할 노드 목록)
mpirun -np 4 -hostfile mpi_hosts ./mpi_example.x
```

`mpi_hosts` 파일은 프로세스를 실행할 계산 노드를 지정합니다.
```
work1 slots=1
work2 slots=1
work3 slots=1
work4 slots=1
```

### MPI 기본 뼈대

```c
#include <mpi.h>
MPI_Init(&argc, &argv);                       /* MPI 환경 초기화 */
MPI_Comm_size(MPI_COMM_WORLD, &size);         /* 전체 프로세스 수 */
MPI_Comm_rank(MPI_COMM_WORLD, &rank);         /* 현재 프로세스 랭크 */
/* ... 통신/계산 ... */
MPI_Finalize();                               /* MPI 환경 종료 */
```

---

## 예제 목록

파일명 앞의 번호는 실습 진행 순서입니다.

### 1. 기초

| 파일 | 주제 | 핵심 내용 |
|------|------|-----------|
| `mpi_example.c` | Hello (rank/size) | `MPI_Comm_rank`/`MPI_Comm_size`로 랭크·전체 프로세스 수 출력 |
| `02-hello_host.c` | Hello + 호스트명 | `MPI_Get_processor_name`, `MPI_Get_version`으로 실행 노드·MPI 버전 확인 |
| `03-mpi_calfun.c` | 함수 값 계산 | 랭크를 x값으로 사용해 각 프로세스가 `y = x²+x+1`을 병렬 계산 |

### 2. 점대점 통신 (Point-to-Point)

| 파일 | 주제 | 핵심 내용 |
|------|------|-----------|
| `04-send_recv.c` | `MPI_Send`/`MPI_Recv` | 블로킹 송수신, `MPI_ANY_SOURCE`, `MPI_Get_count`로 수신 개수 확인 |
| `05-ping_pong.c` | Ping-Pong | 두 프로세스가 값을 주고받음. 프로세스 수가 안 맞으면 대기(교착)하는 상황 관찰 |
| `06-summation.c` | 합산 | 각 프로세스의 계산값을 rank 0이 `MPI_Recv`로 모아 평균 계산 |
| `06-mpi_proc_null.c` | `MPI_PROC_NULL` | 더미 대상으로의 통신(실제 동작 없음) — 경계 처리 단순화 |
| `07-waitall.c` | 논블로킹 + `Waitall` | `MPI_Isend`/`MPI_Irecv`로 비동기 통신 후 `MPI_Waitall`로 일괄 완료 대기 |
| `08-deadlock.c` | 교착 상태 | 양쪽이 먼저 `MPI_Send`를 호출해 발생하는 deadlock 재현 |
| `09-mpi_sendrecv.c` | `MPI_Sendrecv` | 송신·수신을 한 번에 처리해 교착 방지 (링 형태 통신) |
| `10-mpi_sendrecv_replace.c` | `MPI_Sendrecv_replace` | 하나의 버퍼로 송수신을 동시에 수행 |

### 3. 집합 통신 (Collective)

| 파일 | 주제 | 핵심 내용 |
|------|------|-----------|
| `11-mpi_bcast.c` | `MPI_Bcast` / `MPI_Ibcast` | 한 프로세스의 데이터를 전체에 브로드캐스트 (블로킹/논블로킹+`MPI_Wait`) |
| `13-mpi_gather.c` | `MPI_Gather` | 각 프로세스 데이터를 root로 모음. `MPI_IN_PLACE` 활용 |
| `14-mpi_gatherv.c` | `MPI_Gatherv` | 프로세스마다 크기가 다른 데이터를 모음 (`recvcounts`, `displs`) |
| `15-mpi_allgather.c` | `MPI_Allgather` | Gather 결과를 모든 프로세스가 공유 |
| `16-mpi_allgatherv.c` | `MPI_Allgatherv` | 가변 크기 Allgather |
| `17-mpi_scatter.c` | `MPI_Scatter` | root의 데이터를 각 프로세스에 분배. `MPI_IN_PLACE` 활용 |
| `18-mpi_scatterv.c` | `MPI_Scatterv` | 프로세스마다 다른 크기로 분배 |
| `19-mpi_reduce.c` | `MPI_Reduce` | 각 프로세스 값을 `MPI_SUM` 등으로 축약해 root에 저장 |
| `20-mpi_alltoall.c` | `MPI_Alltoall` | 모든 프로세스가 서로 데이터를 교환(전치) |
| `21-mpi_alltoallv.c` | `MPI_Alltoallv` | 가변 크기 Alltoall (`sendcounts`/`recvcounts`/`displs`) |
| `22-mpi_reduce_scatter.c` | `MPI_Reduce_scatter` | 축약 후 결과를 가변 크기로 분배 |
| `23-mpi_reduce_scatter_block.c` | `MPI_Reduce_scatter_block` | 축약 후 균등 블록으로 분배. `MPI_IN_PLACE` 활용 |

### 4. 동기화

| 파일 | 주제 | 핵심 내용 |
|------|------|-----------|
| `24-mpi_barrier.c` | `MPI_Barrier` | 모든 프로세스가 도달할 때까지 대기 (rank 0에 의도적 지연) |

### 5. 파일 접근 (File I/O)

| 파일 | 주제 | 핵심 내용 |
|------|------|-----------|
| `25-mpi_posix_race.c` | POSIX I/O Race Condition | 여러 프로세스가 동기화 없이 같은 파일 위치에 write → 결과가 덮어써짐(`race_file.txt`) |
| `26-mpi_shared_io.c` | MPI-IO 병렬 I/O | `MPI_File_write_at`으로 rank별 offset에 안전하게 병렬 쓰기(`shared_file.txt`) |

---

## 그 외 파일

- `mpi_hosts` — MPI 실행 노드 목록(호스트 파일)
- `*.x`, `a.out` — 컴파일된 실행 바이너리 (`.gitignore`로 제외)
- `race_file.txt`, `shared_file.txt` — 파일 I/O 예제 실행 결과
- `work1.txt` ~ `work4.txt` — NFS 공유 동작 확인용 테스트 파일
