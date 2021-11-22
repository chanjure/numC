/**
 * @file Stats.C
 * @brief Statistics tools
 */

// Library dependencies
#include<math.h>
#include<numC/Matrix_gsl.h>
#include<numC/Stats.h>

#include<iostream> //for dignose

Matrix ave(Matrix A, int axis){
	
	int n = A.shape[0];
	int m = A.shape[1];

	if(axis == 1){

		Matrix result(n,1,"ave");

		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				result.matrix[i][0] += A.matrix[i][j]/(1.*m);
			}
		}
		
		return result;
	}
	else if (axis == 0){
		
		Matrix result(1,m);
		
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++) result.matrix[0][j] += A.matrix[i][j]/(1.*n);
		}

		return result;
	}
}

Matrix var(Matrix A, int axis){
	// Default : sample var

	int n = A.shape[0];
	int m = A.shape[1];

	if(axis == 1){
		Matrix A_ave = ave(A, 1);
		Matrix result(n,1);

		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++) result.matrix[i][0] += pow(A.matrix[i][j] - A_ave.matrix[i][0], 2.)/(1.*m)/(m - 1.);
		}

		return result;
	}
	else if(axis == 0){
		Matrix A_ave = ave(A, 0);
		Matrix result(1,m);
		
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++) result.matrix[0][j] += pow(A.matrix[i][j] - A_ave.matrix[0][j], 2.)/(1.*n)/(n - 1.);
		}

		return result;
	}
}

Matrix cov(Matrix A, int axis){
	// Default : sample covariance

	int n = A.shape[0];
	int m = A.shape[1];
	
	if(axis == 0){
		Matrix A_ave;
		A_ave = ave(A, 1);

		Matrix result(n,n);

		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				for(int k=0;k<m;k++){
					result.matrix[i][j] += (A.matrix[i][k] - A_ave.matrix[i][0]) * (A.matrix[j][k] - A_ave.matrix[j][0])/(1.*m)/(m-1.);
				}
			}
		}

		return result;
	}
	else if(axis == 1){
		Matrix A_ave = ave(A, 0);

		Matrix result(m,m);

		for(int i=0;i<m;i++){
			for(int j=0;j<m;j++){
				for(int k=0;k<n;k++) result.matrix[i][j] += (A.matrix[k][i] - A_ave.matrix[0][i]) * (A.matrix[k][j] - A_ave.matrix[0][j])/(1.*m)/(m-1.);
			}
		}

		return result;
	}
}

Matrix* JK_resample(Matrix A, int axis){
	
	int n = A.shape[0];
	int m = A.shape[1];

	Matrix *result;
	result = new Matrix [m];
	for(int i=0;i<m;i++) result[i].init(n, m-1);

	int p=0;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			p = 0;
			for(int k=0;k<m;k++){
				if(i != k){
					result[i].matrix[j][p] = A.matrix[j][k];
					p++;
				}
			}
		}
	}

	return result;
}

Matrix sample_ave(Matrix* A, int l){

	int n = A[0].shape[0];

	Matrix result(n,1);

	for(int i=0;i<n;i++){
		for(int j=0;j<l;j++) result.matrix[i][0] += A[j].matrix[i][0]/(1.*l);
	}

	return result;
}

Matrix JK_error(Matrix* A, int l){

	int n = A[0].shape[0];
	
	Matrix A_ave(n,1);
	A_ave = sample_ave(A, l);

	Matrix result(n, 1);

	for(int i=0;i<n;i++){
		for(int j=0;j<l;j++) result.matrix[i][0] += pow(A[j].matrix[i][0] - A_ave.matrix[i][0], 2.) /(1.*l)*(l-1.);
	}

	for(int i=0;i<n;i++) result.matrix[i][0] = sqrt(result.matrix[i][0]);

	return result;
}

Matrix BS_error(Matrix* A, int l){
	int n = A[0].shape[0];
	
	Matrix A_ave(n,1);
	A_ave = sample_ave(A, l);

	Matrix result(n,1);

	for(int i=0;i<n;i++){
		for(int j=0;j<l;j++) result.matrix[i][0] += pow(A[j].matrix[i][0] - A_ave.matrix[i][0],2.) / (l-1.);
	}

	for(int i=0;i<n;i++) result.matrix[i][0] = sqrt(result.matrix[i][0]);

	return result;
}

double chisqr(Matrix y_bar, Matrix c_inv, Matrix f){

	double result;

	result = matmul(matmul(sub(y_bar, f).T(), c_inv), sub(y_bar, f)).matrix[0][0];

	return result;
}
