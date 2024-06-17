#include "src/loss_function.h"


int main(){
    loss_f* CE = init_CrossEntropy();
    Matrix* predict = init_matrix(4, 1);
    Matrix* label = init_matrix(4, 1);
    double predict_entry[] = {0.0418, 0.0057, 0.1135, 0.8390};
    double label_entry[] = {1, 0, 0, 0};
    predict->entry = predict_entry;
    label->entry = label_entry;

    printf("CE:%lf\ngradient:\n", CE->get_loss_item(predict, label));
    print_matrix(CE->get_gredient(predict, label));
    

    loss_f* MSELoss = init_MSELoss();

    printf("\nMSELoss:\n%lf\ngradient:\n", MSELoss->get_loss_item(predict, label));
    print_matrix(MSELoss->get_gredient(predict, label));


}
//答案跟pytorch一樣應該就沒問題了(吧


//gcc -fopenmp test_loss_function.c loss_function.c matrix/matrix.c matrix/matrix_ops.c -o test_loss_function