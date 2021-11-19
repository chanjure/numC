/**
 * @file Matrix.C
 * @brief Various matrix operations
 * @date Mar 19, 2021
 * @author C J Park \n chanjure@snu.ac.kr
 */

// Library dependencies
#include <iostream>
#include <numC/Matrix.h>


// ========================== //
// Matrix operation functions //
// ========================== //

double** sum(double** mat1, double** mat2, int a, int b){
    
    static double** result;

    result = new double*[a];
    for(int i=0;i<a;i++) *(result+i) = new double [b];

    for(int i=0;i<a;i++){
        for(int j=0;j<b;j++) *(*(result+i)+j) = *(*(mat1+i)+j) + *(*(mat2+i)+j);
    }

    return result;
}

double** sub(double** mat1, double** mat2, int a, int b){
    
    static double** result;

    result = new double*[a];
    for(int i=0;i<a;i++) *(result+i) = new double [b];

    for(int i=0;i<a;i++){
        for(int j=0;j<b;j++) *(*(result+i)+j) = *(*(mat1+i)+j) - *(*(mat2+i)+j);
    }

    return result;
}

double** matmul(double** mat1, double** mat2, int a, int b, int c){
    
    static double** result;
    
    result = new double*[a];
    for(int i=0;i<a;i++) *(result + i) = new double [c];

    for(int i=0;i<a;i++){
        for(int j=0;j<c;j++) *(*(result+i)+j) = 0.;
    }

    for(int i=0;i<a;i++){
        for(int j=0;j<c;j++){
            for(int k=0;k<b;k++){
                *(*(result+i)+j) += *(*(mat1+i)+k) * *(*(mat2+k)+j);
            }
        }
    }

    return result;
}

double** transpose(double** mat, int a, int b){

    static double** result;

    result = new double*[b];
    for(int i=0;i<b;i++) *(result+i) = new double [a];

    for(int i=0;i<a;i++){
        for(int j=0;j<b;j++){
            *(*(result+j)+i) = *(*(mat+i)+j);
        }
    }

    return result;
}


// ============== //
// Util functions //
// ============== //

double** identity(int a, double val){
    static double** result;

    result = new double*[a];
    for(int i=0;i<a;i++) *(result+i) = new double [a];

    for(int i=0;i<a;i++){
        for(int j=0;j<a;j++){
            if(i==j) *(*(result+i)+j) = val;
            else *(*(result+i)+j) = 0.;
        }
    }

    return result;
}

double** mat_copy(double** mat, int a, int b){
    static double** result;

    result = new double*[a];
    for(int i=0;i<a;i++) *(result+i) = new double [b];

    for(int i=0;i<a;i++){
        for(int j=0;j<b;j++) *(*(result+i)+j) = *(*(mat+i)+j);
    }

    return result;
}

double** inverse(double** A, int a, int b){

    static double** result; // output matmul(invsqA, A.T)
    double** sqA; // squarized matrix = matmul(A.transpose, A)
    double** invsqA; // inverse of squared A
    double** A_t; // Transposed matrix
    double* row; // Temporary row container
    double* invrow; // Temporary row container for inverse matrix - memorize sort order
    double det; // determinant
    double pivot;

		const double tol = 1e-14;

    result = new double*[b];
    for(int i=0;i<b;i++) *(result+i) = new double [a];

    sqA = new double*[b];
    for(int i=0;i<b;i++) *(sqA+i) = new double [b];

    invsqA = new double*[b];
    for(int i=0;i<b;i++) *(invsqA+i) = new double [b];

    row = new double [b];

    // Initially identity matrix for inverse matrix container.
    invsqA = identity(b); 
        
    // Initialize transposed matrix.
    A_t = new double*[b];
    for(int i=0; i<b;i++) *(A_t+i) = new double [b];
    
    if(a!=b){    
        A_t = transpose(A,a,b);
        // Squarize the matrix
        for(int i=0;i<b;i++){
            for(int j=0;j<b;j++){
                for(int k=0;k<a;k++){
                    *(*(sqA+i)+j) = *(*(A_t+i)+k) * *(*(A+k)+j);
                }
            }
        }
    }
    else{
        A_t = identity(a);
        sqA = mat_copy(A,a,a);
    }

    // Sort pivot
    for(int j=0;j<b;j++){
				int i = 1;
        while(*(*(sqA+j)+j) <=tol && i<b){
            // Save zero pivot row
            row = *(sqA+j);
            invrow = *(invsqA+j);
            
            // Exchange with row below
            *(sqA+j) = *(sqA+j+i);
            *(invsqA+j) = *(invsqA+j+i);

            *(sqA+j+i) = row;
            *(invsqA+j+i) = invrow;

            i++;
        }
    }
		print(sqA,3,3);

    // Gauss Jordan method
    for(int i=0;i<b;i++){
        // Scale
        pivot = *(*(sqA+i)+i);
				printf("pivot : %f\n",pivot);
        if(pivot!=1.){
            for(int j=0;j<b;j++){
                *(*(invsqA+i)+j)/=pivot;
                *(*(sqA+i)+j)/=pivot;
            }
        }
        // Subtraction
        for(int j=0;j<b;j++){
            if(j!=i){
                double target = *(*(sqA+j)+i);
                for(int k=0;k<b;k++){
                    *(*(invsqA+j)+k) -= *(*(invsqA+i)+k) * target;
                    *(*(sqA+j)+k) -= *(*(sqA+i)+k) * target;
                }
            }
        }
    }

    result = matmul(invsqA, A_t, b,b,a);

    return result;
}

double** zero(int a, int b){
    static double** result;
    
    result = new double*[a];
    for(int i=0;i<a;i++) *(result+i) = new double [b];

    for(int i=0;i<a;i++){
        for(int j=0;j<b;j++) *(*(result+i)+j) = 0.;
    }
    
    return result;
}

void print(double** A, int a, int b){
    for(int i=0;i<a;i++){
        for(int j=0;j<b;j++) printf("%10.4e ", *(*(A+i)+j));
        printf("\n");
    }
}

