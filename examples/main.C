#include <iostream>
#include <numC/Matrix_gsl.h>
#include <numC/Stats.h>
#include <numC/Utils.h>

int main(){

	/*
	 * Matrix_gsl class example
	 */

	// Create n x m Matrix with name "A".
	// The matrix is initialized as zero matrix
	// If the name is not specified, it is automatically set to ""
	Matrix A(2,2,"A");
	Matrix B(2,2);

	// Print matrices
	printf("Print A and B\n");
	A.printM();
	B.printM();

	// Set matrix values
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			A.matrix[i][j] = (i+j)*1.;
			B.matrix[i][j] = i*1. + 10.*j;
		}
	}

	// Print assigned values
	printf("Print assigned values\n");
	A.printM();
	B.printM();

	// Concatenate column
	Matrix C;
	C = c_(A,B);
	printf("Print concatenated AB along column\n");
	C.printM();
	
	// Concatenate row
	Matrix R;
	R = r_(A,B);
	printf("Print concatenated AB along row\n");
	R.printM();

	// Calculate trace of the matrix
	double A_trace;
	A_trace = A.trace();
	printf("Trace of A : %lf\n", A_trace);

	// Print transpose of the matrix
	printf("Transpose of B\n");
	B.T().printM();

	// Matrix multiplication
	Matrix E;
	E = A%B;
	printf("A x B\n");
	E.printM();

	// Calculate eigenvalue and eigenvector and save it to A.eigvec and A.eigval
	E.eig();
	printf("Eigenvalue of A x B\n");
	E.printM("eigval");
	
	// Minimum or maximum of matrix element or eigenvalues
	printf("Maximum of eigenvalue of A x B : %lf\n",E.max("eigval"));

	printf("Eigenvector of A x B\n");
	E.printM("eigvec");

	// Calculate determinant of A x B
	double E_det;
	E_det = E.det();
	printf("Determinant of E : %lf \n", E_det);

	// Elementwise arithmetic is fully equipted
	printf("A+B\n");
	(A+B).printM();
	printf("A-B\n");
	(A-B).printM();
	printf("A.B\n");
	mul(A,B).printM();
	printf("A/B\n");
	div(A,B).printM();

	// Scalar product available
	double a = 2.;
	printf("A*2.\n");
	(A*a).printM();
	printf("A/2.\n");
	(A/a).printM();

	// Clipping by value
	printf("clipping value in A larger than 1.5\n");
	(A.clip(1.5,"upper")).printM();

	return 0;
}
