
#include <iostream>
#include "Matrix.h"

using namespace std;

SparseMatrix::SparseMatrix()
{
	rows = cols = terms = capacity = 0;
	a = NULL;
	SmArray = NULL;
}

SparseMatrix::~SparseMatrix()
{
	for (int i = 0; i < rows; i++)
		delete[] a[i];
	delete[] a;
	delete[] SmArray;
}

void SparseMatrix::operator=(SparseMatrix input)
{
	rows = input.rows;
	cols = input.cols;
	terms = input.terms;
	capacity = input.capacity;
	
	a = new int* [input.rows];
	for (int i = 0; i < input.cols; i++)
		a[i] = new int[input.cols];


	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			a[i][j] = input.a[i][j];
		}
	}

	SmArray = new MatrixTerm[input.capacity];
	for (int i = 0; i < input.capacity; i++)
	{
		SmArray[i].row = input.SmArray[i].row;
		SmArray[i].col = input.SmArray[i].col;
		SmArray[i].val = input.SmArray[i].val;
	}
}

SparseMatrix::SparseMatrix(int b)
{
	cout << __FUNCTION__ << endl;
	//system("pause");
	rows = cols = b;
	terms = 0;
	capacity = 0;

	a = new int* [rows];
	for (int i = 0; i < cols; i++)
		a[i] = new int[cols];
	SmArray = NULL;
}

SparseMatrix::SparseMatrix(int ro, int col, int term)
{
	rows = ro;
	cols = col;
	terms = capacity = term;
	SmArray = new MatrixTerm[capacity];
	a = new int* [rows];
	for (int i = 0; i < cols; i++)
		a[i] = new int[cols];
}

/*
* Populates matrix values randomly.
*/
void SparseMatrix::initialize()
{
	/*It will insuare that sparse Matrix have 10% terms*/
	long Cterms = 0;
	Cterms = (rows * cols) * .1;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (terms > Cterms)
			{
				a[i][j] = 0;
			}
			else
			{
				a[i][j] = rand() % 10;
				if (a[i][j] != 0)
					terms++;
			}
		}
	}
	
	cout << "Printing Initialized Matrix." << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << "\n\n" << endl;
	capacity = terms;
	
	/* It stores index for sparse Matrix when populating.*/
	long count = 0;
	SmArray = new MatrixTerm[capacity];
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (a[i][j] != 0)
			{
				SmArray[count].row = i;
				SmArray[count].col = j;
				SmArray[count].val = a[i][j];
				count++;
			}
		}
	}
}

/*
* It is a conventional way of getting a transpose matrix.
* This function returns the transpose in a new variable, keeping current matrix unchanged.
*/
void SparseMatrix::Transpose1(SparseMatrix* transpose)
{
	/* cout << "Showing Result of Algo 1" << endl;*/
	cout << "Running " << __FUNCTION__ << endl;
	/* SparseMatrix b(rows, cols, terms);*/
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			transpose->a[i][j] = a[j][i];
		}
	}
	cout << "Exiting " << __FUNCTION__ << endl;
	return;
}

/*
* This method has same complexity of conventional method.
* This function returns the transpose in a new variable, keeping current matrix unchanged.
*/
void SparseMatrix::Transpose2(SparseMatrix* transpose)
{
	cout << "Running " << __FUNCTION__ << endl;
	long b = 0;
	for (int c = 0; c < cols; c++)
	{
		for (long i = 0; i < terms; i++)
		{
			if (SmArray[i].col == c)
			{
				transpose->SmArray[b].row = c;
				transpose->SmArray[b].col = SmArray[i].row;
				transpose->SmArray[b].val = SmArray[i].val;
				b++;
			}
		}
	}
	cout << "Exiting " << __FUNCTION__ << endl;
	return;
}

/*
* This methods calculates transpose in efficient manner.
* In this case, matrix data is stored in a different data structure than simply 2-D array.
* This function returns the transpose in a new variable, keeping current matrix unchanged.
*/
void SparseMatrix::FastTranspose3(SparseMatrix* transpose)
{
	cout << "Running " << __FUNCTION__ << endl;
	/* SparseMatrix b(rows, cols, terms);*/
	int* rowSize = new int[cols];
	int* rowStart = new int[cols];
	for (long i = 0; i < cols; i++)
	{
		rowStart[i] = 0;
		rowSize[i] = 0;
	}
	/* cout << "rowStart and rowSize are initialize as 0" << endl;*/
	for (long i = 0; i < terms; i++)
	{
		rowSize[SmArray[i].col]++;
	}
	/* cout << "rowSize has been done" << endl;*/
	rowStart[0] = 0;
	for (int i = 1; i < cols; i++)
	{
		rowStart[i] = rowSize[i - 1] + rowStart[i - 1];
	}
	/* cout << "rowStart has been done. Going to transpse" << endl;*/
	for (long i = 0; i < terms; i++)
	{
		int j = 0;
		j = rowStart[SmArray[i].col];
		transpose->SmArray[j].col = SmArray[i].row;
		transpose->SmArray[j].row = SmArray[i].col;
		transpose->SmArray[j].val = SmArray[i].val;
		rowStart[SmArray[i].col]++;
	}
	/* cout << "Transpose is done" << endl;*/
	delete[] rowSize;
	delete[] rowStart;
	cout << "Exiting " << __FUNCTION__ << endl;
	return;
}

/*
* It prints in the following manner.
* Row_Number Column_Number Stored_value
*/
void SparseMatrix::print()
{
	cout << "Running " << __FUNCTION__ << endl;
	for (long i = 0; i < terms; i++)
	{
		cout << SmArray[i].row << " ";
		cout << SmArray[i].col << " ";
		cout << SmArray[i].val << endl;
	}
	cout << "Exiting " << __FUNCTION__ << endl;
}