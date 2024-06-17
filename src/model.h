#include "nn.h"
#include "dataloader.h"
#include "optimizer.h"
#include "loss_function.h"

#ifndef MODEL_H
#define MODEL_H

typedef struct model_{
    nn_node *begin, *end;
    void (*add)(struct model_ *self, nn_node*);
    Matrix* (*predict)(struct model_ *self, Matrix*);
    void (*train)(struct model_ *self, optim* optimizer, int epoch, dataloader* train_data, dataloader* valid_data, loss_f* loss_function);//optimizor, epoch, train_dataloader, valid_dataloader, loss_function
    
}Model;
//模型本身 紀錄一串nn_node的頭跟尾 以及


void model_add_impl(Model *self, nn_node* newNode);
/*
加入新的模型元素
    使用者傳入newNode的指標，把該指標接到linklist上面
*/

Matrix* predict_impl(Model *self, Matrix *data);
/*
進行預測:
    對於給定的輸入
    將data丟給linklist從頭走一遍
    預測其答案
    答案會是一個matrix

*/


void train_impl(Model *self, optim*, int, dataloader*, dataloader*, loss_f*);
/*

*/


Model* init_model();
#endif