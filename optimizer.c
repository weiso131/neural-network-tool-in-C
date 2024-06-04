#include "optimizer.h"
#include <math.h>

Matrix* optimize(optim* self, Matrix* dw, double lr, Matrix* Vdw, Matrix* Sdw){
    Matrix *ans = copy(dw);
    for (int i = 0, row = dw->row, col = dw->col; i < row; ++i){
        for (int j = 0; j < col; ++j){
            Vdw->entry[i * col + j] = self->beta1 * Vdw->entry[i * col + j] + (1 - self->beta1) * dw->entry[i * col + j];
            Sdw->entry[i * col + j] = self->beta2 * Sdw->entry[i * col + j] + (1 - self->beta2) * dw->entry[i * col + j] * dw->entry[i * col + j];
            ans->entry[i * col + j] -= lr * Vdw->entry[i * col + j] / (sqrt(Sdw->entry[i * col + j]) + self->epsilon);
        }
            
    }
        
    return ans;
}

optim* init_Adam(double lr, double beta1, double beta2, double episode){
    optim* adam = malloc(sizeof(optim));
    *adam = (optim){lr, beta1, beta2, episode, optimize};
    return adam;
}
