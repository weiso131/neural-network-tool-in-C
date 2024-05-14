
#include "matrix_ops.h"
#include "omp.h"

const int THREAD_NUM = 4;

#define sizeCheck(warning){\
    if (!(m1->row == m2->row && m1->col == m2->col) && \
    !(m2->col == m1->col && m2->row == 1) && !(m2->row == m1->row && m2->col == 1)){\
        printf(warning);\
        return NULL;\
    }\
}

Matrix* dot(Matrix* m1, Matrix* m2){
    sizeCheck("dot return NULL")
    Matrix* result = create(m1->row, m1->col);
    omp_set_num_threads(THREAD_NUM);
    #pragma omp parallel for schedule(static)
    for (int i = 0;i < m1->row;++i){
        for (int j = 0;j < m1->col;++j)
            *((result->entry) + i * m1->col + j) = \
            *((m1->entry) + i * m1->col + j) * *((m2->entry) + (i % m2->row) * m2->col + (j % m2->col));
    }
        
    return result;
}
Matrix* add(Matrix* m1, Matrix* m2){
    sizeCheck("add return NULL")
    Matrix* result = create(m1->row, m1->col);

    omp_set_num_threads(THREAD_NUM);

    #pragma omp parallel for schedule(static)
    for (int i = 0;i < m1->row;++i){
        for (int j = 0;j < m1->col;++j)
            *((result->entry) + i * m1->col + j) = \
            *((m1->entry) + i * m1->col + j) + *((m2->entry) + (i % m2->row) * m2->col + (j % m2->col));
    }
    return result;
}