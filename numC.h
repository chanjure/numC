//==========================================//
//																					//
// numC.h																		//
// ----------------------------------------	//
// numpy like library for C/C++							//
//																					//
// ----------------------------------------	//
// Mar 19, 2021															//
// C J Park																	//
// chanjure@snu.ac.kr												//
//																					//
//==========================================//

#ifndef NUMC_H
#define NUMC_H

// Library dependencies
#include <iostream>

// ============
// class Matrix
// ------------
class Matrix{

	private:
		int shape[2];
		const std::string type = "numC::Matrix";
		double** matrix;

	public:

		// Generator
		Matrix(int, int);
		~Matrix();

		// Util
		double operator[](int, int) const{return matrix[i][j]};
		double& operator[](int, int){return matrix[i][j]};

		// Arithmetics
		Matrix operator+(const Matrix &A);
		Matrix operator-(const Matrix &A);
		Matrix operator*(const Matrix &A);
		Matrix operator*(double a);
		Matrix operator/(const Matrix &A);
		Matrix operator/(double a);
		Matrix operator@(const Matrix &A);

		// Matrix operation
		Matrix flat();
		double trace();
		Matrix T();
		Matrix diag();
		Matrix det();
		Matrix inv();
		Matrix c_(Matrix, Matrix);
		Matrix r_(Matrix, Matrix);
};

// ============
// class Vector
// ============

class Vector{

	private:

	public:

}

// Functions
extern double ftn(double, double);

#endif
