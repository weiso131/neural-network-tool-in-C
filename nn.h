
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

typedef struct nn_node_{
    struct nn_node_ *prev, *next;
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



typedef struct linear_{
    Matrix *w;//n x m
    Matrix *b;//n x 1
    Matrix* (*forward)(struct linear_* self, Matrix* x);
    Matrix* (*w_backward)(struct linear_* self, Matrix* x, Matrix* dz);
    Matrix* (*b_backward)(struct linear_* self, Matrix* dz);
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
nn_node* Linear_init(int n, int m, Matrix* specify_w, Matrix* specify_b);//n, m, 指定w, 指定b
Matrix* Linear_forward(struct linear_* self, Matrix* x);
Matrix* Linear_w_backward(struct linear_* self, Matrix* x, Matrix* dz);
Matrix* Linear_b_backward(struct linear_* self, Matrix* dz);
typedef struct act_func_{
    Matrix* (*forward)(struct act_func_* self, Matrix* x);
    Matrix* (*backward)(struct act_func_* self, Matrix* x);
    double slope;
}Act_func;
//統一的活化函數結構，單純方便使用

typedef struct relu_{
    Matrix* (*forward)(struct relu_*, Matrix*);
    Matrix* (*backward)(struct relu_*, Matrix*);
}ReLU;
nn_node* ReLU_init();
Matrix* relu_forward(ReLU *self, Matrix *x);
Matrix* relu_backward(ReLU *self, Matrix *x);

typedef struct sigmoid_{
    Matrix* (*forward)(struct sigmoid_*, Matrix*);
    Matrix* (*backward)(struct sigmoid_*, Matrix*);
}Sigmoid;
nn_node* sigmoid_init();
Matrix* sigmoid_forward(ReLU *self, Matrix *x);
Matrix* sigmoid_backward(ReLU *self, Matrix *x);

/*
活化函數
    forward
        實作把輸入帶入對應的活化函數再輸出
    backward
        實作把輸入帶入對應的活化函數的導數再輸出

*/

typedef struct drop_{
    double drop_rate;//(0, 1)
    Matrix* (*forward)(struct drop_* self, Matrix* x);
}Drop;
nn_node* drop_init(double);
Matrix *drop_forward(Drop* self, Matrix *x);
Matrix *drop_backward(Drop* self, Matrix *x);
/*
drop:
    forward
        輸入matrix上的每個數值都有固定機率drop_rate變成0再輸出
    backward
        https://blog.csdn.net/mch2869253130/article/details/119809360
*/

typedef struct softmax_{
    Matrix* (*forward)(struct softmax_* self, Matrix* x);
}Softmax;
nn_node* softmax_init();
Matrix* softmax_forward(struct softmax_* self, Matrix* x);



#endif