
#include "matrix_ops.h"
#include "omp.h"

const int THREAD_NUM = 4;

#define sizeCheck(warning){\
    if (!(m1->row == m2->row && m1->col == m2->col) && \
    !(m2->col == m1->col && m2->row == 1) && !(m2->row == m1->row && m2->col == 1)\
    && !(m2->row == 1 && m2->col == 1)){\
        printf(warning);\
        return NULL;\
    }\
}
#define operation(oper)\
for (int _i = 0;_i < m1->row;++_i)\
    for (int _j = 0;_j < m1->col;++_j)\
        *((result->entry) + _i * m1->col + _j) = \
        *((m1->entry) + _i * m1->col + _j) oper *((m2->entry) + (_i % m2->row) * m2->col + (_j % m2->col));\


Matrix* mul(Matrix* m1, Matrix* m2){
    //size _Check
    if (m1->col != m2->row){
        printf("mul return NULL\n");
        return NULL;
    }
    Matrix* result = create(m1->row, m2->col);
    #pragma omp parallel for schedule(static)
    for (int i = 0;i < m1->row;i++){
        for (int j = 0;j < m2->col;j++){
            *(result->entry + i * m2->col + j) = 0;
            for (int k = 0;k < m1->col;k++)
                *(result->entry + i * m2->col + j) += \
                *(m1->entry + i * m1->col + k) * *(m2->entry + k * m2->col + j);
        }
    }
    return result;
}

Matrix* dot(Matrix* m1, Matrix* m2){
    sizeCheck("dot return NULL");
    Matrix* result = create(m1->row, m1->col);
    #pragma omp parallel for schedule(static)
    operation(*);
    return result;
}

Matrix* scale(Matrix* m1, double x){
    Matrix* result = create(m1->row, m1->col);
    #pragma omp parallel for schedule(static)
    for (int i = 0;i < m1->col * m1->row;++i)
        *(result->entry + i) = *(m1->entry + i) * x;
    return result;
}

Matrix* add(Matrix* m1, Matrix* m2){
    sizeCheck("add return NULL");
    Matrix* result = create(m1->row, m1->col);
    #pragma omp parallel for schedule(static)
    operation(+);
    return result;
}

Matrix* sub(Matrix* m1, Matrix* m2){
    sizeCheck("sub return NULL");
    Matrix* result = create(m1->row, m1->col);
    #pragma omp parallel for schedule(static)
    operation(-);
    return result;
}

Matrix* addScale(Matrix* m1, double x){
    Matrix* result = create(m1->row, m1->col);
    #pragma omp parallel for schedule(static)
    for (int i = 0;i < m1->col * m1->row;++i)
        *(result->entry + i) = *(m1->entry + i) + x;
    return result;
}

Matrix *apply(Matrix *m1, act_f f){
    Matrix* result = create(m1->row, m1->col);
    #pragma omp parallel for schedule(static)
    for (int i = 0;i < m1->col * m1->row;++i)
        *(result->entry + i) = f(*(m1->entry + i));
    return result;
}

Matrix *transpose(Matrix *m1){
    Matrix* result = create(m1->row, m1->col);
    #pragma omp parallel for schedule(static)

    for (int i = 0;i < m1->row;++i)
        for (int j = 0;j < m1->col;++j)
            *(result->entry + i * m1->col + j) = *(m1->entry + j * m1->row + i);
    return result;
}

