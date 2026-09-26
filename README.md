# 병렬 컴퓨팅 (Parallel Computing)

충북대학교 소프트웨어학부 **병렬컴퓨팅** 수업의 실습 자료 모음입니다.
병렬 컴퓨팅의 기본 개념부터 다양한 병렬 프로그래밍 방법론까지, Linux 기반 환경에서
**Pthreads · OpenMP · MPI · CUDA** 등을 직접 구현하며 학습한 내용을 정리했습니다.

---

## 1. 강의 개요

병렬 컴퓨팅의 기본 개념부터 다양한 병렬 프로그래밍 방법론까지 학습합니다.
Linux 기반 환경에서 Pthreads, OpenMP, MPI, CUDA 등을 활용하여 병렬 프로그램을 구현하고,
다양한 병렬 처리 방법과 컴퓨팅 아키텍처를 이해합니다.

## 2. 학습 목표

- 병렬 컴퓨팅의 기본 개념과 원리를 이해한다.
- Pthreads, OpenMP, MPI, CUDA 등 주요 병렬 프로그래밍 기술을 학습한다.
- High Throughput Parallel Processing의 개념과 활용 방법을 이해한다.
- Linux 환경과 NVIDIA GPU를 활용한 병렬 프로그램 구현 경험을 쌓는다.
- 다양한 병렬 컴퓨팅 방법론을 실습하고 병렬 프로그램 구현 역량을 강화한다.

---

## 3. 실습 구성

이 저장소에 정리된 실습별 자료입니다. 각 폴더의 자세한 설명은 폴더 내 `README.md`를 참고하세요.

| 폴더 | 주제 | 내용 |
|------|------|------|
| [Pthreads](./Pthreads) | **POSIX Threads** | pthread 라이브러리로 스레드 생성·관리, Mutex/조건 변수 동기화 (예제 10종) |
| [HTC](./HTC) | **High Throughput Computing** | HTCondor로 VirtualBox 3노드 클러스터 구축 및 작업명세서(jds)로 작업 제출·처리 |
| [OpenMP](./OpenMP) | **OpenMP** | 컴파일러 지시어 기반 공유 메모리 병렬화, 동기화, 성능 최적화 (예제 40종) |
| [MPI](./MPI) | **MPI (OpenMPI)** | 5노드 클러스터에서 메시지 패싱 기반 분산 병렬 — 점대점/집합 통신, 병렬 I/O |
| [강의자료](./강의자료) | **강의/실습 자료** | 개념 슬라이드 및 Lab PDF |

> CUDA, Advanced Architecture, Quantum Parallelism 등 후반부 주제는 학기 진행에 따라 추가될 예정입니다.

## 4. 개념 정리

실습을 하며 생긴 "왜 이렇게 하는가" 질문을 정리한 문서입니다.

- [OpenMP vs Pthreads](./docs/OpenMP-vs-Pthreads.md) — 공유 메모리 병렬화의 고수준/저수준 비교
- [HTCondor vs MPI — 파일 전송 방식과 `/scratch`](./docs/HTCondor-vs-MPI-파일전송.md) — MPI에서만 NFS 공유가 필요했던 이유

---

## 5. 주차별 내용

| 주차 | 내용 | 실습 자료 |
|------|------|-----------|
| 1주차 | Introduction to Parallel Computing | — |
| 2주차 | Pthreads | [Pthreads](./Pthreads) |
| 3주차 | High Throughput Parallel Processing | [HTC](./HTC) |
| 4주차 | OpenMP I | [OpenMP](./OpenMP) |
| 5주차 | OpenMP II | [OpenMP](./OpenMP) |
| 6주차 | MPI I | [MPI](./MPI) |
| 7주차 | MPI II | [MPI](./MPI) |
| 8주차 | 중간고사 | — |
| 9주차 | CUDA I | (예정) |
| 10주차 | CUDA II | (예정) |
| 11주차 | Advanced Parallel Computing Architecture / OpenMP III | (예정) |
| 12주차 | Quantum Parallelism I / MPI III | (예정) |
| 13주차 | Quantum Parallelism II / CUDA III | (예정) |
| 14주차 | Project Presentation | — |
| 15주차 | 기말고사 | — |

---

## 6. 실습 환경

- **호스트**: Ubuntu + Oracle VirtualBox
- **게스트 VM**: Rocky Linux 10 (Virtual Machine)
- **언어/컴파일러**: C/C++ 기반 병렬 프로그래밍, GCC
- **NVIDIA GPU**: CUDA 실습용
- **병렬 프로그래밍 도구**: Pthreads, OpenMP(`libomp-devel`), MPI(OpenMPI), CUDA
- **클러스터 도구**: HTCondor, NFS(노드 간 파일 공유)

### 빠른 시작

```bash
# Pthreads 예제 컴파일 & 실행
cd Pthreads
gcc ex1.c -lpthread -o ex1
./ex1

# OpenMP 예제 컴파일 & 실행
cd OpenMP
gcc omp_example_01.c -fopenmp -o omp_example_01.x
./omp_example_01.x

# MPI 예제 컴파일 & 실행 (OpenMPI)
cd MPI
mpicc mpi_example.c -o mpi_example.x
mpirun -np 4 -hostfile mpi_hosts ./mpi_example.x
```

> HTCondor / MPI 클러스터 구축 및 실행 방법은 각 폴더의 README를 참고하세요.

---

## 7. 주요 학습 내용

- **Pthreads**: 스레드를 활용한 병렬 프로그래밍
- **OpenMP**: 공유 메모리 기반 병렬 프로그래밍
- **MPI**: 분산 메모리 환경에서의 병렬 프로그래밍
- **CUDA**: NVIDIA GPU를 활용한 GPU 병렬 프로그래밍
- **High Throughput Computing**: 높은 처리량을 목표로 하는 병렬 처리
- **Advanced Parallel Computing Architecture**: 병렬 컴퓨팅 아키텍처
- **Quantum Parallelism**: 양자 병렬성의 기본 개념

## 8. 실습 방향

Linux 환경과 NVIDIA GPU를 활용하여 다양한 병렬 프로그래밍 방법을 직접 구현하고 실습합니다.
성능 자체의 개선보다는 각 병렬 컴퓨팅 방법론을 이해하고 적용하는 것에 초점을 둡니다.

---

## 디렉터리 구조

```
병렬컴퓨팅_실습/
├── Pthreads/    # Pthreads 실습 (ex1~ex10)
├── HTC/         # HTCondor 클러스터 실습
├── OpenMP/      # OpenMP 실습 (예제 01~40)
├── MPI/         # MPI 실습 (OpenMPI)
├── docs/        # 개념 정리 문서
└── 강의자료/     # 강의 슬라이드 & Lab PDF
```
