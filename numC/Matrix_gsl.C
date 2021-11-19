/* Tag Index
Imp : Could be improved

   */

#include<gsl/gsl_vector.h>
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_linalg.h>
#include<numC/Matrix_gsl.h>

// Utill functions
void Matrix::init(int n, int m, std::string name){

	this->shape[0] = n;
	this->shape[1] = m;
	this->matrix = new double* [n];
	for(int i=0;i<n;i++) *(this->matrix+i) = new double [m];
	this->eigval = new double* [n];
	for(int i=0;i<n;i++) *(this->eigval+i) = new double [1];
	this->eigvec = new double* [n];
	for(int i=0;i<n;i++) *(this->eigvec+i) = new double [m];

	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			this->matrix[i][j] = 0.;
			this->eigvec[i][j] = 0.;
		}
		this->eigval[i][0] = 0.;
	}
	
	this->name = name;
}

Matrix& Matrix::operator=(const Matrix &A){

	if (this != &A){ // Check self reference

		if(this->matrix != NULL) this->~Matrix();

		int n = A.shape[0];
		int m = A.shape[1];
	
		this->init(n,m, this->name);

		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				this->matrix[i][j] = A.matrix[i][j];
			}
		}
	}

	return *this;
}

Matrix Matrix::operator%(const Matrix &A){
	
	int n = this->shape[0];
	int m = A.shape[1];
	int k = this->shape[1];

	Matrix result(n,m);

	result = matmul(*(this),A);
	return result;
}

Matrix Matrix::operator+(const Matrix &A){
	return add(*(this),A);
}

Matrix Matrix::operator-(const Matrix &A){
	return sub(*(this),A);
}
/*
Matrix Matrix::operator*(double n){
	Matrix result = *this;
	for(int i=0;i<result.shape[0];i++){
		for(int j=0;j<result.shape[1];j++) result.matrix[i][j] *= n;
	}

	return result;
}

Matrix Matrix::operator/(const Matrix &A){
	return div(*(this),A);
}
*/
// Matrix functions
void Matrix::printM(std::string option){
	std::cout<<this->name<<std::endl;
	if(!option.compare("matrix")){
		for(int i=0;i<this->shape[0];i++){
			for(int j=0;j<this->shape[1];j++) printf("%10.8f ",this->matrix[i][j]);
			printf("\n");
		}
	}
	else if(!option.compare("eigval")){ // Imp error handling
		for(int i=0;i<this->shape[0];i++) printf("%10.8f ",this->eigval[i][0]);
		printf("\n");
	}
	else if(!option.compare("eigvec")){
		for(int i=0;i<this->shape[0];i++){
			for(int j=0;j<this->shape[1];j++) printf("%10.8f ",this->eigvec[i][j]);
			printf("\n");
		}
	}
}

Matrix Matrix::flat(){
	Matrix result(this->shape[0],1);

	for(int i=0;i<this->shape[0];i++) result.matrix[i][0] = this->matrix[i][i];

	return result;
}

double Matrix::trace(){
	double result=0.;

	for(int i=0;i<this->shape[0];i++) result += this->matrix[i][i];

	return result;
}

Matrix Matrix::T(){
	Matrix result(this->shape[1],this->shape[0]);

	for(int i=0;i<this->shape[1];i++){
		for(int j=0;j<this->shape[0];j++) result.matrix[i][j] = this->matrix[j][i];
	}

	return result;
}

void Matrix::asMat(double** a){
	//todo: automatically get shape of the array then initialize Matrix	
	for(int i=0;i<this->shape[0];i++){
		for(int j=0;j<this->shape[1];j++) this->matrix[i][j] = a[i][j];
	}
}

Matrix Matrix::diag(){

	int n = this->shape[0];

	Matrix result(n, n);

	for(int i=0;i<n;i++) result.matrix[i][i] = this->eigval[i][0];

	return result;
}

Matrix Matrix::clip(double thres, std::string option){
	// Exclusive upper/lower cliping
	
	int n = this->shape[0];
	int m = this->shape[1];

	Matrix result(n, m);
	
	if(!option.compare("upper")){
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(this->matrix[i][j] > thres) result.matrix[i][j] = 0.;
				else result.matrix[i][j] = this->matrix[i][j];
			}
		}
	}
	else if(!option.compare("lower")){
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(this->matrix[i][j] < thres) result.matrix[i][j] = 0.;
				else result.matrix[i][j] = this->matrix[i][j];
			}
		}
	}

	return result;
}

