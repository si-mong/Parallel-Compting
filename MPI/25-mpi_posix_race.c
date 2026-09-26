#include <mpi.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define FILENAME "race_file.txt"

int main(int argc, char *argv[])
{
    int rank, size;
    int fd;
    char buf[128];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // 모든 프로세스가 동일한 파일을 쓰기 전용으로 열기
    fd = open(FILENAME, O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        perror("open");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // 각 프로세스가 쓸 문자열 생성
    snprintf(buf, sizeof(buf), "Rank %d writing without synchronization\n", rank);

    // 모든 프로세스가 동기화 없이 파일의 맨 처음(0) 위치로 오프셋을 이동 (경쟁 상태 원인)
    lseek(fd, 0, SEEK_SET);

    // 마이크로초 단위로 타이밍을 어긋나게 하여 경쟁 상태를 시각적으로 유도
    usleep((rank + 1) * 10000);

    // 파일에 데이터 쓰기 (동기화가 없으므로 늦게 쓴 프로세스의 내용이 이전 내용을 덮어씀)
    write(fd, buf, strlen(buf));

    close(fd);
    MPI_Finalize();
    return 0;
}
