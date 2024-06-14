#include "dataloader.h"

int main(){
    int data_length = 25, batch_size = 4;

    Matrix **data = (Matrix **)malloc(sizeof(Matrix *) * data_length),
           **label = (Matrix **)malloc(sizeof(Matrix *) * data_length);
    for (int i = 0; i < data_length; i++){
        data[i] = (Matrix*)create(4, 1);
        label[i] = (Matrix*)create(2, 1);
        fill(data[i], i);
        fill(label[i], i);
    }

    dataloader* loader = init_dataloader(data, label, batch_size, data_length, 1);
    for (int i = 0;i < data_length / batch_size + (data_length % batch_size != 0);i++){
        Matrix* x = loader->batches[i]->data;
        Matrix* y = loader->batches[i]->label;
        printf("data:\n");
        print_matrix(x);
        printf("label:\n");
        print_matrix(y);

    }
}