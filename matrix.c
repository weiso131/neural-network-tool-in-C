#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<omp.h>

#include "matrix.h"




Matrix* create(int row, int col, size_t size, number_t type){
    Matrix* m = malloc(sizeof(Matrix));
    *m = (Matrix){row, col, size, type, malloc(sizeof(void*))};
    m->entry = malloc(row * col * size);
    return m;
}



Matrix* dot(Matrix* m1, Matrix* m2){
    if (m1->row != m2->row || m1->col != m2->col || m1->type != m2->type) 
        return NULL;

    Matrix* result = create(m1->row, m1->col, m1->size, m1->type);

    for (int i = 0;i < m1->row * m1->col;++i)
        entryOperation(result->entry, m1->entry, m2->entry, i, i, i, m1->type, *)
    return result;

}



void print_float(float* value){
    printf("%f ", *value);
}

void print_int(int* value){
    printf("%d ", *value);
}

void print_double(double* value){
    printf("%lf ", *value);
}








