#include <omp.h>
#include <stdio.h>
#include <conio.h>

// global 
static int a = 10;


void f()
{
	printf("in subproc f %d \n", a);
}

void f1(int x) 
{
	printf("in subproc f1 %d \n", x);
}

void main() {
#pragma omp parallel private(a)
	{
		a = omp_get_thread_num();
		f();
		f1(a);
	}
	printf("a = %d", a);
	_getch();

}