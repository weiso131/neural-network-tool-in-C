#include "nn.h"
#include<time.h>
nn_node* init_drop(double drop_rate){
    Drop *drop = malloc(sizeof(Drop));

    if (drop_rate <= 0 || drop_rate > 1){
        printf("drop rate must be (0, 1]\n");
        return NULL;
    }
    *drop = (Drop){drop_rate, NULL, drop_forward, drop_backward};

    nn_node *drop_node = malloc(sizeof(nn_node));
    *drop_node = (nn_node){NULL, NULL, drop, DROP};
    return drop_node;
}
Matrix *drop_forward(Drop *self, Matrix *x){
    if (!self->drop_matrix)
        self->drop_matrix = init_matrix(x->row, x->col);
    double drop_rate = self->drop_rate;
    srand(time(NULL));

    for (int i = 0;i < x->row * x->col; i++){
        if ((double)rand() / (double)RAND_MAX < drop_rate)
            self->drop_matrix->entry[i] = 0;
        else
            self->drop_matrix->entry[i] = 1 / (1 - drop_rate);
    }
        

    return dot(x, self->drop_matrix);
}

Matrix *drop_backward(Drop* self, Matrix* dz, Matrix* x, optim* optimizer){
    return dot(self->drop_matrix, dz);
}
