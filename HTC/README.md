# HTCondor 클러스터 실습

병렬컴퓨팅 수업의 **HTC(High-Throughput Computing)** 실습 자료입니다.
VirtualBox 위에 Rocky Linux 가상머신 3대로 HTCondor 클러스터를 구축하고,
작업명세서(Job Description File)를 작성해 클러스터에 작업을 제출·처리하는 과정을 다룹니다.

> 참고 강의자료: `강의자료/Lab-HTC-01.pdf`(클러스터 생성), `Lab-HTC-02.pdf`(클러스터 구축), `Lab-HTC-03.pdf`(작업 처리)

---

## 클러스터 구성

Ubuntu 호스트에서 VirtualBox로 Rocky Linux VM 3대를 복제해 구성합니다.
호스트 전용 네트워크(`vboxnet0`, `192.168.56.1/24`)의 `enp0s8` 인터페이스로 노드 간 통신합니다.

| 역할 | 호스트네임 | IP | HTCondor 역할 |
|------|-----------|-----|--------------|
| main | `main.supercom.org` | 192.168.56.101 | Central Manager + Submit |
| work #1 | `work1.supercom.org` | 192.168.56.102 | Execute |
| work #2 | `work2.supercom.org` | 192.168.56.103 | Execute |

### 구축 요약

1. **가상머신 복제** — `VBoxManage clonevm "Rocky Linux" --name "Work1" --register` (또는 GUI Clone, Full Clone + MAC 재생성)
2. **네트워크 설정** — 각 노드의 `/etc/hostname`, `/etc/hosts`, `/etc/NetworkManager/system-connections/enp0s8.nmconnection`(고정 IP) 수정 후 재부팅
3. **통신 확인** — `ping`으로 노드 간 연결 테스트
4. **HTCondor 설치**
   - main: `curl -fsSL https://get.htcondor.org | sudo GET_HTCONDOR_PASSWORD="htcondor" /bin/bash -s -- --no-dry-run --central-manager main.supercom.org`
   - work1/2: `... --execute main.supercom.org`
5. **방화벽 비활성화** — `sudo systemctl stop firewalld && sudo systemctl disable firewalld`
6. **설정 파일 작성** — `/etc/condor/config.d/condor_config.local`
   ```
   UID_DOMAIN = <노드 도메인>
   ALLOW_WRITE = *.supercom.org
   CONDOR_HOST = main.supercom.org
   NETWORK_INTERFACE = enp0s8
   ```
   main 노드는 `01-central-manager.config`에 `use role:get_htcondor_submit` 추가
7. **서비스 시작** — `sudo systemctl enable condor && sudo systemctl restart condor`
8. **클러스터 확인** — `condor_status` (work1, work2가 `Unclaimed / Idle` 로 표시되면 성공)

> `etc/` 디렉터리에 실습 중 사용한 `hostname`, `hosts`, `enp0s8.nmconnection` 설정 파일 예시가 들어 있습니다.

---

## 작업명세서(Job Description File) 기본 구조

```
executable = <실행 파일>
universe   = <실행 환경: vanilla | standard | parallel | java | vm ...>
input      = <입력 데이터>
output     = <표준출력 기록 파일>
error      = <표준에러 기록 파일>
log        = <작업 로그 파일>
queue [실행 개수]
```

주요 명령어
- `condor_submit <file.jds>` : 작업 제출
- `condor_q` : 큐 확인 (`-nobatch`, `-analyze <jobid>`)
- `condor_status` : 워커노드/슬롯 상태 확인 (`-l`, `-compact`)
- `condor_rm <jobid>` : 작업 삭제

---

## 실습 예제 (`main/`)

단계별로 작업명세서 기능을 확장해가는 예제들입니다. 각 폴더에는 실행 스크립트, `.jds`, 그리고 실행 결과(`out.txt`, `error.txt`, `log.txt`)가 함께 들어 있습니다.

| 디렉터리 | 주제 | 핵심 내용 |
|----------|------|-----------|
| `01.date` | 간단한 작업 | `date.sh`(현재 시각 출력 → `sleep 10` → 다시 출력)를 `vanilla` universe로 제출하는 가장 기본적인 예제 |
| `02.argument` | 인자를 갖는 작업 | `count.sh`에 `arguments = 1 10`을 전달해 1~10 합(=55)을 계산 |
| `03.multiple` | 여러 작업 동시 실행 (문제 상황) | `queue 10`으로 10개 작업 제출. **모든 작업이 같은 `out/error/log` 파일에 기록**되어 결과가 덮어써지는 문제 확인 |
| `04.multiple` | 디렉터리 분리 | `initialdir = run_1 / run_2`로 작업별 작업 디렉터리를 분리해 결과 충돌 해결. `read.sh`는 `file.txt`를 한 줄씩 출력 |
| `05.multiple` | 파일 이름 분리 | `output = out.$(Process).txt` 처럼 `$(Process)`(작업 번호)를 파일명에 넣어 결과를 분리 (`queue 10`) |
| `06.multiple` | `$(Process)` + 디렉터리 분리 | `initialdir = run_$(Process)`로 작업별 디렉터리를 자동 지정 (`queue 2`) |
| `07.requirement` | 요구사항을 갖는 작업 | `requirements`로 실행 노드 조건 지정. `req-error.jds`는 `Arch == "INTEL"`로 매칭 실패(작업이 Idle 상태로 멈춤), `requirement.jds`는 `Arch == "X86_64"`로 정상 실행. `condor_status -l | grep Arch`로 실제 스펙(`X86_64`) 확인 |

### 예: `count.sh` (인자로 받은 범위의 합 계산)
```bash
#!/bin/bash
NUM_START=$1
NUM_END=$2
LOOP_COUNT=$NUM_START
SUM=0
echo "Sum from $NUM_START to $NUM_END"
while [ $LOOP_COUNT -le $NUM_END ]; do
    SUM=`expr $SUM + $LOOP_COUNT`
    LOOP_COUNT=`expr $LOOP_COUNT + 1`
done
echo "Total Sum = $SUM"
```

### 트러블슈팅 메모
- 실행 스크립트에 `#!/bin/bash` 누락 시 `Execution format error`
- Bash 변수 대입 시 `=` 앞뒤 공백 제거
- 파일을 root로 생성하면 permission error 발생 가능
- 작업 실행 시간이 너무 짧으면 `condor_q`로 보기 전에 종료됨
- `condor_ssh_to_job <jobid>`로 실행 중인 작업 노드에 접속 가능

> POSIX Threads(pthread) 실습은 별도 폴더(`../Pthreads`)로 분리되어 있습니다.

---

## 디렉터리 구조

```
HTC/
└── main/
    ├── 01.date ~ 07.requirement/   # HTCondor 작업 예제 (jds + 스크립트 + 결과)
    └── etc/                        # 노드 네트워크/호스트 설정 파일 예시
```
