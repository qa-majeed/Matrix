#include <iostream>
#include <ctime>
using namespace std;


class MatrixTerm
{
	friend class SparseMatrix;
private:
	int row, col, val;
};
class SparseMatrix
{
private:
	int rows, cols;
	long terms, capacity;
	/* 
	*	It stores a 2-D matrix in a conventional way.
	*	Declare an array of 75*75 or 100*100 here
	*/
	int** a;
	MatrixTerm* SmArray;

public:
	SparseMatrix(int);
	SparseMatrix(int ro, int col, int term)
	{
		rows = ro;
		cols = col;
		terms = capacity = term;
		SmArray = new MatrixTerm[capacity];
		a = new int* [rows];
		for (int i = 0; i < cols; i++)
			a[i] = new int[cols];
	}
	SparseMatrix()
	{
		rows = cols = terms = capacity = 0;
		a = NULL;
		SmArray = NULL;
	}
	~SparseMatrix()
	{
		for (int i = 0; i < rows; i++)
			delete[] a[i];
		delete[] a;
		delete[] SmArray;
	}
	void print();
	SparseMatrix Transpose1();
	SparseMatrix Transpose2();
	SparseMatrix FastTranspose3();
	int getcols()
	{
		return cols;
	}
	int getrows()
	{
		return rows;
	}

};

float totalTime(float ti, float tf)
{
	/*It will store total time of execution of transpose*/
	float TT((float)tf - (float)ti);
	cout << "Total time is " << TT << endl;
	float sec = TT / CLOCKS_PER_SEC;
	cout << "Total time in seconds " << sec << endl;
	return sec;
}

int main()
{
	/*IT stores time for different number of algorithms.*/
	clock_t ti[3], tf[3];

	/*It saves no of rows and cols of a matrix in operation.*/
	int b = 2;
	SparseMatrix a(10);
	a.print();
	cout << endl << endl << endl << endl;
	/*cout << "Going to transpose a function" << endl;*/
	SparseMatrix trans;
	


	cout << "Algo 01" << endl;
	ti[0] = clock();
	cout << "Initial time is " << ti[0] << endl;
	trans = a.Transpose1();
	tf[0] = clock();
	cout << "Final time is " << tf[0] << endl;
	totalTime((float)ti[0], (float)tf[0]);


	cout << "\n\n Algo 2" << endl;
	ti[0] = clock();
	cout << "Initial time is " << ti[0] << endl;
	trans = a.Transpose2();
	tf[0] = clock();
	cout << "Final time is " << tf[0] << endl;
	totalTime((float)ti[0], (float)tf[0]);

	cout << "\n\n Algo 3" << endl;
	ti[0] = clock();
	cout << "Initial time is " << ti[0] << endl;
	trans = a.FastTranspose3();
	tf[0] = clock();
	cout << "Final time is " << tf[0] << endl;
	totalTime((float)ti[0], (float)tf[0]);

	/*cout << "\n\n";
	trans = a.FastTranspose3();
	cout << "Transpose is done going to print" << endl;
	trans.print();
	cout << "Transpose printing is end" << endl;*/

	system("pause");
	return 0;
}

SparseMatrix::SparseMatrix(int b)
{
	cout << __FUNCTION__ << endl;
	//system("pause");
	rows = cols = b;
	terms = 0;
	capacity = 0;
	/*It will insuare that sparse Matrix have 10% terms*/
	long Cterms = 0;

	Cterms = (rows * cols) * .1;
	a = new int* [rows];
	for (int i = 0; i < cols; i++)
		a[i] = new int[cols];

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (terms > Cterms && cols)
			{
				a[i][j] = 0;
			}
			else
			{
				a[i][j] = rand() % 10;
				if (a[i][j] != 0)
					terms++;
			}
			/*cout << a[i][j] << " ";*/
		}
		/*cout << endl;*/
	}
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
	/*
	for (int i = 0; i < terms; i++)
	{
		cout << SmArray[i].row << " ";
		cout << SmArray[i].col << " ";
		cout << SmArray[i].val << endl;

	}*/
}

/*
* It is a conventional way of getting a transpose matrix.
* This function returns the transpose in a new variable, keeping current matrix unchanged. 
*/
SparseMatrix SparseMatrix::Transpose1()
{
	cout << "Showing Result of Algo 1" << endl;
	SparseMatrix b(rows, cols, terms);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			b.a[i][j] = a[j][i];
		}
	}
	return b;
}

/*
* This method has same complexity of conventional method.
* This function returns the transpose in a new variable, keeping current matrix unchanged.
*/
SparseMatrix SparseMatrix::Transpose2()
{
	SparseMatrix out;
	out.cols = out.rows = rows;
	out.capacity = capacity;
	out.terms = terms;
	out.SmArray = new MatrixTerm[terms];
	long b = 0;
	for (int c = 0; c < cols; c++)
	{
		for (long i = 0; i < terms; i++)
		{
			if (SmArray[i].col == c)
			{
				out.SmArray[b].row = c;
				out.SmArray[b].col = SmArray[i].row;
				out.SmArray[b].val = SmArray[i].val;
				b++;
			}
		}
	}
	return out;
}

/*
* This methods calculates transpose in efficient manner.
* In this case, matrix data is stored in a different data structure than simply 2-D array.
* This function returns the transpose in a new variable, keeping current matrix unchanged.
*/
SparseMatrix SparseMatrix::FastTranspose3()
{
	SparseMatrix b(rows, cols, terms);
	int* rowSize = new int[cols];
	int* rowStart = new int[cols];
	for (long i = 0; i < cols; i++)
	{
		rowStart[i] = 0;
		rowSize[i] = 0;
	}
	/*cout << "rowStart and rowSize are initialize as 0" << endl;*/
	for (long i = 0; i < terms; i++)
	{
		rowSize[SmArray[i].col]++;
	}
	/*cout << "rowSize has been done" << endl;*/
	rowStart[0] = 0;
	for (int i = 1; i < cols; i++)
	{
		rowStart[i] = rowSize[i - 1] + rowStart[i - 1];
	}
	/*cout << "rowStart has been done. Going to transpse" << endl;*/
	for (long i = 0; i < terms; i++)
	{
		int j = 0;
		j = rowStart[SmArray[i].col];
		b.SmArray[j].col = SmArray[i].row;
		b.SmArray[j].row = SmArray[i].col;
		b.SmArray[j].val = SmArray[i].val;
		rowStart[SmArray[i].col]++;
	}
	/*cout << "Transpose is done" << endl;*/
	delete[] rowSize;
	delete[] rowStart;
	return b;
}

/*
* It prints in the following manner.
* Row_Number Column_Number Stored_value
*/
void SparseMatrix::print()
{
	for (long i = 0; i < terms; i++)
	{
		cout << SmArray[i].row << " ";
		cout << SmArray[i].col << " ";
		cout << SmArray[i].val << endl;
	}
}