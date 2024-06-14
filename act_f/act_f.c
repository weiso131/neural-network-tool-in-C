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
Matrix* relu_backward(ReLU *self, Matrix* dz, Matrix* x, optim* optimizer){
    Matrix* act_PD = apply(x, relu_backward_impl);//activate function partial derivative
    Matrix* output = dot(dz, act_PD);
    free_matrix(act_PD);
    return output;

}