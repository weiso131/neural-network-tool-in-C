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

Matrix *db_calculate(Matrix *dz){
    Matrix *db = create(dz->row, 1);
    for (int i = 0; i < dz->row;i++){
        for (int j = 0;j < dz->col;j++)
            db->entry[i] += dz->entry[i * dz->col + j];
        db->entry[i] /= dz->col;
    }
    return db;
        
}

Matrix* Linear_backward(struct linear_* self, Matrix* dz, Matrix* x, optim* optimizer){
    //Update
    Matrix *xT = transpose(x);
    Matrix *dw = mul(dz, xT);
    free_matrix(xT);

    Matrix *db = db_calculate(dz);

    Matrix *lr_dW = optimizer->optimize(optimizer, dw, self->vdw, self->sdw);
    Matrix *lr_db = optimizer->optimize(optimizer, db, self->vdb, self->sdb);
    free_matrix(dw);
    free_matrix(db);

    Matrix *ori_w = self->w;
    Matrix *ori_b = self->b;
    self->w = sub(ori_w, lr_dW);
    self->b = sub(ori_b, lr_db);
    
    free_matrix(ori_w);
    free_matrix(ori_b);

    //calculate output
    Matrix* wT = transpose(self->w);
    Matrix* output = mul(wT, dz);
    free_matrix(wT);

    return output;

}   

/*
小筆記:
linear在forward的時候，要有個對應的東西去存它的輸出，方便之後反向傳播和記憶體清空
*/