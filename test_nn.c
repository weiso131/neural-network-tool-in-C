#include "nn.h"


int main(){
    nn_node* relu_obj = ReLU_init();
    Act_func *relu = (Act_func*)relu_obj->nn_menber;
    
    Matrix *testReLUVec = create(4, 1);
    double testReLUVec_entry[] = {4.8763, -4.8763, 114.514, -114.514};
    testReLUVec->entry = testReLUVec_entry;
    printf("test relu forward\n");
    print_matrix(relu->forward(relu, testReLUVec));

    Matrix *testSoftmaxVec = create(10, 1);
    double testSoftmaxVec_entry[] = {4, 8, 7, 6, 3, 4, 8, 7, 6, 3};
    testSoftmaxVec->entry = testSoftmaxVec_entry;

    nn_node* softmax_obj = softmax_init();
    Softmax *softmax = (Softmax*)softmax_obj->nn_menber;

    printf("test softmax:\n");
    print_matrix(softmax->forward(softmax, testSoftmaxVec));

    nn_node *drop_obj = drop_init(0.1);
    Drop *drop = (Drop*)drop_obj->nn_menber;

    printf("test drop forward:\n");
    print_matrix(drop->forward(drop, testSoftmaxVec));



    Matrix *testLinearForwardVec = create(10, 1);
    testLinearForwardVec->entry = testSoftmaxVec_entry;

    Matrix *w = create(1, 10);
    w->entry = testSoftmaxVec_entry;
    Matrix *b = create(1, 1);
    double b_entry[] = {1.0};
    b->entry = b_entry;

    nn_node *linear_obj = Linear_init(1, 10, w, b);
    Linear *linear = (Linear*)linear_obj->nn_menber;

    printf("test linear forward:\n");
    print_matrix(linear->forward(linear, testLinearForwardVec));

}
//gcc test_nn.c linear.c softmax.c drop.c act_f/act_f.c act_f/act_f_impl.c matrix/matrix.c matrix/matrix_ops.c -o test_nn -lm