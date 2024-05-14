#include<stdio.h>
#include<string.h>

#include<omp.h>

#include "matrix.h"

Matrix* create(int row, int col, size_t size, number_t type){
    Matrix* m = malloc(sizeof(Matrix));
    *m = (Matrix){row, col, size, type, malloc(sizeof(void*))};
    m->entry = malloc(row * col * size);
    return m;
}
Matrix* identity(int n, size_t size, number_t type){
    Matrix* m = create(n, n, size, type);
    switch (type){
    case SHORT:
        identity_fill(m, short)
        break;
    case INT:
        identity_fill(m, int)
        break;
    case FLOAT:
        identity_fill(m, float)
        break;
    case DOUBLE:
        identity_fill(m, double)
        break;
    default:
        identity_fill(m, long long)
        break;
    }
    return m;
}

Matrix* copy(Matrix* m){
    Matrix *p = create(m->row, m->col, m->size, m->type);
    char *tar = p->entry, *end = tar + m->row * m->col * m->size, *src = m->entry;
    for (;tar != end;tar++, src++)
        *tar = *src;
    return p;
}

#define index_value_compare(type){\
    int bigger = *((type*)matrix->entry + i * mul_i + j * mul_j) > *((type*)matrix->entry + i * mul_i + maxIndex * mul_j);\
    maxIndex = (1 - bigger) * maxIndex + bigger * j;\
}

Matrix* argmax(Matrix* matrix, int dim){
    int n = matrix->row * (1 - dim) + matrix->col * dim, \
        m = matrix->col * (1 - dim) + matrix->row * dim, \
        mul_i = matrix->col * (1 - dim) + dim, \
        mul_j = matrix->col * dim + (1 - dim);

    Matrix *argmaxArray = create(n, 1, sizeof(int), INT);

    for (int i = 0;i < n;i++){
        int maxIndex = 0;
        for (int j = 0;j < m;j++){
            switch (matrix->type){
            case SHORT:
                index_value_compare(short)
                break;
            case INT:
                index_value_compare(int)
                break;
            case FLOAT:
                index_value_compare(float)
                break;
            case DOUBLE:
                index_value_compare(double)
                break;
            default:
                index_value_compare(long long)
                break;
            }\
        }
        *((int*)argmaxArray->entry + i) = maxIndex;

    }
    

    return argmaxArray;
    
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








