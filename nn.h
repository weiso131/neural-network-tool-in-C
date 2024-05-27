
#include "matrix/matrix.h"
#include "matrix/matrix_ops.h"
#ifndef NN_H
#define NN_H
typedef enum {
    LINEAR,
    RELU,
    SIGMOID,
    TANH,
    DROP,
    SOFTMAX,
}NNtype;

typedef struct {
    nn_node *prev, *next;
    void *nn_menber;
    NNtype menber_type;

}nn_node;
/*
nn_node 一個紀錄模型中所有操作的雙向linked list
nn_menber 操作的本體
menber_type 記錄他是甚麼操作
*/

typedef struct {
    nn_node (*Linear)(int, int); //代表輸入層與輸出層
    nn_node (*ReLU)();
    nn_node (*sigmoid)();
    nn_node (*tanh)();
    nn_node (*drop)(double);//drop的機率
    nn_node (*softmax)();


}nn;
//nn是一個輔助物件 裡面存有一堆funtion的生成器 呼叫後會給出對應的nn_node

nn* create_nn();

nn_node Linear_impl(int, int);
nn_node ReLU_impl();
nn_node sigmoid_impl();
nn_node tanh_impl();
nn_node drop_impl(double);
nn_node softmax_impl();

typedef struct{
    Matrix *w;
    Matrix *b;
    Matrix* (*forward)(Linear*, Matrix*);
    void (*backward)(Linear*, Matrix*, Matrix*, double);
}Linear;
#endif