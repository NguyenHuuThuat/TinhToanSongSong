#include <omp.h>
#include <stdio.h>

void main()
{
	int i;
#pragma omp parallel for
	for (i = 0; i < 12; i++)
	{
		printf("[%d] Hello World =%d \n", omp_get_thread_num(), i);
	}
}