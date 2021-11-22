/**
 * @file Stats.h
 *
 * @brief Statistics tools
 *
 * @date Nov 22, 2021
 * @author C J Park \n chanjure@snu.ac.kr
 * @bug No known bugs.
 * @version 1.0
 */
#ifndef STATS_H
#define STATS_H

// Library dependencies
#include <numC/Matrix_gsl.h>

/**
 * @brief Matrix average
 *
 * Calculate average along the given axis
 *
 * Parameters:
 * @param A (Matrix) Matrix to calculate
 * @param axis (int) axis to calculate default = 1
 *
 * Returns:
 * @return result (Matrix) a vector (collapsed Matrix)
 *
 * Example:
 * @details B = ave(A, 0);
 *
 * Tag: average vector matrix
 */
Matrix ave(Matrix A, int axis=1);

/**
 * @brief Matrix variance
 *
 * Calculate variance along the given axis
 *
 * Parameters:
 * @param A (Matrix) Matrix to calculate
 * @param axis (int) axis to calculate default = 1
 *
 * Returns:
 * @return result (Matrix) a vector (collapsed Matrix)
 *
 * Example:
 * @details B = var(A,0);
 *
 * Tag: variance vector matrix
 */
Matrix var(Matrix A, int axis=1);

/**
 * @brief Covariance matrix
 *
 * Calculate covariance along the given axis
 *
 * Parameters:
 * @param A (Matrix) Matrix of data
 * @param axis (int) axis to calculate default = 0
 *
 * Returns:
 * @return result (Matrix) covariance of vectors along axis
 *
 * Example:
 * @details C = cov(A, 0);
 *
 * Tag: covariance vector matrix
 */
Matrix cov(Matrix A, int axis=0);

/**
 * @brief Jackknife resample
 *
 * Resample along the given axis
 * It samples maximum amount of data (N samples)
 *
 * Parameters:
 * @param A (Matrix) Matrix of data
 * @param axis (int) axis to calculate default = 1
 *
 * Returns:
 * @return result (Matrix*) Array(Pointer) of matrix 
 *
 * Example:
 * @details X = JK_resample(A, 0);
 *
 * Tag: Jackknife resampling
 */
Matrix* JK_resample(Matrix A, int axis=1);

/**
 * @brief Sample average
 *
 * Calculate average of array(pointer) of Matrices
 *
 * Parameters:
 * @param A (Matrix*) Pointer to Matrix eg) resampled data
 * @param l (int) number of JK samples (N)
 *
 * Returns:
 * @return result (Matrix) collapsed array of Matrices
 *
 * Example:
 * @details A = sample_ave(B, 200);
 *
 * Tag: Jackknife average
 */
Matrix sample_ave(Matrix* A, int l); // int = number of jk samples

/**
 * @brief Jackknife standard deviation
 *
 * Calculate standard deviation(sqrt(var), error)
 * of Jackknife resampled data
 *
 * Parameters:
 * @param A (Matrix*) Jackknife resampled data
 * @param l (int) number of JK samples (N)
 *
 * Returns:
 * @return result (Matrix) collapsed array of Matrices
 *
 * Example:
 * @details A = JK_error(B, 200);
 *
 * Tag: Jackknife standard deviation error
 */
Matrix JK_error(Matrix* A, int l);

/**
 * @brief Bootstrap standard deviation
 *
 * Calculate standard deviation(sqrt(var), error)
 * of Bootstrap resampled data
 *
 * Parameters:
 * @param A (Matrix*) Bootstrap resampled data
 * @param l (int) number of BS samples
 *
 * Returns:
 * @return result (Martix) collapsed array of Matrices
 *
 * Example:
 * @details A = BS_error(B, 500);
 *
 * Tag: Bootstrap standard deviation error
 */
Matrix BS_error(Matrix* A, int l);

/**
 * @brief Chi square
 *
 * Calculate chi-square of given data
 * chi^2 = (y_bar - f)^T C^-1 (y_bar - f)
 *
 * Parameters:
 * @param y_bar (Matrix) vector containing an average of the data
 * @param c_inv (Matrix) inverse of covariance matrix
 * @param f (Matrix) vector of fitting function values
 *
 * Returns:
 * @return result (double) chi^2 of given data and fitting function
 *
 * Example:
 * @details chisq = chiqr(Y_bar, C_inv, F);
 *
 * Tag: chi-square fitting
 */
double chisqr(Matrix y_bar, Matrix c_inv, Matrix f);

#endif