// gsl functions
Matrix Matrix::inv(){
	// Calculate inverse using LU decomposition.
	
	int n = this->shape[0];
	int m = this->shape[1];
	gsl_permutation *gsl_p = gsl_permutation_alloc(n);
	gsl_matrix *gsl_LU = gsl_matrix_alloc(n,m);
	int sign;

	Matrix result(m, n);

	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++) gsl_matrix_set(gsl_LU, i, j, this->matrix[i][j]);
	}

	gsl_linalg_LU_decomp(gsl_LU, gsl_p, &sign);
	gsl_linalg_LU_invx(gsl_LU, gsl_p);
	
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++) result.matrix[i][j] = gsl_matrix_get(gsl_LU, i, j);
	}

	gsl_matrix_free(gsl_LU);
	gsl_permutation_free(gsl_p);

	return result;
}

double Matrix::det(){

	int n = this->shape[0];
	int m = this->shape[1];

	gsl_matrix *gsl_LU = gsl_matrix_alloc(n,m);
	gsl_permutation *gsl_p = gsl_permutation_alloc(n);
	int sign;

	double result;

	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++) gsl_matrix_set(gsl_LU, i, j, this->matrix[i][j]);
	}

	gsl_linalg_LU_decomp(gsl_LU, gsl_p, &sign);
	result = gsl_linalg_LU_det(gsl_LU, sign);

	gsl_matrix_free(gsl_LU);
	gsl_permutation_free(gsl_p);

	return result;
}

void Matrix::eig(){
	// One-sided Jacobi orthonormalization

	int n = this->shape[0];
	int m = this->shape[1];
	gsl_matrix *gsl_A = gsl_matrix_alloc(n, m); // this matrix & eigen vector matrix
	gsl_vector *gsl_S = gsl_vector_alloc(n);	// eigen value vector
	gsl_matrix *gsl_V = gsl_matrix_alloc(n, m); // eigen vector matrix
	gsl_vector *workspace = gsl_vector_alloc(n); // workspace for Golub-Reinsch
	
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++) gsl_matrix_set(gsl_A, i, j, this->matrix[i][j]);
	}
	
	gsl_linalg_SV_decomp(gsl_A, gsl_V, gsl_S, workspace); // Golub-Reinsch
	//gsl_linalg_SV_decomp_jacobi(gsl_A, gsl_V, gsl_S); //Jacobi
	
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++) this->eigvec[i][j] = gsl_matrix_get(gsl_A,i,j);
		this->eigval[i][0] = gsl_vector_get(gsl_S,i);
	}

	// Destructor
	gsl_vector_free(gsl_S);
	gsl_vector_free(workspace); // Golub-Reinsch
	gsl_matrix_free(gsl_A);
	gsl_matrix_free(gsl_V);
}

double Matrix::min(std::string option){

	int n = this->shape[0];
	int m = this->shape[1];

	double result;

	if(!option.compare("matrix")){
		gsl_matrix *gsl_this = gsl_matrix_alloc(n, m);

		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++) gsl_matrix_set(gsl_this, i, j, this->matrix[i][j]);
		}
	
		result = gsl_matrix_min(gsl_this);

		gsl_matrix_free(gsl_this);

	}
	else if (!option.compare("eigval")){
		gsl_matrix *gsl_this = gsl_matrix_alloc(n, 1);

		for(int i=0;i<n;i++) gsl_matrix_set(gsl_this, i, 0, this->eigval[i][0]);

		result = gsl_matrix_min(gsl_this);

		gsl_matrix_free(gsl_this);

	}

	return result;

}

double Matrix::max(std::string option){

	int n = this->shape[0];
	int m = this->shape[1];

	double result;

	if(!option.compare("matrix")){
		gsl_matrix *gsl_this = gsl_matrix_alloc(n, m);

		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++) gsl_matrix_set(gsl_this, i, j, this->matrix[i][j]);
		}

		result = gsl_matrix_max(gsl_this);

		gsl_matrix_free(gsl_this);
	}
	else if (!option.compare("eigval")){
		gsl_matrix *gsl_this = gsl_matrix_alloc(n, 1);

		for(int i=0;i<n;i++) gsl_matrix_set(gsl_this, i, 0, this->eigval[i][0]);

		result = gsl_matrix_max(gsl_this);

		gsl_matrix_free(gsl_this);
	}

	return result;
}

