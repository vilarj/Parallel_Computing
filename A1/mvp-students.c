#include <stdio.h>
#include <stdlib.h>
#include "mvp.h"

void assignMatrix2(double** mat, double* vec, int n) {
    for (int i = 0; i < n; i++) {
        vec[i] = 1;

        for (int k = 0; k < n; k++) {
            if (i == k) {mat[i][k] = 2;}
            else if (k == i+1) {mat[i][k] = 1;}
            else if (k == i-1) {mat[i][k] = 1;}
            else {mat[i][k] = 0;}
        } 
    }
}

void assignMatrix1(double* mat, double* vec, int n) {
    for (int i = 0; i < n; i++) {
        vec[i] = 1;

        for (int k = 0; k < n; k++) {
            if (i == k) {mat[i * n + k] = 2;}
            else if (k == i+1) {mat[i * n + k] = 1; }
            else if (k == i-1) {mat[i * n + k] = 1;}
            else {mat[i * n + k] = 0;}
        }
    }
} 

void printMatVec2(double** mat, double* vec, double* res, int n) {
    for (int i = 0; i < n; i++) {
        for (int k = 0; i < n; k++) {printf("%5.2f ", mat[i][k]);}
        
        if (i == n/2) {printf("%5.2f = %5.2f \n", vec[i], res[i]);}
        else {printf("%5.2f     %5.2f\n", vec[i], res[i]);}
    }
    
}

void printMatVec1(double* mat, double* vec, double* res, int n) {
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            printf("%5.2f ", mat[i * n * k]);
        }
        if(i == n/2) {printf("  %5.2f = %5.2f\n", vec[i], res[i]);}
        else {printf("  %5.2f   %5.2f\n", vec[i], res[i]);}
    }
}

double* mvp1(double* mat, double* vec, int n) {
    double *resms = (double*) malloc(n * sizeof(double*));
    double sum = 0;

    for (int i = 0; i < n; i++) {
        sum = 0;

        for (int k = 0; k < n; k++) {sum += mat[i * n + k] *  vec[k];}
        resms[i] = sum;
    }

    return resms;
}

double* mvp2(double** mat, double* vec, int n) {
    double *resms = (double*) malloc(n * sizeof(double));
    

    return resms;
}

void freeMatrix(void **mat, int n) {
    for (int i = 0; i < n; i++) {free(mat);}
}

//Main function
int main(int argc, char **argv) {
    double* vec;
    double** mat2;

    int n=5;

    printf("Matrix-Vector product using int** matrix:\n");

    vec  = (double*) malloc(n * sizeof(double*));
    mat2 = (double**) malloc(n * sizeof(double**));

    for(int i=0;i<n;i++)
        mat2[i] =  (double**) malloc(n * sizeof(double**));

    assignMatrix2(mat2,vec,n);

    double* resms = mvp2(mat2,vec,n);
    
    printMatVec2(mat2,vec,resms,n);
    printf("\n");
    freeMatrix((void**)mat2,n);

    printf("Matrix-Vector product using int* matrix:\n");
    
    double* mat1;
    mat1 = (double*) malloc(n*n*sizeof(double));

    assignMatrix1(mat1, vec, n);
    double* res=mvp1(mat1, vec, n);
    printMatVec1(mat1, vec, res, n);
    printf("\n");

    free(mat1);
    free(vec);
    free(resms);

    return 0;
}