#include "matrix.h"
#ifndef MATRIX_OPS_H
#define MATRIX_OPS_H

typedef double (*act_f) (double x);



Matrix* mul(Matrix*, Matrix*);
Matrix* add(Matrix*, Matrix*);
Matrix* sub(Matrix*, Matrix*);
Matrix* dot(Matrix*, Matrix*);

Matrix* scale(Matrix*, double);
//乘上純量

Matrix* addScalar(Matrix*, double);
//加上純量

Matrix* apply(Matrix*, act_f);
Matrix* transpose(Matrix*);
Matrix* softmax(Matrix *x);
#endif