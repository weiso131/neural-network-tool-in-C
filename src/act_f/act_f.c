#include "../nn.h"
#include "act_f_impl.h"
nn_node* init_ReLU(){
    ReLU* relu = malloc(sizeof(ReLU));
    *relu = (ReLU){relu_forward, relu_backward};

    nn_node* relu_node = malloc(sizeof(nn_node));
    *relu_node = (nn_node){NULL, NULL, relu, ACTIVATE};

    return relu_node;
}

Matrix* relu_forward(ReLU *self, Matrix *x){
    return apply(x, relu_forward_impl);
}
Matrix* relu_backward(ReLU *self, Matrix *dz, Matrix *x, optim *optimizer){
    
    Matrix* act_PD = apply(x, relu_backward_impl);//activate function partial derivative
    Matrix* output = dot(dz, act_PD);
    free_matrix(act_PD);
    return output;

}

nn_node* init_sigmoid(){
    Sigmoid* sigmoid = malloc(sizeof(Sigmoid));
    *sigmoid = (Sigmoid){sigmoid_forward, sigmoid_backward};

    nn_node* sigmoid_node = malloc(sizeof(nn_node));
    *sigmoid_node = (nn_node){NULL, NULL, sigmoid, ACTIVATE};

    return sigmoid_node;
}

Matrix* sigmoid_forward(Sigmoid *self, Matrix *x){
    return apply(x, sigmoid_forward_impl);
}
Matrix* sigmoid_backward(Sigmoid *self, Matrix *dz, Matrix *x, optim *optimizer){
    
    Matrix* act_PD = apply(x, sigmoid_backward_impl);//activate function partial derivative
    Matrix* output = dot(dz, act_PD);
    free_matrix(act_PD);
    return output;

}
