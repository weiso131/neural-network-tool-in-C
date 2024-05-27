#include "matrix/matrix.h"

#ifndef OPTIMIZER_H
#define OPTIMIZER_H

typedef Matrix* (*optim)(Matrix*);

typedef struct{
    double init_lr, beta1, beta2, episode;
    optim optimize;

}Adam;

Adam* init_Adam(double, double, double, double);
/*
公式參考:https://hackmd.io/IXesQRuzSQisMGYL4t1eRQ，crtl+f找優化器

1.  optim(Matrix*)傳入的matrix是dw或db

2.  更新linear的時候:
    w = optimize(dw);
    b = optimize(b);

3.  使用者create一個Adam的object之後
    要傳入Adam_object->opimize給model.train()
    這樣也可以確保之後無聊想實作其他優化器時
    格式可以統一
*/
#endif

