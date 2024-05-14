
#include "matrix.h"
#include "matrix_ops.h"
Matrix* dot(Matrix* m1, Matrix* m2){
    if (m1->row != m2->row || m1->col != m2->col) 
        return NULL;

    Matrix* result = create(m1->row, m1->col);

    for (int i = 0;i < m1->row * m1->col;++i)
        *((result->entry) + i) = *((m1->entry) + i) * *((m2->entry) + i);
    return result;

}