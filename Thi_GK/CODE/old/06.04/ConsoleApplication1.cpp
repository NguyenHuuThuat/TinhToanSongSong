
#include <stdio.h>
#include<conio.h>
#include<stdlib.h>
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
	} 	while (Row <= 0);

	do {
		printf("\nEnter Colum of the initial objects: ");
		scanf_s("%d", &Col);
		printf("\nChosen objects Colum= %d\n", Col);
		if (Col <= 0)printf("\nColume of objects must be greater than 0!\n");
	} 	while (Col <= 0);

	//khởi tạo ma trận theo kích thước nhập vào
	pMatrix = new double[Row * Col];

	// Definition of matrix and vector elements
	DummyDataInitialization(pMatrix, Row, Col);
}

//in ma trận
void PrintMatrix(double* pMatrix, int RowCount, int ColCount) {
	int i, j; // Loop variables
	for (i = 0; i < RowCount; i++) {
		for (j = 0; j < ColCount; j++)
			printf("%7.4f ", pMatrix[i * RowCount + j]);
		printf("\n");
	}
}

int main()
{
	double* pMatrix;  // The first argument -initial matrix
	double* pVector;  // The second argument -initial vector
	double* pResult;  // Result vector for matrix-vector multiplication 
	int Row;// Sizes of initial matrix and vector
	int Col;
	ProcessInitialization(pMatrix, Row, Col);
	PrintMatrix(pMatrix, Row, Col);
}
