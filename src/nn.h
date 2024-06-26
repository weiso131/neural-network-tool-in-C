
#include "matrix/matrix.h"
#include "matrix/matrix_ops.h"
#include "optimizer.h"
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

typedef struct linear_{
    Matrix *w;//n x m
    Matrix *b;//n x 1
    Matrix *vdw;//n x m
    Matrix *sdw;//n x m
    Matrix *vdb;//n x 1
    Matrix *sdb;//n x 1
    Matrix* (*forward)(struct linear_* self, Matrix* x);
    Matrix* (*backward)(struct linear_* self, Matrix* dz, Matrix* x, optim* optimizer);
    
}Linear; 
/*
    forward:
        輸入一個matrix x
        計算mul(w, x) + b並輸出該結果

    backward:
        輸入dz, x, optimzizer
        dz是下一層反向傳播回來的東西
        x是上一層的輸出
        optimizer是optimizer

        丟進去更新w, b
        然後計算W^TdZ並回傳

*/
nn_node* init_Linear(int input_dim, int output_dim, Matrix* specify_w, Matrix* specify_b);//n, m, 指定w, 指定b
Matrix* Linear_forward(struct linear_* self, Matrix* x);
Matrix* Linear_backward(struct linear_* self, Matrix* dz, Matrix* x, optim* optimizer);
typedef struct act_func_{
    Matrix* (*forward)(struct act_func_* self, Matrix* x);
    Matrix* (*backward)(struct act_func_* self, Matrix* dz, Matrix* x, optim* optimizer);
    double slope;
}Act_func;
/*
    統一的活化函數結構，單純方便使用
    forward:
        輸入一個matrix x
        計算g(x)並輸出該結果
    backward:
        輸入dz, x, optimzizer
        dz是下一層反向傳播回來的東西
        x是上一層的輸出
        optimizer是NULL(反正用不到，單純統一backward格式)
        
        計算dZ並回傳
*/



typedef struct relu_{
    Matrix* (*forward)(struct relu_* self, Matrix* x);
    Matrix* (*backward)(struct relu_* self, Matrix* dz, Matrix* x, optim* optimizer);
}ReLU;
nn_node* init_ReLU();
Matrix* relu_forward(ReLU *self, Matrix *x);
Matrix* relu_backward(ReLU *self, Matrix* dz, Matrix* x, optim* optimizer);

typedef struct sigmoid_{
    Matrix* (*forward)(struct sigmoid_* self, Matrix* x);
    Matrix* (*backward)(struct sigmoid_* self, Matrix* dz, Matrix* x, optim* optimizer);
}Sigmoid;
nn_node* init_sigmoid();
Matrix* sigmoid_forward(Sigmoid *self, Matrix *x);
Matrix* sigmoid_backward(Sigmoid *self, Matrix* dz, Matrix* x, optim* optimizer);




typedef struct drop_{
    double drop_rate;//(0, 1)
    Matrix* drop_matrix;
    Matrix* (*forward)(struct drop_* self, Matrix* x);
    Matrix* (*backward)(struct drop_* self, Matrix* dz, Matrix* x, optim* optimizer);
}Drop;
nn_node* init_drop(double);
Matrix *drop_forward(Drop* self, Matrix *x);
Matrix *drop_backward(Drop* self, Matrix* dz, Matrix* x, optim* optimizer);
/*
drop:
    forward
        輸入matrix上的每個數值都有固定機率drop_rate變成0再輸出
        並將每個元素是否被drop存在drop_matrix裡
        存的時候順便/(1-drop_rate) 這樣backward時的答案就是drop_matrix了
    backward
        https://blog.csdn.net/mch2869253130/article/details/119809360
        輸入dz, x, optimzizer
        dz是下一層反向傳播回來的東西
        x是上一層的輸出
        optimizer是NULL(反正用不到，單純統一backward格式)
        
        計算dZ並回傳
        
*/




#endif
