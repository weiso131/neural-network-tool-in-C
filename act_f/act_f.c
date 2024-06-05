#include "../nn.h"
#include "act_f_impl.h"
nn_node* ReLU_init(){
    ReLU* relu = malloc(sizeof(ReLU));
    *relu = (ReLU){relu_forward, relu_backward};

    nn_node* relu_node = malloc(sizeof(nn_node));
    *relu_node = (nn_node){NULL, NULL, relu, ACTIVATE};

    return relu_node;
}

Matrix* relu_forward(ReLU *self, Matrix *x){
    return apply(x, relu_forward_impl);
}
Matrix* relu_backward(ReLU *self, Matrix *x){
    return apply(x, relu_backward_impl);
}