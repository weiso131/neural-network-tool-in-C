#include <stdlib.h>
#include <time.h>
#include "dataloader.h"

batch_data* get_batch(dataloader *loader, int num){
    // return (batch_data){loader->};
}

dataloader* init_dataloader(Matrix **data, Matrix **label, int batch_size, int data_length, int shuffle){
    dataloader *loader = malloc(sizeof(dataloader));
    int batch_length = (data_length - 1) / batch_size + 1;
    *loader = (dataloader){malloc(batch_length * sizeof(Matrix*)), malloc(batch_length * sizeof(Matrix*)), batch_size, data_length, malloc(data_length * sizeof(int)), get_batch};
    for (int i = 0, *p = loader->indice; i < data_length; ++i)p[i] = i;
    if (shuffle){
        srand(time(0));
        for (int i = 1, *p = loader->indice; i < n; ++i){
            int k = rand()%i;
            p[i]^=p[k]^=p[i]^=p[k];
        }
    }
    for (int i = 0; i < batch_length; ++i){
        loader->data[i] = malloc(sizeof(data * batch_size));
        loader->label[i] = malloc(sizeof(data * batch_size));
        for (int j = 0; j < batch_size; ++j){
            loader->data[i][j] = data[p[i* batch_size + j]];
            loader->label[i][j] = label[p[i * batch_size + j]];
        }
    }
    return loader;
}
