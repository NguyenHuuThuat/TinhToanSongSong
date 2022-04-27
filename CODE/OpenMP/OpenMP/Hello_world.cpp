#include <omp.h>
#include<stdio.h>

void main(){
#pragma omp parallel
	printf("[%d] Hello world \n", omp_get_thread_num());
}