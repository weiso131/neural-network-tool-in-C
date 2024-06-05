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

    Matrix *testSoftmaxVec = create(5, 1);
    double testSoftmaxVec_entry[] = {4, 8, 7, 6, 3};
    testSoftmaxVec->entry = testSoftmaxVec_entry;

    nn_node* softmax_obj = softmax_init();
    Softmax *softmax = (Softmax*)softmax_obj->nn_menber;

    printf("test softmax:\n");
    print_matrix(softmax->forward(softmax, testSoftmaxVec));

}