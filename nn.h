
#include "matrix/matrix.h"
#include "matrix/matrix_ops.h"
#ifndef NN_H
#define NN_H
typedef enum {
    LINEAR,
    ACTIVATE,
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
    nn_node (*drop)(double);//drop的機率
    nn_node (*softmax)();


}nn;
//nn是一個輔助物件 裡面存有一堆funtion的生成器 呼叫後會給出對應的nn_node

nn* create_nn();

nn_node Linear_impl(int, int);//n, m
nn_node ReLU_impl();
nn_node sigmoid_impl();
nn_node drop_impl(double);
nn_node softmax_impl();

typedef struct{
    Matrix *w;//n x m
    Matrix *b;//n x 1
    Matrix* (*forward)(Linear*, Matrix*);
    Matrix* (*w_backward)(Linear*, Matrix*, Matrix*);
    Matrix* (*b_backward)(Linear*, Matrix*);
    /*
    forward:
        輸入一個matrix x
        計算mul(w, x) + b並輸出該結果

    w_backward:
        輸入兩個matrix分別代表:
        1. 該層輸出Z的導數dZ
        2. 上一層輸出經過活化函數在轉置的g(Z)T

        根據公式計算dW並輸出

    b_backward:
        輸入matrix代表該層輸出Z的導數dZ
        
        根據公式計算db並輸出

    關於反向傳播的update:
        考量optimizor的實作，先把dW,db算出來
        再交由train內部實作:
        w = w - optim_name->optimize(optim_name, dW, lr);
        b = b - optim_name->optimize(optim_name, db, lr);
    */
}Linear; 

typedef struct{
    Matrix* (*forward)(ReLU*, Matrix*);
    Matrix* (*backward)(ReLU*, Matrix*);
}ReLU;

typedef struct{
    Matrix* (*forward)(Sigmoid*, Matrix*);
    Matrix* (*backward)(Sigmoid*, Matrix*);
}Sigmoid;

/*
活化函數
    forward
        實作把輸入帶入對應的活化函數再輸出
    backward
        實作把輸入帶入對應的活化函數的導數再輸出

*/

typedef struct{
    double drop_rate;//(0, 1)
    Matrix* (*forward)(Drop*, Matrix*);
}Drop;

/*
drop:
    forward
        輸入matrix上的每個數值都有固定機率drop_rate變成0再輸出
*/

typedef struct{
    Matrix* (*forward)(Softmax*, Matrix*);
}Softmax;




#endif