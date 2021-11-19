#ifndef STATS_H
#define STATS_H

Matrix ave(Matrix, int axis=1);
Matrix var(Matrix, int axis=1);
Matrix cov(Matrix, int axis=0);

Matrix* JK_resample(Matrix, int axis=1);

Matrix sample_ave(Matrix*, int); // int = number of jk samples
Matrix JK_error(Matrix*, int);
Matrix BS_error(Matrix*, int);

double chisqr(Matrix, Matrix, Matrix); // y_ave, c_inv, f

#endif
