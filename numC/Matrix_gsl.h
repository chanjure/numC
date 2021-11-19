#ifndef MATRIX_GSL_H
#define MATIRX_GSL_H

#include<iostream>
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_vector.h>
#include<gsl/gsl_linalg.h>

class Matrix{

	private:

	public:
		int shape[2];
		double** matrix;
		double** eigval;
		double** eigvec;
		std::string name;

		Matrix(std::string name = "New"){
			this->name = name;
			this->matrix = NULL;
		}
		Matrix(int n, int m, std::string name = "New"){
			this->init(n, m, name);
		}
		Matrix(const Matrix& A){
			int n = A.shape[0];
			int m = A.shape[1];
			this->init(n, m, this->name);
			for(int i=0;i<n;i++){
				for(int j=0;j<m;j++){
					this->matrix[i][j] = A.matrix[i][j];
					this->eigvec[i][j] = A.eigvec[i][j];
				}
				this->eigval[i][0] = A.eigval[i][0];
			}
		}
		~Matrix(){
			delete [] this->matrix;
			delete [] this->eigval;
			delete [] this->eigvec;
		}

		// Utill functions
		void init(int, int, std::string name = "New");
		Matrix & operator=(const Matrix &A);
		Matrix operator%(const Matrix &A);
		Matrix operator+(const Matrix &A);
		Matrix operator-(const Matrix &A);
		Matrix & operator*=(double a){
			for(int i=0;i<this->shape[0];i++){
				for(int j=0;j<this->shape[1];j++) this->matrix[i][j] *= a;
			}

			return *this;
		}
		Matrix operator/=(double a){
			for(int i=0;i<this->shape[0];i++){
				for(int j=0;j<this->shape[1];j++) this->matrix[i][j] /= a;
			}

			return *this;
		}

		// Matrix functions
		void printM(std::string = "matrix");
		Matrix flat(); // Return diagonal element in vector form
		double trace();
		Matrix T();
		void asMat(double**);
		Matrix diag(); // Return diagonalized matrix
		Matrix clip(double, std::string = "upper"); //upper or lower

		// gsl functions
		Matrix inv();
		double det(); 
		void eig();
		double min(std::string = "matrix");
		double max(std::string = "matrix");
};
inline Matrix operator* (Matrix A, double a){
	return A*=a;
}
inline Matrix operator* (double a, Matrix A){
	return A*=a;
}
inline Matrix operator/ (Matrix A, double a){
	return A/=a;
}
inline Matrix operator/ (double a, Matrix A){
	return A/=a;
}

// Elementwise Operations
Matrix add(Matrix, Matrix);
Matrix sub(Matrix, Matrix);
Matrix mul(Matrix, Matrix);
Matrix div(Matrix, Matrix);

// Matrix Operations
Matrix matmul(Matrix, Matrix);
Matrix c_(Matrix, Matrix);
Matrix r_(Matrix, Matrix);

// Raw Array Operations
double max(double**, int, int);
double min(double**, int, int);

#endif
