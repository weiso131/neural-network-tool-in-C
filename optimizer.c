#include "optimizer.h"
#include <math.h>

Matrix* adam_optimize(optim* self, Matrix* dw, Matrix* Vdw, Matrix* Sdw){
    Matrix *output = create(dw->row, dw->col);
    for (int i = 0, row = dw->row, col = dw->col; i < row; ++i){
        for (int j = 0; j < col; ++j){
            Vdw->entry[i * col + j] = self->beta1 * Vdw->entry[i * col + j] + (1 - self->beta1) * dw->entry[i * col + j];
            Sdw->entry[i * col + j] = self->beta2 * Sdw->entry[i * col + j] + (1 - self->beta2) * dw->entry[i * col + j] * dw->entry[i * col + j];
            output->entry[i * col + j] = self->init_lr * Vdw->entry[i * col + j] / (sqrt(Sdw->entry[i * col + j]) + self->epsilon);
        }
            
    }
        
    return output;
}

optim* init_Adam(double lr, double beta1, double beta2, double episode){
    optim* adam = malloc(sizeof(optim));
    *adam = (optim){lr, beta1, beta2, episode, adam_optimize};
    return adam;
}

Matrix* SGD_optimize(optim* self, Matrix* dw, Matrix* Vdw, Matrix* Sdw){
    return scale(dw, self->init_lr);
}
optim* init_SGD(double init_lr){
    optim* SGD = malloc(sizeof(optim));
    *SGD = (optim){init_lr, 0, 0, 0};
    return SGD;
}
