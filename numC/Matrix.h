//==========================================//
//																					//
// Matrix.h																	//
// ----------------------------------------	//
// Header file for Matrix algebra						//
//																					//
// ----------------------------------------	//
// Mar 19, 2021															//
// C J Park																	//
// chanjure@snu.ac.kr												//
//																					//
//==========================================//

#ifndef MATRIX_h
#define MATRIX_h

// Library dependencies

// Matrix operation functions
extern double** sum(double**, double**, int, int);
extern double** sub(double**, double**, int, int);
extern double** matmul(double**, double**, int, int, int);
extern double** transpose(double**, int, int);
extern double** inverse(double**, int, int);

// Util functions
extern double** identity(int, double val = 1.); // Return identity matrix of dimension int x int
extern double** mat_copy(double**, int, int); // Copy matrix
extern double** zero(int, int); // Create and initalize matrix of dimension int x int
extern void print(double**,int,int); // Print matrix

#endif
