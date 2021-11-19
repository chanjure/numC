/**
 * @file Matrix.h
 *
 * @brief Header file for Matrix algebra
 * @date Mar 19, 2021
 * @author C J Park \n chanjure@snu.ac.kr
 * @bug No known bugs.
 * @version 0.1
 */

#ifndef MATRIX_h
#define MATRIX_h

// Library dependencies

// Matrix operation functions
/**
 * @brief Elementwise summation
 *
 * mat1 + mat2 = result
 * Two input matrices must be in same shape axb
 *
 * Parameters:
 * @param mat1, mat2 (double**) matrices to be added
 * @param a (int) number of rows of mat1 and mat2
 * @param b (int) number of columns of mat1 and mat2
 *
 * Returns:
 * @return result (double**)
 *
 * Example:
 * @details A = sum(A,B,2,2);
 *
 * Tag: add, sum, element wise
 */
extern double** sum(double**, double**, int, int);

/**
 * @brief Elementwise subtraction
 *
 * mat1 - mat2 = result
 * Two input matrices must be in same shape axb
 *
 * Parameters:
 * @param mat1, mat2 (double**) matrices to be subtracted
 * @param a (int) number of rows of mat1 and mat2
 * @param b (int) number of columns of mat1 and mat2
 *
 * Returns:
 * @return result (double**)
 *
 * Example:
 * @details A = sub(A,B,2,2);
 *
 * Tag: subtract, element wise
 */
extern double** sub(double**, double**, int, int);

/**
 * @brief Matrix multiplication
 *
 * mat1 * mat2 = result
 * number of column of mat1 must match number of column of mat2
 *
 * Parameters:
 * @param mat1, mat2 (double**) matrices to be multiplied
 * @param a (int) number of rows of mat1
 * @param b (int) number of folumns of mat1 = number of rows of mat2
 * @param c (int) number of columns of mat2
 *
 * Returns:
 * @return result (double**) matrix of dimension a x c
 *
 * Example:
 * @details A = matmul(A,B,2,3,2);
 *
 * Tag: multiplication
 */
extern double** matmul(double**, double**, int, int, int);

/**
 * @brief Matrix transpose
 *
 * mat^T
 *
 * Parameters:
 * @param mat (double**) matrix to be transposed
 * @param a (int) number of rows of mat
 * @param b (int) number of columns of mat
 *
 * Returns:
 * @return result (double**) transposed mat
 *
 * Example:
 * @details A_T = transpose(A,2,2);
 *
 * Tag: transpose
 */
extern double** transpose(double**, int, int);

/**
 * @brief Matrix left inverse
 *
 * Matrix left inverse using Gaussian reduction
 *
 * Parameters:
 * @param A (double**) matrix to inverse
 * @param a (int) number of rows of A
 * @param b (int) number of columns of A
 *
 * Returns:
 * @return result (double**) left inverse of A
 *
 * Example:
 * @details A_inv = inverse(A,2,2);
 *
 * Tag: left inverse gaussian reduction
 */
extern double** inverse(double**, int, int);

// Util functions
/**
 * @brief Identity matrix
 *
 * create identity matrix of given size
 * square matrix will be created
 *
 * Parameters:
 * @param a (int) dimension of identity matrix
 * @param val (double) value to initalize (default = 1.)
 *
 * Returns:
 * @return result (double**) identity matrix
 *
 * Example:
 * @details A = identity(3, 0.5);
 *
 * Tag: identity initalize
 */
extern double** identity(int, double val = 1.);

/**
 * @brief Hard copy matrix
 *
 * create hard copy of given matrix
 *
 * Parameters:
 * @param mat (double**) matrix to copy
 * @param a (int) number of rows of mat
 * @param b (int) number of columns of mat
 *
 * Returns:
 * @return result (double**) hard copy of mat
 *
 * Example:
 * @details A = mat_copy(B,3,3);
 *
 * Tag: ftn
 */
extern double** mat_copy(double**, int, int);

/**
 * @brief Initialize matrix
 *
 * Create and initialize matrix elements to zero
 *
 * Parameters:
 * @param a (int) number of rows
 * @param b (int) number of columns
 *
 * Returns:
 * @return result (double**) zero matrix of size axb
 *
 * Example:
 * @details A = zero(2,3);
 *
 * Tag: initalize zero
 */
extern double** zero(int, int);

/**
 * @brief Print matrix
 *
 * print matrix of given size
 *
 * Parameters:
 * @param A (double**) matrix to print
 * @param a (int) number of rows of A
 * @param b (int) number of columns of A
 *
 * Returns:
 * @return stdout(matrix A)
 *
 * Example:
 * @details print(A,2,3);
 *
 * Tag: print
 */
extern void print(double**,int,int);

#endif
