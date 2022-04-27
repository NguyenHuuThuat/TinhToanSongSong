#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

/*  WINDOWS

// Function that converts numbers form LongInt type to double type
double LiToDouble(LARGE_INTEGER x) {
	double result =
		((double)x.HighPart) * 4.294967296E9 + (double)((x).LowPart);
	return result;
}

// Function that gets the timestamp in seconds
double GetTime() {
	LARGE_INTEGER lpFrequency, lpPerfomanceCount;
	QueryPerformanceFrequency(&lpFrequency);
	QueryPerformanceCounter(&lpPerfomanceCount);
	return LiToDouble(lpPerfomanceCount) / LiToDouble(lpFrequency);
}

*/


// Function for simple definition of matrix and vector elements
void DummyDataInitialization(double* pMatrix, int Size) {
	int i, j; // Loop variables
	for (i = 0; i < Size; i++) {
		for (j = 0; j < Size; j++)
			pMatrix[i * Size + j] = i;
	}
}

// Function for random definition of matrix and vector elements
// void RandomDataInitialization(double* pMatrix, double* pVector, int Size) {
// 	int i, j; // Loop variables
// 	srand(unsigned(clock()));
// 	for (i = 0; i < Size; i++) {
// 		pVector[i] = rand() / double(1000);
// 		for (j = 0; j < Size; j++)
// 			pMatrix[i * Size + j] = rand() / double(1000);
// 	}
// }

// Function for memory allocation and definition of object’s elements
void ProcessInitialization(double*& pMatrix, double*& pResult, int& Size) {
	// Size of initial matrix and vector definition
	do {
		printf("\nEnter size of the initial objects: ");
		scanf_s("%d", &Size);
		printf("\nChosen objects size = %d\n", Size);
		if (Size <= 0)
			printf("\nSize of objects must be greater than 0!\n");
	} while (Size <= 0);
	// Memory allocation
	pMatrix = new double[Size * Size];
	pResult = new double[Size];
	// Definition of matrix and vector elements
	DummyDataInitialization(pMatrix, Size);
}

// Function for formatted matrix output
void PrintMatrix(double* pMatrix, int RowCount, int ColCount) {
	int i, j; // Loop variables
	for (i = 0; i < RowCount; i++) {
		for (j = 0; j < ColCount; j++)
			printf("%7.4f ", pMatrix[i * RowCount + j]);
		printf("\n");
	}
}

// Function for formatted vector output
void PrintVector(double* pVector, int Size) {
	int i;
	for (i = 0; i < Size; i++)
		printf("%7.4f ", pVector[i]);
}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void SerialResultCalculation(double* pMatrix, double* pResult, int Size)
{
	int i, j;
	for (j = 0; j < Size; j++)
	{
		pResult[j] = pMatrix[j];
		for (i = 0; i < Size; i++)
		{
			if (pMatrix[i * Size + j] > pResult[j])
				pResult[j] = pMatrix[i * Size + j];
		}
	}
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
double ParallelResultCalculation(double* pMatrix, double* pResult, int Size)
{
	int i, j;
	double Result = 0;

#pragma omp parallel for private(i) shared (Result)
	for (j = 0; j < Size; j++)
	{
		pResult[j] = pMatrix[j];
		for (i = 0; i < Size; i++)
		{
			if (pMatrix[i * Size + j] > pResult[j])
				pResult[j] = pMatrix[i * Size + j];
		}
		Result += pResult[j];
	}

	return Result / (double)Size;
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void TestResult(double* pMatrix, double* pResult, int Size)
{
	// Buffer for storing the result of serial matrix-vector multiplication
	double* pSerialResult;
	int equal = 0; // Flag, that shows wheather the vectors are identical
	int i; // Loop variable
	pSerialResult = new double[Size];
	SerialResultCalculation(pMatrix, pSerialResult, Size);
	for (i = 0; i < Size; i++) {
		if (pResult[i] != pSerialResult[i])
			equal = 1;
	}
	if (equal == 1)
		printf("The results of serial and parallel algorithms "
			"are NOT identical. Check your code.\n");
	else
		printf("The results of serial and parallel algorithms are "
			"identical.\n");
	delete[] pSerialResult;
}

// Function for computational process termination
void ProcessTermination(double* pMatrix, double* pResult) {
	delete[] pMatrix;
	delete[] pResult;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Khởi tạo dữ liệu giả 
void DummyDataInitialization(double* pMatrix, int Row, int Col) {
	int i, j;  // Loop variables
	for (i = 0; i < Row; i++) {
		for (j = 0; j < Col; j++)
			pMatrix[i * Row + j] = 3 + rand() % 20;
	}
}

void ProcessInitialization(double*& pMatrix, int& Row, int& Col) {
	// row and col  of initial matrix and vector definition
	do {
		printf("\nEnter row of the initial objects: ");
		scanf_s("%d", &Row);
		printf("\nChosen objects row= %d\n", Row);
		if (Row <= 0)printf("\nRow of objects must be greater than 0!\n");
	} while (Row <= 0);

	do {
		printf("\nEnter Colum of the initial objects: ");
		scanf_s("%d", &Col);
		printf("\nChosen objects Colum= %d\n", Col);
		if (Col <= 0)printf("\nColume of objects must be greater than 0!\n");
	} while (Col <= 0);

	//khởi tạo ma trận theo kích thước nhập vào
	pMatrix = new double[Row * Col];

	// Definition of matrix and vector elements
	DummyDataInitialization(pMatrix, Row, Col);
}

////in ma trận kích thước bất kỳ *
//void PrintMatrix(double* pMatrix, int RowCount, int ColCount) {
//	int i, j; // Loop variables
//	for (i = 0; i < RowCount; i++) {
//		for (j = 0; j < ColCount; j++)
//			printf("%7.4f ", pMatrix[i * RowCount + j]);
//		printf("\n");
//	}
//}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



int main() {
	double* pMatrix; // The first argument - initial matrix
	double* pResult; // Result vector for matrix-vector multiplication
	int Size; // Sizes of initial matrix and vector
	double Start, Finish, Duration;
	double Result;
	double* pVector;  // The second argument -initial vector
	int Row;// Sizes of initial matrix and vector
	int Col;

	printf("Parallel matrix-vector multiplication program\n");
	// Memory allocation and definition of objects' elements
	ProcessInitialization(pMatrix, pResult, Size);
	// Matrix and vector output
	printf("Initial Matrix \n");
	// PrintMatrix(pMatrix, Size, Size);

	// Matrix-vector multiplication
	Start = omp_get_wtime();
	Result = ParallelResultCalculation(pMatrix, pResult, Size);
	Finish = omp_get_wtime();
	Duration = Finish - Start;
	TestResult(pMatrix, pResult, Size);

	// Printing the time spent by matrix-vector multiplication
	// PrintVector(pResult, Size);
	printf("\nResult = %f\n", Result);
	// Printing the time spent by matrix-vector multiplication
	printf("\n Time of execution: %f\n", Duration);
	// Computational process termination
	ProcessTermination(pMatrix, pResult);

	return 0;
}
