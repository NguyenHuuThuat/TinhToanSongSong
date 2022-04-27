#include<omp.h>
#include<stdio.h>
#include<conio.h>

void main()
{
	int i;
	omp_set_num_threads(10);
#pragma omp parallel
#pragma omp for
	for (i = 0; i < 100; i++)
		printf("[%d] Hellow world, No thread = %d \n", omp_get_thread_num(), i);
	_getch();
}