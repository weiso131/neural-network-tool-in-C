#include "nn.h"
#include<time.h>
nn_node* init_drop(double drop_rate){
    Drop *drop = malloc(sizeof(Drop));

    if (drop_rate <= 0 || drop_rate > 1){
        printf("drop rate must be (0, 1]\n");
        return NULL;
    }
    *drop = (Drop){drop_rate, drop_forward};

    nn_node *drop_node = malloc(sizeof(nn_node));
    *drop_node = (nn_node){NULL, NULL, drop, DROP};
    return drop_node;
}
Matrix *drop_forward(Drop *self, Matrix *x){
    Matrix *output = init_matrix(x->row, x->col);
    double drop_rate = self->drop_rate;
    srand(time(NULL));

    for (int i = 0;i < x->row * x->col;i++){
        if ((double)rand() / (double)RAND_MAX < drop_rate)
            output->entry[i] = 0;
        else
            output->entry[i] = x->entry[i];
    }
        

    return output;
}

//drop backward尚未完成
//https://blog.csdn.net/mch2869253130/article/details/119809360
