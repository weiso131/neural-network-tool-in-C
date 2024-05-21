#include "matrix.h"

Matrix* create(int row, int col){
    Matrix* m = malloc(sizeof(Matrix));
    *m = (Matrix){row, col, malloc(sizeof(double*))};
    m->entry = malloc(row * col * sizeof(double));
    return m;
}
Matrix* identity(int n){
    Matrix* matrix = create(n, n);
    for (int i = 0;i < matrix->row;i++)
        for (int j = 0;j < matrix->col;j++)
            *((matrix->entry) + i * matrix->col + j) = (double)(i == j);
    return matrix;
}

Matrix* copy(Matrix* m){
    Matrix *p = create(m->row, m->col);
    double *tar = p->entry, *end = tar + m->row * m->col, *src = m->entry;
    for (;tar != end;tar++, src++)
        *tar = *src;
    return p;
}

Matrix* argmax(Matrix* matrix, int dim){
    int n = matrix->row * (1 - dim) + matrix->col * dim, \
        m = matrix->col * (1 - dim) + matrix->row * dim, \
        mul_i = matrix->col * (1 - dim) + dim, \
        mul_j = matrix->col * dim + (1 - dim);

    Matrix *argmaxArray = create(n, 1);

    for (int i = 0;i < n;i++){
        int maxIndex = 0;
        for (int j = 0;j < m;j++){
            int bigger = *(matrix->entry + i * mul_i + j * mul_j) > *(matrix->entry + i * mul_i + maxIndex * mul_j);
            maxIndex = (1 - bigger) * maxIndex + bigger * j;
        }
        *(argmaxArray->entry + i) = maxIndex;

    }
    return argmaxArray;
    
}