// Elementwise Operations
Matrix add(Matrix A, Matrix B){

	if(A.shape[0] != B.shape[0] || A.shape[1] != B.shape[1]){
		printf("Matrix error : add, A=(%d,%d), B=(%d,%d) shape does not match.\n",A.shape[0],A.shape[1],B.shape[0],B.shape[1]);
		exit(1); // Imp
	}
	int n = A.shape[0];
	int m = A.shape[1];
	Matrix result(n, m);

	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++) result.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
	}

	return result;
}

Matrix sub(Matrix A, Matrix B){

	if(A.shape[0] != B.shape[0] || A.shape[1] != B.shape[1]){
		printf("Matrix error : sub, A=(%d,%d), B=(%d,%d) shape does not match.\n",A.shape[0],A.shape[1],B.shape[0],B.shape[1]);
		exit(1); // Imp
	}
	int n = A.shape[0];
	int m = A.shape[1];
	Matrix result(n, m);
	
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++) result.matrix[i][j] = A.matrix[i][j] - B.matrix[i][j];
	}

	return result;
}
	
Matrix mul(Matrix A, Matrix B){

	if(A.shape[0] != B.shape[0] || A.shape[1] != B.shape[1]){
		printf("Matrix error : mul, A=(%d,%d), B=(%d,%d) shape does not match.\n",A.shape[0],A.shape[1],B.shape[0],B.shape[1]);
		exit(1); // Imp
	}
	int n = A.shape[0];
	int m = A.shape[1];
	Matrix result(n, m);
	
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++) result.matrix[i][j] = A.matrix[i][j] * B.matrix[i][j];
	}

	return result;
}

Matrix div(Matrix A, Matrix B){

	if(A.shape[0] != B.shape[0] || A.shape[1] != B.shape[1]){
		printf("Matrix error : div, A=(%d,%d), B=(%d,%d) shape does not match.\n",A.shape[0],A.shape[1],B.shape[0],B.shape[1]);
		exit(1); // Imp
	}
	int n = A.shape[0];
	int m = A.shape[1];
	Matrix result(n, m);
	
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++) result.matrix[i][j] = A.matrix[i][j] / B.matrix[i][j];
	}

	return result;
}

// Matrix Operations
Matrix matmul(Matrix A, Matrix B){

	if(A.shape[1] != B.shape[0]){
		printf("Matrix error : matmul, A=(%d,%d), B=(%d,%d) shape does not match.\n",A.shape[0],A.shape[1],B.shape[0],B.shape[1]);
		exit(1); // Imp
	}
	int n = A.shape[0];
	int m = B.shape[1];
	int l = A.shape[1]; // = B.shape[0]
	Matrix result(n, m);

	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			for(int k=0;k<l;k++) result.matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];
		}
	}

	return result;
}

Matrix c_(Matrix A, Matrix B){

	if(A.shape[0] != B.shape[0]){
		printf("Matrix error : c_, A=(%d,%d), B=(%d,%d) number of column does not match.\n",A.shape[0],A.shape[1],B.shape[0],B.shape[1]);
		exit(1);
	}

	int n = A.shape[0];
	int m = A.shape[1];
	int o = B.shape[1];

	Matrix result(n,m+o);
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++) result.matrix[i][j] = A.matrix[i][j];
		for(int j=0;j<o;j++) result.matrix[i][j+m] = B.matrix[i][j];//fix here
	}

	return result;
}

Matrix r_(Matrix A, Matrix B){

	if(A.shape[1] != B.shape[1]){
		printf("Matrix error : r_, A=(%d,%d), B=(%d,%d) number of row does not match.\n",A.shape[0],A.shape[1],B.shape[0],B.shape[1]);
		exit(1);
	}

	int n = A.shape[0];
	int m = A.shape[1];
	int o = B.shape[0];

	Matrix result(n+o,m);
	for(int j=0;j<m;j++){
		for(int i=0;i<n;i++) result.matrix[i][j] = A.matrix[i][j];
		for(int i=0;i<o;i++) result.matrix[i+n][j] = B.matrix[i][j];
	}

	return result;
}

// Raw Array Operations
double max(double** A, int n, int m){
	
	gsl_matrix *gsl_A = gsl_matrix_alloc(n, m);

	double result;

	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++) gsl_matrix_set(gsl_A, i, j, A[i][j]);
	}

	result = gsl_matrix_max(gsl_A);

	gsl_matrix_free(gsl_A);

	return result;
}

double min(double** A, int n, int m){

	gsl_matrix *gsl_A = gsl_matrix_alloc(n, m);

	double result;

	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++) gsl_matrix_set(gsl_A, i, j, A[i][j]);
	}

	result = gsl_matrix_min(gsl_A);

	gsl_matrix_free(gsl_A);

	return result;
}	
