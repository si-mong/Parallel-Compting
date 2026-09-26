#include <mpi.h> 
#include <stdio.h>
/* 라이브러리 사용을 위한 헤더 */

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv); /* MPI 환경 초기화 */
	int world_size, world_rank;

	MPI_Comm_size(MPI_COMM_WORLD, &world_size); /* 전체 프로세스 수 얻기 */
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); /* 현재 프로세스의 랭크 얻기 */

	printf("Hello from rank %d out of %d ranks\n", world_rank, world_size);

	MPI_Finalize(); /* MPI 환경 종료 */
	return 0;
}
