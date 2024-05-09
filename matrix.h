

#ifndef MATRIX_H
#define MATRIX_H

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

#define print_matrix(matrix, type){\
    int rows = matrix->row, cols = matrix->col;\
    for (int i = 0;i < rows;i++){\
        for (int j = 0;j < cols;j++)\
            print_##type((type*)matrix->entry + i * cols + j);\
        printf("\n");\
    }\
}/*見泰迪熊實作*/
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

Matrix* create(int, int, size_t, number_t);
Matrix* dot(Matrix*, Matrix*);
void print_float(float*);
void print_int(int*);
void print_double(double*);
#endif