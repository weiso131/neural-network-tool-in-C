#include "nn.h"


int main(){
    nn_node* relu_obj = ReLU_init();
    Act_func *relu = (Act_func*)relu_obj->nn_menber;
    
    Matrix *testReLUVec = create(4, 1);
    double testReLUVec_entry[] = {4.8763, -4.8763, 114.514, -114.514};
    testReLUVec->entry = testReLUVec_entry;
    printf("test relu forward\n");
    print_matrix(relu->forward(relu, testReLUVec));
    printf("test relu backward\n");
    print_matrix(relu->backward(relu, testReLUVec));
}