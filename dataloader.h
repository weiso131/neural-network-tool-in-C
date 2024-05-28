#include "matrix/matrix.h"
#ifndef DATALOADER_H
#define DATALOADER_H

typedef struct {
    Matrix *data, *label;
}batch_data;


typedef struct{
    Matrix **data, **label;
    int batch_size, data_length;//一個batch的大小,資料的數量
    int *indice;//資料的順序，有shuffle可以把順序打亂
    batch_data* (*get_batch)(dataloader*, int);//train的時候迭代這些資料

}dataloader;

dataloader* init_dataloader(Matrix **data, Matrix **label, int batch_size, int data_length, int shuffle);


//迭代器



#endif