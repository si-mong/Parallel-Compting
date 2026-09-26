#include <stdio.h>
#include <omp.h>
#define NUM_ITER 100000000
int main() {
	int sum = 0;
	double start, end;

	/* ------------------ atomic test ------------------ */
	sum = 0;
	start = omp_get_wtime();

	#pragma omp parallel for
	for(int i = 0; i < NUM_ITER; i++) {
		#pragma omp atomic
		sum += 1;
	}

	end = omp_get_wtime();
	printf("Atomic result: %d\n", sum);
	printf("Atomic time: %f seconds\n\n", end - start);

	/* ------------------ critical test ------------------ */
	sum = 0;
	start = omp_get_wtime();

	#pragma omp parallel for
	for(int i = 0; i < NUM_ITER; i++) {
		#pragma omp critical
		{
			sum += 1;
		}
	}
	end = omp_get_wtime();
	printf("Critical result: %d\n", sum);
	printf("Critical time: %f seconds\n", end - start);

	return 0;
}

