#include"nn.h"
#include <stdint.h>
#include<math.h>
#define double_int union{double d;int64_t i;}
double doubleMax(double a, double b){
    double_int a_union = {.d = a};
    double_int b_union = {.d = b};
    double_int diff = {.d = a - b};

    a_union.i &= ~(diff.i >> 63);
    b_union.i &= (diff.i >> 63);
    return a_union.d + b_union.d;

}

nn_node* softmax_init(){
    Softmax* softmax = malloc(sizeof(Softmax));
    *softmax = (Softmax){softmax_forward};

    nn_node* softmax_node = malloc(sizeof(nn_node));
    *softmax_node = (nn_node){NULL, NULL, softmax, SOFTMAX};

    return softmax_node;
}

Matrix* softmax_forward(Softmax *self, Matrix *x){
    Matrix* output = create(x->row, x->col);
    double maxElement = -1e9, sum = 0;
    for (int i = 0;i < x->col * x->row;i++) maxElement = doubleMax(maxElement, x->entry[i]);
    for (int i = 0;i < x->col * x->row;i++) sum += exp(x->entry[i] - maxElement);
    for (int i = 0;i < x->col * x->row;i++) output->entry[i] = exp(x->entry[i] - maxElement) / sum;
    return output;
}



