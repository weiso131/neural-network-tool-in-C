#include <stdlib.h>
#include <time.h>
#include "dataloader.h"

dataloader* init_dataloader(Matrix **data, Matrix **label, int batch_size, int data_length, int shuffle){
    dataloader *loader = malloc(sizeof(dataloader));
    int batch_length = (data_length - 1) / batch_size + 1;
    *loader = (dataloader){malloc(batch_length * sizeof(batch_data)), batch_size, data_length, malloc(data_length * sizeof(int)), get_batch};
    for (int i = 0; i < data_length; ++i)loader->indice[i] = i;
    if (shuffle){
        srand(time(0));
        for (int i = 1, *p = loader->indice; i < n; ++i){
            int k = rand()%i;
            p[i]^=p[k]^=p[i]^=p[k];
        }
    }
    int row = (*data)->row, col = (*data)->col * batch_size, full_batch_legth = data_length / batch_size, latest_matrix_num = data_length % batch_size;
    for (int batch_num = 0; batch_num < batch_length; ++batch_num){
        loader->batches[batch_num]->data = create(row, col);
        loader->batches[batch_num]->label = create(row, col);
        for (int matrix_num = 0; matrix_num < batch_size; ++matrix_num){
            for(int i = 0; i < row; ++i)
                for(int j = 0; j < col; ++j){
                    loader->batches[batch_num]->data[i][j] = data[p[batch_num * batch_size + matrix_num]][i][j];
                    loader->batches[batch_num]->label[i][j] = label[p[batch_num * batch_size + matrix_num]][i][j];
                }
        }
    }
    for (int matrix_num = 0; matrix_num < latest_matrix_num; ++matrix_num){
        for(int i = 0; i < row; ++i)
            for(int j = 0; j < col; ++j){
                loader->batches[full_batch_length]->data[i][j] = data[p[full_batch_length * batch_size + matrix_num]][i][j];
                loader->batches[full_batch_length]->label[i][j] = label[p[full_batch_length * batch_size + matrix_num]][i][j];
            }
    }
    return loader;
}
