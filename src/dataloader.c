#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "dataloader.h"

dataloader* init_dataloader(Matrix **data, Matrix **label, int batch_size, int data_length, int shuffle){
    //檢查輸入是否符合要求
    if ((*data)->col != 1){
        printf("(*data)->col should be 1");
        return NULL;
    }
    int batch_length = (data_length - 1) / batch_size + 1;
    dataloader *loader = malloc(sizeof(dataloader));
    
    *loader = (dataloader){(batch_data**)malloc(batch_length * sizeof(batch_data*)), 
                batch_size, data_length, malloc(data_length * sizeof(int))};
    for (int i = 0; i < data_length; ++i) loader->indice[i] = i;

    //隨機交換，達到打亂順序的效果
    if (shuffle){
        srand(time(0));
        for (int i = 1, *p = loader->indice; i < data_length; ++i){
            int k = rand()%i;
            p[i]^=p[k]^=p[i]^=p[k];
        }
    }

    for (int batch_num = 0; batch_num <= data_length / batch_size; ++batch_num){
        
        //計算這個batch實際上的batchSize，考慮data_length % batch_size != 0
        bool remainData = (data_length - batch_num * batch_size) / batch_size == 0;
        int realBatchSize = (1 - remainData) * batch_size + (remainData) * (data_length % batch_size);

        if (realBatchSize == 0)
            break;
        loader->batches[batch_num] = malloc(sizeof(batch_data));
        loader->batches[batch_num]->data = init_matrix((*data)->row, realBatchSize);
        loader->batches[batch_num]->label = init_matrix((*label)->row, realBatchSize);
        
        for (int matrix_num = 0; matrix_num < realBatchSize; ++matrix_num){
            for(int j = 0; j < realBatchSize; ++j){
                for(int i = 0; i < (*data)->row; ++i)
                    loader->batches[batch_num]->data->entry[i * realBatchSize + j] = data[loader->indice[batch_num * batch_size + j]]->entry[i];
                for(int i = 0; i < (*label)->row; ++i)
                    loader->batches[batch_num]->label->entry[i * realBatchSize + j] = label[loader->indice[batch_num * batch_size + j]]->entry[i];
            }
                
        }
    }
    return loader;
}
