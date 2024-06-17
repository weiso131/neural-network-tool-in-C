#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#ifndef MATRIX_H
#define MATRIX_H


typedef struct{
    int row, col;
    double* entry;
}Matrix;



#define flatten_matrix(matrix){\
    matrix->row = matrix->row * matrix->col;\
    matrix->col = 1;\
}

#define free_matrix(matrix){\
    free(matrix->entry);\
    free(matrix);\
    matrix = NULL;\
}

void fill(Matrix *matirx, double value);

void random_fill(Matrix *matrix);

void print_matrix(Matrix *matrix);

Matrix* init_matrix(int, int);
//創建一個新的矩陣

Matrix* identity(int);
//創建一個單位矩陣

Matrix* copy(Matrix*);
//創建一個新的矩陣，把舊的矩陣的entry複製過去

Matrix* argmax(Matrix*, int);
//dim 決定在哪個維度取值
//回傳值是個int的array指標，帶表那裏最大值所在的index


double NormalDistributionRand();
//常態分布
//泰迪

#endif