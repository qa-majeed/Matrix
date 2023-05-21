#pragma once
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
	SparseMatrix(int ro, int col, int term);
	SparseMatrix();
	~SparseMatrix();
	void operator=(SparseMatrix a);
	void initialize();
	void print();
	void Transpose1(SparseMatrix* transpose);
	void Transpose2(SparseMatrix* transpose);
	void FastTranspose3(SparseMatrix* transpose);
	int getcols()
	{
		return cols;
	}
	int getrows()
	{
		return rows;
	}
	int get_terms() 
	{
		return terms;
	}
	int get_capacity()
	{
		return capacity;
	}

};
