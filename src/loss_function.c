#include "loss_function.h"
#include <math.h>


Matrix* CrossEntropy_get_gredient(Matrix* predict, Matrix* label){
    Matrix *probability = softmax(predict);
    Matrix *output = sub(probability, label);
    free_matrix(probability);
    return output;
}
double CrossEntropy_get_loss_item(Matrix* predict, Matrix* label){
    Matrix *probability = softmax(predict);
    double ans = 0;
    for (int i = 0, row = probability->row, col = probability->col; i < row; ++i)
        for (int j = 0; j < col; ++j)
            ans -= label->entry[i * col + j] * log(probability->entry[i * col + j]);
    free_matrix(probability);
    return ans;
}
loss_f* init_CrossEntropy(){
    loss_f* criterion = malloc(sizeof(loss_f));
    *criterion = (loss_f){CrossEntropy_get_gredient, CrossEntropy_get_loss_item};
    return criterion;
}

Matrix* MSELoss_get_gredient(Matrix* predict, Matrix* label){
    Matrix *tmp = sub(predict, label), *ans = scale(tmp, 1.0 / 2.0);
    free_matrix(tmp);
    return ans;
}
double MSELoss_get_loss_item(Matrix* predict, Matrix* label){
    double ans = 0;
     for (int i = 0, row = predict->row, col = predict->col; i < row; ++i)
        for (int j = 0; j < col; ++j)
            ans += (predict->entry[i * col + j] - label->entry[i * col + j]) * (predict->entry[i * col + j] - label->entry[i * col + j]);
    return ans / (predict->row * predict->col);
}
loss_f* init_MSELoss(){
    loss_f* criterion = malloc(sizeof(loss_f));
    *criterion = (loss_f){MSELoss_get_gredient, MSELoss_get_loss_item};
    return criterion;
}


