#include <stdio.h>
#include <omp.h>
#include <conio.h>

int main() {
	int nthreads, tid;
//#pragma omp parallel private(nthreads, tid)
	omp_set_num_threads(11);
#pragma omp parallel
	//{
	//	/*int tid = omp_get_thread_num();
	//	if (tid == 0) 
	//	{
	//		int nthreads = omp_get_num_threads();
	//		printf("Number of thread = %d \n", nthreads);
	//	}*/
	//}
	//_getch();
	printf("Hello! threads %d\n", omp_get_thread_num());
}