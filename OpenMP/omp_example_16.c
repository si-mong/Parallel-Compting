#include <stdio.h>
#include <omp.h>

int main()
{
        int sum = 0;

        #pragma omp parallel for
        for(int i = 0; i < 1000; i++){

                #pragma omp critical
		{
			sum += i;
		}
        }
        printf("sum = %d\n", sum);
        return 0;

}
