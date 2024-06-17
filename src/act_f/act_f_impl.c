#include "act_f_impl.h"
#include <stdint.h>
#include <math.h>

#define double_int union{double d;int64_t i;}

double relu_forward_impl(double x){
    double_int out = {.d = x};
    
    out.i &= ~(out.i >> 63);
    return out.d;

    //https://hackmd.io/@sysprog/constant-time-relu
}
double relu_backward_impl(double x){
    double_int ori = {.d = x};
    double_int out = {.d = 1.0};
    out.i &= ~(ori.i >> 63);
    return out.d;
}

double sigmoid_forward_impl(double x){
    return 1 / (1 + exp(-x));
}
double sigmoid_backward_impl(double x){
    double s = sigmoid_forward_impl(x);
    return s * (1 - s);
}
