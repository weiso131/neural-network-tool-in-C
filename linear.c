#include "nn.h"

nn_node* Linear_init(int n, int m, Matrix* specify_w, Matrix* specify_b){
    Linear *linear = malloc(sizeof(Linear));
    linear->w = specify_w;
    linear->b = specify_b;
    if (specify_w == NULL || specify_w->row != n || specify_w->col != m){
        linear->w = create(n, m);
        random_fill(linear->w);
    }
    if (specify_b == NULL || specify_b->row != n || specify_b->col != 1){
        linear->b = create(n, 1);
        random_fill(linear->b);
    }


    *linear = (Linear){linear->w, linear->b, create(n, m), create(n, m), create(n, 1), create(n, 1), Linear_forward, Linear_backward};

    fill(linear->vdw, 0);
    fill(linear->sdw, 0);
    fill(linear->vdb, 0);
    fill(linear->sdb, 0);

    nn_node *linear_node = malloc(sizeof(nn_node));
    *linear_node = (nn_node){NULL, NULL, linear, LINEAR};

    return linear_node;

}
Matrix* Linear_forward(struct linear_* self, Matrix* x){
    Matrix *mul_result = mul(self->w, x);
    Matrix *result = add(mul_result, self->b);
    free_matrix(mul_result);
    return result;
}
Matrix* Linear_backward(struct linear_* self, Matrix* dz, Matrix* x, optim* optimizer){
    Matrix *xT = transpose(x);
    Matrix *dw = mul(dz, xT);
    free_matrix(xT);

    Matrix *lr_dW = optimizer->optimize(optimizer, dw, self->vdw, self->sdw);
    Matrix *lr_db = optimizer->optimize(optimizer, dz, self->vdb, self->sdb);
    free_matrix(dw);

    Matrix *ori_w = self->w;
    Matrix *ori_b = self->b;
    self->w = sub(ori_w, lr_dW);
    self->b = sub(ori_b, lr_db);
    
    free_matrix(ori_w);
    free_matrix(ori_b);
}   

/*
小筆記:
linear在forward的時候，要有個對應的東西去存它的輸出，方便之後反向傳播和記憶體清空
*/