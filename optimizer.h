#include "matrix/matrix.h"

#ifndef OPTIMIZER_H
#define OPTIMIZER_H

typedef struct{
    double init_lr, beta1, beta2, episode;
    Matrix* (*optimize)(optim*, Matrix*, double);

}optim;

optim* init_Adam(double, double, double, double);
/*
公式參考:https://hackmd.io/IXesQRuzSQisMGYL4t1eRQ，crtl+f找優化器

1.  傳入的matrix是dw或db
    double是learning rate

2.  更新linear的時候:
    w = optimize(dw);
    b = optimize(b);

3.  使用者create一個Adam的object之後
    要傳入Adam_object給model.train()
*/
#endif

