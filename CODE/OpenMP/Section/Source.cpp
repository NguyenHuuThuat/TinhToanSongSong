// Section
#include <omp.h>
#include <stdio.h>

int main() {
	omp_set_num_threads(3);
#pragma omp parallel sections

	{
	#pragma omp section
		for (int i = 0; i < 5; i++)
			printf("Hello world form section 1, No thread = %d \n", omp_get_thread_num());
	#pragma omp section
		printf("I'm from section 2, No thread = %d\n", omp_get_thread_num());
	}
}
