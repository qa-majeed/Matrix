#include <iostream>
#include <ctime>
#include "Matrix.h"

using namespace std;

float totalTime(float ti, float tf)
{
	/* It will store total time of execution of transpose*/
	float TT((float)tf - (float)ti);
	cout << "Total time is " << TT << endl;
	float sec = TT / CLOCKS_PER_SEC;
	cout << "Total time in seconds " << sec << endl;
	return sec;
}

int main()
{
	/* It stores time for different number of algorithms.*/
	clock_t ti, tf;

	/* It saves no of rows and cols of a matrix in operation.*/
	int b = 2;
	SparseMatrix a(10);
	a.initialize();
	a.print();
	cout << endl << endl << endl << endl;
	/* cout << "Going to transpose a function" << endl;*/
	SparseMatrix trans(a.getrows(), a.getcols(), a.get_capacity());

	cout << "Algo 01" << endl;
	ti = clock();
	cout << "Initial time is " << ti << endl;
	/* trans = a.Transpose1(&trans);*/
	a.Transpose1(&trans);
	tf = clock();
	cout << "Final time is " << tf << endl;
	totalTime((float)ti, (float)tf);


	cout << "\n\n Algo 2" << endl;
	ti = clock();
	cout << "Initial time is " << ti << endl;
	/* trans = a.Transpose2();*/
	a.Transpose2(&trans);
	tf = clock();
	cout << "Final time is " << tf << endl;
	totalTime((float)ti, (float)tf);

	cout << "\n\n Algo 3" << endl;
	ti = clock();
	cout << "Initial time is " << ti << endl;
	/* trans = a.FastTranspose3();*/
	a.FastTranspose3(&trans);
	tf = clock();
	cout << "Final time is " << tf << endl;
	totalTime((float)ti, (float)tf);

	/* cout << "\n\n";
	trans = a.FastTranspose3();
	cout << "Transpose is done going to print" << endl;
	trans.print();
	cout << "Transpose printing is end" << endl;*/

	system("pause");
	return 0;
}
