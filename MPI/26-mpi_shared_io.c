#include <mpi.h>
#include <stdio.h>
#include <string.h>

#define FILENAME "shared_file.txt"
#define BUF_SIZE 128

int main(int argc, char *argv[])
{
    int rank, size;
    MPI_File fh;
    MPI_Status status;

    char write_buf[BUF_SIZE];
    char read_buf[BUF_SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // 각 프로세스가 쓸 문자열 생성
    snprintf(write_buf, BUF_SIZE,
             "Hello from rank %d out of %d processes\n", rank, size);

    // [MPI-IO] 모든 프로세스가 공동으로 접근할 공유 파일을 개방
    MPI_File_open(MPI_COMM_WORLD,
                  FILENAME,
                  MPI_MODE_CREATE | MPI_MODE_RDWR,
                  MPI_INFO_NULL,
                  &fh);

    // 각 랭크별로 겹치지 않는 고유한 파일 오프셋 영역 계산 (Race Condition 방지)
    MPI_Offset offset = rank * BUF_SIZE;
    
    // 계산된 고유 오프셋 위치에 데이터 안전하게 쓰기
    MPI_File_write_at(fh, offset, write_buf, strlen(write_buf),
                      MPI_CHAR, &status);

    // 모든 프로세스가 쓰기 작업을 완료할 때까지 대기
    MPI_Barrier(MPI_COMM_WORLD);

    // 파일의 자신의 오프셋 위치에서 데이터를 다시 읽어오기
    MPI_File_read_at(fh, offset, read_buf, BUF_SIZE,
                     MPI_CHAR, &status);

    printf("Rank %d read: %s", rank, read_buf);

    // MPI 파일 닫기 및 종료
    MPI_File_close(&fh);
    MPI_Finalize();
    return 0;
}
