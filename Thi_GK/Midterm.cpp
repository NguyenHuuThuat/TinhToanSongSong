/*
INPUT:  Matrix of m rows, n cols
OUTPUT: The average value of each column's highest value for all columns of the input matrix

Ex: Given a 3x3 matrix such as:
        [ 100   200  300
          400   200  500
          100   900  100 ]
--> the highest value of each column respectively: 400, 900, 500
    --> the expected result of the calculation: (400 + 900 + 500) / 3 = 600
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

/*  CONSTANTS  */
constexpr auto NUM_THREADS = 8;

/*  FUNCTION DECLARATIONS  */
// Memory allocation and definition of objects' elements
void ProcessInitialization(double*& Matrix, double*& tempResults, int& Row, int& Col);
// Generating random values for the input matrix
void DummyDataInitialization(double* Matrix, int Row, int Col);
// Calculations
double SerialResultCalculation(double* Matrix, double*& tempResults, int Row, int Col);
double ParallelResultCalculation(double* Matrix, double* tempResults, int Row, int Col);
// Extra Parallel function using only one parallel code block
double xParallelResultCalculation(double* Matrix, double* tempResults, int Row, int Col);
// Function for computational process termination
void ProcessTermination(double* Matrix, double* tempResults);


int main() {
    /*  DECLARE VARIABLES */
    int Row, Col;          // # of Rows and Columns of the input matrix
    double* Matrix;        // Matrix input
    double* tempResults;   // Vector to store intermediate results
    double ParallelResult; // result calculated by Parallel algorithm
    double SerialResult;   // Result calculated by Serial algorithm

    /*  INIT  */
    omp_set_num_threads(NUM_THREADS);
    printf("Parallel matrix-vector multiplication program\n");
    ProcessInitialization(Matrix, tempResults, Row, Col);

    /*  PARALLEL EXECUTION  */
    auto pStart = high_resolution_clock::now();
    ParallelResult = xParallelResultCalculation(Matrix, tempResults, Row, Col);
    auto pFinish = high_resolution_clock::now();
    auto pDuration = duration_cast<microseconds>(pFinish - pStart);

    /*  TEST RESULT WITH A SERIAL ALGORITHM  */
    auto sStart = high_resolution_clock::now();
    SerialResult = SerialResultCalculation(Matrix, tempResults, Row, Col);
    auto sFinish = high_resolution_clock::now();
    auto sDuration = duration_cast<microseconds>(sFinish - sStart);

    /*  PRINT RESULT  */
    // Printing serial and parallel results
    printf("Serial Result = %lf\n", SerialResult);
    printf("Parallel Result = %lf\n", ParallelResult);
    // Printing the time spent by the calculations
    cout << "Time of parallel execution: " << pDuration.count() << " microseconds" << endl;
    cout << "Time of serial execution: " << sDuration.count() << " microseconds" << endl;

    /* COMPUTATIONAL PROCESS TERMINATION */
    ProcessTermination(Matrix, tempResults);
    return 0;
}

/*  FUNCTION DEFINITIONS  */

void DummyDataInitialization(double* Matrix, int Row, int Col)
{
    int i, j;
    srand(unsigned(clock()));
    for (i = 0; i < Row; i++)
    {
        for (j = 0; j < Col; j++)
            Matrix[i * Col + j] = 3.0 + rand() % 2000000;   // Using random number for matrix elements
    }
}

void ProcessInitialization(double*& Matrix, double*& tempResults, int& Row, int& Col)
{
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

    // Declare matrix and tempResults array
    Matrix = new double[Row * Col];
    tempResults = new double[Col];

    // Initialize matrix elements
    DummyDataInitialization(Matrix, Row, Col);
}

double SerialResultCalculation(double* Matrix, double*& tempResults, int Row, int Col)
{
    int i, j;
    double result = 0;

    for (j = 0; j < Col; j++)
    {
        tempResults[j] = Matrix[j];
        for (i = 0; i < Row; i++)
        {
            if (Matrix[i * Col + j] > tempResults[j])
                tempResults[j] = Matrix[i * Col + j];
        }
        result += tempResults[j] / Col;
    }

    return result;
}

double ParallelResultCalculation(double* Matrix, double* tempResults, int Row, int Col)
{
    int i, j;
    double sum[NUM_THREADS] = { 0.0 };
    double result = 0.0;

    // get largest number of each column, store in tempResults
#pragma omp parallel for private(i)
    for (j = 0; j < Col; j++)
    {
        tempResults[j] = Matrix[j];
        for (i = 0; i < Row; i++)
        {
            if (Matrix[i * Col + j] > tempResults[j])
                tempResults[j] = Matrix[i * Col + j];
        }
    }

#pragma omp parallel
    {
        int i, nthreads;
        nthreads = omp_get_num_threads();

        for (i = omp_get_thread_num(); i < Col; i += nthreads)
            sum[omp_get_thread_num()] += tempResults[i];
    }

    for (i = 0; i < NUM_THREADS; i++)
        result += sum[i];

    return result / Col;
}

double xParallelResultCalculation(double* Matrix, double* tempResults, int Row, int Col)
{
    int i, j, nthreads;
    double Result[NUM_THREADS] = { 0.0 };
    double result = 0;

#pragma omp parallel private(i, j)
    {
        nthreads = omp_get_num_threads();
        for (j = omp_get_thread_num(); j < Col; j += nthreads)
        {
            tempResults[j] = Matrix[j];
            for (i = 0; i < Row; i++)
            {
                if (Matrix[i * Col + j] > tempResults[j])
                    tempResults[j] = Matrix[i * Col + j];
            }
            Result[omp_get_thread_num()] += tempResults[j];
        }
    }

    for (i = 0; i < NUM_THREADS; i++)
    {
        result += Result[i] / Col;
    }

    return result;
}

void ProcessTermination(double* Matrix, double* tempResults) {
    delete[] Matrix;
    delete[] tempResults;
}
