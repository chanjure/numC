#include <iostream>
#include <numC/Matrix_gsl.h>
#include <numC/Utils.h>

int main(){

	/*
	 * Matrix_gsl class example
	 */

	// Create n x m Matrix with name "A".
	// The matrix is initialized as zero matrix
	// If the name is not specified, it is automatically set to ""
	printf("Matrices can be initialized with a name\n");
	printf("eg) Matrix A(2,2,'A')\n");

	Matrix A(2,2,"A");
	Matrix B(2,2);

	printf("\n");

	// Print matrices
	printf("Utils::printM() is a utility to print a matrix\n");
	printf("It can print three object.\nprintM('matrix') or printM() prints matrix elements.\n");
	printf("printM('eigval') prints eigenvalue\n");
	printf("printM('eigvec') prints eigenvector\n");
	printf("note that, to print eigval and eigvec, you must run A.eig() to calculate it first.\n\n");
	printf("Print matrix A initialized with name 'A'\n");
	A.printM();
	printf("Print matrix B initialized without name\n");
	B.printM();
	printf("and they are automatically initialized to zeros\n");
	
	printf("\n");

	printf("Setting values of A, B\n");
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

	printf("\n");

	// Concatenate column
	printf("Matrix::c_(A,B) concatenates AB along column\n");
	Matrix C;
	C = c_(A,B);
	C.printM();
	
	printf("\n");
	
	// Concatenate row
	printf("Matrix::r_(A,B) concatenates AB along row\n");
	Matrix R;
	R = r_(A,B);
	R.printM();

	printf("\n");

	// Calculate trace of the matrix
	double A_trace;
	A_trace = A.trace();
	printf("Matrix::trace() returns trace of A : %lf\n", A_trace);

	printf("\n");

	// Print transpose of the matrix
	printf("Matrix::T() returns transpose matrix of B\n");
	B.T().printM();

	printf("\n");

	// Matrix multiplication
	printf("Percent symbol between A,B is A x B\n");
	Matrix E;
	E = A%B;
	E.printM();

	printf("\n");

	// Calculate eigenvalue and eigenvector and save it to A.eigvec and A.eigval
	printf("Matrix::eig() calculates the eigenvalue and eigenvector\n");
	E.eig();
	E.printM("eigval");

	printf("\n");
	
	// Minimum or maximum of matrix element or eigenvalues
	printf("(Matrix::max()) Maximum of eigenvalue of A x B : %lf\n",E.max("eigval"));

	printf("Eigenvector of A x B\n");
	E.printM("eigvec");

	printf("\n");

	// Calculate determinant of A x B
	double E_det;
	E_det = E.det();
	printf("(Matrix::det()) Determinant of E : %lf \n", E_det);

	printf("\n");

	// Elementwise arithmetic is fully equipted
	printf("Elementwise operation of matrix\n");
	printf("A+B\n");
	(A+B).printM();
	printf("A-B\n");
	(A-B).printM();
	printf("A.B\n");
	mul(A,B).printM();
	printf("A/B\n");
	div(A,B).printM();

	printf("\n");

	// Scalar product available
	printf("Scalar and matrix product\n");
	double a = 2.;
	printf("A*2.\n");
	(A*a).printM();
	printf("A/2.\n");
	(A/a).printM();

	printf("\n");

	// Clipping by value
	printf("(Matrix::clip(val,'upper' or 'lower')) clipping value in A larger or lower than val\n");
	(A.clip(1.5,"upper")).printM();

	return 0;
}
