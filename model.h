#include "nn.h"
#include "dataloader.h"
#include "optimizer.h"

#ifndef MODEL_H
#define MODEL_H
typedef struct {
    nn_node *begin, *end;
    void (*add)(nn_node*);
    Matrix* (*predict)(Matrix*);
    void (*train)(optim, int, dataloader*);//optimizor, epoch, dataloader
    
}Model;
//模型本身 紀錄一串teddy_node的頭跟尾 以及


void add_impl(Model *self, nn_node* newNode);
Matrix* predict_impl(Model *self, Matrix *data);
void train_impl(Model *self, optim, int, dataloader*);

Model* create_model();
#endif