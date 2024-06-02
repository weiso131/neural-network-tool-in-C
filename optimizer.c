#include "optimizer.h"
#include <math.h>

Matrix* optimize(optim* self, Matrix* dw, double lr, Matrix* Vdw, Matrix* Sdw){
    Matrix *ans = copy(dw);
    for (int i = 0, row = dw->row, col = dw->col; i < row; ++i)
        for (int j = 0; j < col; ++j)
            ans[i][j] -= lr * (self->beta1 * Vdw[i][j] + (1 - self->beta1) * dw[i][j]) / (sqrt(self->beta2 * Sdw[i][j] + (1 - self->beta2) * dw[i][j] * dw[i][j]) + self->epsilon);
    return ans;
}

optim* init_Adam(double lr, double beta1, double beta2, double episode){
    return (optim){lr, beta1, beta2, episode, optimize};
}
