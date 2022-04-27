#include <stdio.h>
#include <omp.h>

int main() {
#pragma parallel omp num_thread(4);
	{
#pragma omp master
		printf("Thread: %d Hello world!\n", omp_get_thread_num());
	}
	return 0;
}