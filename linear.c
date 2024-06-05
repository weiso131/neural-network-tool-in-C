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
    *linear = (Linear){linear->w, linear->b, Linear_forward, Linear_w_backward, Linear_b_backward};

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
Matrix* Linear_w_backward(Linear *self, Matrix* x, Matrix* dz){

}
Matrix* Linear_b_backward(Linear *self, Matrix* dz){

}