/**
 * @file Utils.h
 *
 * @brief File io uitls
 * This functions are not compatible with 
 * Matrix_gsl functions.
 * This is compatible with Matrix functions.
 *
 * @date Nov 23, 2021
 * @author C J Park \n chanjure@snu.ac.kr
 * @bug No known bugs.
 * @version 1.0
 */

#ifndef UTILLS_H
#define UTILLS_H

// Library dependencies

/**
 * @brief readfile
 *
 * read file with specific format.
 * To be generalized.
 *
 * Parameters:
 * @param fname (const char*) file name to read
 * @param x (double**) data points
 * @param y (double**) data values
 * @param n_x (int) number of data points (default = 7)
 * @param n_y (int) number of data values (default = 200)
 *
 * Returns:
 * @return void
 *
 * Example:
 * @details readfile(data6, X, Y, 7, 200);
 *
 * Tag: file io read file
 */
void readfile(const char* fname, double** x, double** y, int n_x=7, int n_y=200);

#endif
