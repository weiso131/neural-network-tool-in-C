#include "nn.h"
#include "loss_function.h"
void test_lenear(){
    optim* optimizer = init_Adam(0.01, 0.9, 0.999, 1e-8);
    loss_f* loss_function = init_MSELoss();
    Matrix* weight = create(3, 5);
    Matrix* bias = create(3, 1);
    fill(weight, 0.5);
    fill(bias, 0.1);
    nn_node* linear_obj = Linear_init(3, 5, weight, bias);
    Linear* linear = (Linear*)linear_obj->nn_menber;

    //data
    Matrix* input = create(5, 1);
    Matrix* target = create(3, 1);
    double input_entry[] = {0.1, 0.5, 0.6, 0.89, 0.34};
    double target_entry[] = {1.0, 0.0, 0.0};
    input->entry = input_entry;
    target->entry = target_entry;

    Matrix* output = linear->forward(linear, input);
    
    printf("\nTest linear:\ntest forward:\n"); 
    print_matrix(output);

    Matrix* dz = loss_function->get_gredient(output, target);
    double loss = loss_function->get_loss_item(output, target);
    printf("loss:%lf\nloss gredient:\n", loss);
    print_matrix(dz);


    linear->backward(linear, dz, input, optimizer);

    printf("weight backward result:\n");
    print_matrix(linear->w);
    printf("bias backward result:\n");
    print_matrix(linear->b);


    for (int i = 0;i < 1000;i++){
        output = linear->forward(linear, input);
        if ((i + 1) % 100 == 0){
            loss = loss_function->get_loss_item(output, target);
            printf("epoch:%d, loss%lf\n", i, loss);
            print_matrix(output);
        }
            
        dz = loss_function->get_gredient(output, target);
        Matrix* forUpdate = linear->backward(linear, dz, input, optimizer);
        free_matrix(output);
        free_matrix(dz);
        free_matrix(forUpdate);
    }
}

int main(){
    nn_node* relu_obj = ReLU_init();
    Act_func *relu = (Act_func*)relu_obj->nn_menber;
    
    Matrix *testReLUVec = create(4, 1);
    double testReLUVec_entry[] = {4.8763, -4.8763, 114.514, -114.514};
    testReLUVec->entry = testReLUVec_entry;
    printf("test relu forward\n");
    print_matrix(relu->forward(relu, testReLUVec));

    printf("test relu backward\n");
    print_matrix(relu->backward(relu, testReLUVec, testReLUVec, NULL));

    Matrix *testSoftmaxVec = create(10, 1);
    double testSoftmaxVec_entry[] = {4, 8, 7, 6, 3, 4, 8, 7, 6, 3};
    testSoftmaxVec->entry = testSoftmaxVec_entry;



    nn_node *drop_obj = drop_init(0.1);
    Drop *drop = (Drop*)drop_obj->nn_menber;

    printf("test drop forward:\n");
    print_matrix(drop->forward(drop, testSoftmaxVec));

    test_lenear();

    
    

}
//gcc test_nn.c linear.c softmax.c drop.c act_f/act_f.c act_f/act_f_impl.c matrix/matrix.c matrix/matrix_ops.c loss_function.c optimizer.c -o test_nn -lm