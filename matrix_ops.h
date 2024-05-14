#include "matrix.h"
#ifndef MATRIX_OPS_H
#define MATRIX_OPS_H

typedef double (*act_f) (Matrix *x);



Matrix* mul(Matrix*, Matrix*);
Matrix* add(Matrix*, Matrix*);
Matrix* dot(Matrix*, Matrix*);
Matrix* scale(Matrix*, double);
Matrix* addScalar(Matrix*, double);

Matrix* apply(Matrix*, act_f);
Matrix* transpose(Matrix*);
#endif