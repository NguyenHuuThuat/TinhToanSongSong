#include <stdio.h>
#include <omp.h>

int main() {
	int i;
	omp_set_num_threads(10);
	#pragma omp parallel for ordered private(i)

	for (i = 0; i < 10; i++) {
#pragma omp ordered
		printf("i = %d in Thread: %d Hello world: \n", i, omp_get_thread_num());
	}
	return 0;
}