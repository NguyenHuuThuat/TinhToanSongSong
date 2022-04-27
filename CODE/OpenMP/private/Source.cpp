#include <stdio.h>
#include <omp.h>
#include <time.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int main() {
	int id;
	int x = 10;
	int y = 100;
	int z = 100;
	//	omp_set_num_threads(2);
	//#pragma omp parallel
	//	{
	//	#pragma omp for private (i) firstprivate(x) lastprivate (y) reduction(+:z)
	//		for (i = 0; i < 10; i++) 
	//		{
	//			x += 1;
	//			y = x + i;
	//			z = x + i;
	//
	//		}
	//	}
	//	printf("firstPrivate x = %d\n", x);
	//	printf("lastPrivate y = %d\n", y);
	//	printf("Reduction z = %d\n", z);

#pragma omp parallel private(id) num_threads(6)
	{
		id = omp_get_thread_num();
		if ((id % 2) == 0) {
			Sleep(3000);
			printf("Even numbers: %d \n", id);
		}

//#pragma omp barrier
		if ((id % 2) != 0)
			printf("Odd numbers: %d \n", id);
	}

	return 0;
}