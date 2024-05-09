#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "matrix.h"
#include "number.h"


Matrix* create(int row, int col, number_t type){
    Matrix* m = malloc(sizeof(Matrix));
    *m = (Matrix){row, col, type, malloc(sizeof(number*))};
    m->entry = malloc(row * col * sizeof(number));
    return m;
}


void fill(Matrix* matrix, double value){
    for (int i = matrix->row * matrix->col; i--;)
        number_set(matrix->entry[i], value, matrix->type)
}

void print_matrix(Matrix* matrix){
    int rows = matrix->row, cols = matrix->col;\
    for (int i = 0;i < rows;i++){
        for (int j = 0;j < cols;j++){
            number_print(matrix->entry[i * cols + j], matrix->type)
            printf(" ");
        }
        printf("\n");
    }
}



