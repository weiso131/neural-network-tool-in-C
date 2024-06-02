#include "loss_function.h"
#include <math.h>

Matrix* CrossEntropy_get_gredient(Matrix* output, Matrix* answer){
    return sub(output, answer);
}
double CrossEntropy_get_loss_item(Matrix* output, Matrix* answer){
    double ans = 0;
    for (int i = 0, row = output->row, col = output->col; i < row; ++i)
        for (int j = 0; j < col; ++j)
            ans -= output[i][j] * log(answer[i][j]);
    return ans;
}
loss_f* init_CrossEntropy(){
    return (loss_f){CrossEntropy_get_gredient, CrossEntropy_get_loss_item};
}

Matrix* MSELoss_get_gredient(Matrix* output, Matrix* answer){
    Matrix *tmp = sub(output, answer), *ans = scale(tmp, 1 / (output->row * output->col));
    free_matrix(tmp);
    return ans;
}
double MSELoss_get_loss_item(Matrix* output, Matrix* answer){
    double ans = 0;
     for (int i = 0, row = output->row, col = output->col; i < row; ++i)
        for (int j = 0; j < col; ++j)
            ans -= (output[i][j] - answer[i][j]) * (output[i][j] - answer[i][j]);
    return ans / (output->row * output->col * 2);
}
loss_f* init_MSELoss(){
    return (loss_f){MSELoss_get_gredient, MSELoss_get_loss_item};
}
