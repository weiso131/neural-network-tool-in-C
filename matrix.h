#include<stdlib.h>
#include<math.h>
#include<time.h>
#ifndef MATRIX_H
#define MATRIX_H

typedef enum {
    SHORT,
    INT,
    FLOAT,
    DOUBLE,
    LONGLONG
}number_t;
typedef struct{
    int row, col;
    size_t size;
    number_t type;
    void* entry;
}Matrix;


#define entryOperation(eNew, e1, e2, eNewIndex, e1Index, e2Index, type, oper){\
    switch (type){\
    case SHORT:\
        *((short*)(eNew) + eNewIndex) = \
        *((short*)(e1) + e1Index) oper *((short*)(e2) + e2Index);\
        break;\
    case INT:\
        *((int*)(eNew) + eNewIndex) = \
        *((int*)(e1) + e1Index) oper *((int*)(e2) + e2Index);\
        break;\
    case FLOAT:\
        *((float*)(eNew) + eNewIndex) = \
        *((float*)(e1) + e1Index) oper *((float*)(e2) + e2Index);\
        break;\
    case DOUBLE:\
        *((double*)(eNew) + eNewIndex) = \
        *((double*)(e1) + e1Index) oper *((double*)(e2) + e2Index);\
        break;\
    default:\
        *((long long*)(eNew) + eNewIndex) = \
        *((long long*)(e1) + e1Index) oper *((long long*)(e2) + e2Index);\
        break;\
    }\
}
#define fill(matrix, value, type){\
    for (int i = matrix->row * matrix->col; i--;)\
        *((type*)(matrix->entry) + i) = (type)value;\
}


#define random_fill(matrix, type){\
    /*一定是浮點數*/\
    srand(time(NULL));\
    for (int i = matrix->row * matrix->col; i--;)\
        *((type*)(matrix->entry) + i) = (type) ((double) rand() / (RAND_MAX) * 2 - 1);\
}

#define identity_fill(matrix, type){\
    for (int i = 0;i < matrix->row;i++)\
        for (int j = 0;j < matrix->col;j++)\
            *((type*)(matrix->entry) + i * matrix->col + j) = (type) (i == j);\
}
#define flatten_matrix(matrix){\
    matrix->row = matrix->row * matrix->col;\
    matrix->col = 1;\
}

#define free_matrix(matrix){\
    free(matrix->entry);\
    free(matrix);\
    matrix = NULL;\
}


#define print_matrix(matrix, type){\
    int rows = matrix->row, cols = matrix->col;\
    for (int i = 0;i < rows;i++){\
        for (int j = 0;j < cols;j++)\
            print_##type((type*)matrix->entry + i * cols + j);\
        printf("\n");\
    }\
}



Matrix* create(int, int, size_t, number_t);
//創建一個新的矩陣

Matrix* identity(int, size_t, number_t);
//創建一個單位矩陣

Matrix* copy(Matrix*);
//創建一個新的矩陣，把舊的矩陣的entry複製過去

Matrix* argmax(Matrix*, int);
//dim 決定在哪個維度取值
//回傳值是個int的array指標，帶表那裏最大值所在的index


double NormalDistributionRand();
//常態分布
//https://stackoverflow.com/questions/2325472/generate-random-numbers-following-a-normal-distribution-in-c-c



void print_float(float*);
void print_int(int*);
void print_double(double*);
#endif