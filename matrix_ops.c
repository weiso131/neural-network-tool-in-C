
#include "matrix.h"
#include "matrix_ops.h"
Matrix* dot(Matrix* m1, Matrix* m2){
    if (m1->row != m2->row || m1->col != m2->col || m1->type != m2->type) 
        return NULL;

    Matrix* result = create(m1->row, m1->col, m1->size, m1->type);

    for (int i = 0;i < m1->row * m1->col;++i)
        entryOperation(result->entry, m1->entry, m2->entry, i, i, i, m1->type, *)
    return result;

}