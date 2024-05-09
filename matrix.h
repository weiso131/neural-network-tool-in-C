#include "number.h"

#ifndef MATRIX_H
#define MATRIX_H



typedef struct{
    int row, col;
    number_t type;
    number* entry;
}Matrix;

Matrix* create(int, int, size_t);
void fill(Matrix*, double);
void print_matrix(Matrix*);


void copy(Matrix* , Matrix* , size_t);

#endif