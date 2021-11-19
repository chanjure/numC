#include<iostream>
#include"Matrix_gsl.h"
#include"Utills.h"
#include"Stats.h"

int main(){

	Matrix A(2,2,"A");
	Matrix B(2,2,"B");
	Matrix C(2,4,"C");
	Matrix R(4,2,"R");


	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			A.matrix[i][j] = (i+j)*1.;
			B.matrix[i][j] = i*1. + 10.*j;
		}
	}
	C = c_(A,B);
	C.printM();

	R = r_(A,B);
	R.printM();

	A.printM();
	B.printM();

	Matrix D;//(2,2,"D");
	D = A;//(A%B)%A;
	D.printM();

	Matrix E(2,2,"E");
	E = A+B;
	E.printM();

	Matrix F(2,2,"F");
	F = (-1.)*A;
	F.printM();

	return 0;
}
