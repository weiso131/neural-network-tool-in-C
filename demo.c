#include <stdio.h>
#include "src/nn.h"
#include "src/dataloader.h"
#include "src/model.h"
#define ERROR(format, ...) {fprintf(stderr, format, __VA_ARGS__);return NULL;}

Matrix **create_vectors(int nums, int each_len){
    Matrix **vectors = malloc(nums * sizeof(Matrix*));
    for (int i = 0; i < nums; ++i)
        vectors[i] = create(each_len, 1);
    return vectors;
}

void free_vectors(Matrix **vectors, int len){
    for (int i = 0; i < len; ++i)
        free_matrix(vectors[i]);
    free(vectors);
}

Matrix **read_vectors(char* file, int *row, int *col){
    FILE *fp = fopen(file, "r");
    if (!fp)ERROR("%s doesn't exist.\n", file);
    if (fscanf(fp, "%d %d", row, col) < 2)ERROR("%s can't read the size of matrix.\n", file);
    Matrix **vectors = create_vectors(*row, *col);
    for (int i = 0; i < *row; ++i)
        for (int j = 0; j < *col; ++j)
            if (!fscanf(fp, "%lf", vectors[i]->entry + j))
                ERROR("unknown error while reading matrix in %s\n", file);
    return vectors;
}

void getAcc_(dataloader *loader, Model *model, char *Name){
    double acc = 0, total = loader->data_length;

    for (int batchNum = 0;batchNum < loader->data_length / loader->batch_size;batchNum++){
        Matrix *data = loader->batches[batchNum]->data, *target = loader->batches[batchNum]->label;
        Matrix *predicts = model->predict(model, data);
        Matrix *argmaxPredict = argmax(predicts, 1);
        Matrix *argmaxTarget = argmax(target, 1);

        for (int i = 0;i < loader->batch_size;i++)
            if (fabs(argmaxPredict->entry[i] - argmaxTarget->entry[i]) < 1e-7)
                acc++;
        
        free_matrix(predicts);
        free_matrix(argmaxPredict);
        free_matrix(argmaxTarget);

    }

    
    printf("%s: acc:%lf\n", Name, acc / total);
}

int main(){
    int data_row, data_col, target_row, target_col;
    Matrix **data = read_vectors("data.txt", &data_row, &data_col);
    if (data == NULL)return -1;
    Matrix **target = read_vectors("target.txt", &target_row, &target_col);
    if (target == NULL){
        free_vectors(data, data_col);
        return -1;
    }
    printf("%d\n", data_row);
    dataloader *trainDataloader = init_dataloader(data, target, 64, 800, 1);
    dataloader *validDataloader = init_dataloader(data + 800, target + 800, 64, 91, 1);

    Model *myModel = create_model();
    myModel->add(myModel, Linear_init(16, data_col, NULL, NULL));
    myModel->add(myModel, ReLU_init());
    myModel->add(myModel, Linear_init(target_col, 16, NULL, NULL));

    printf("訓練前:\n");
    getAcc_(trainDataloader, myModel, "train acc:");
    getAcc_(validDataloader, myModel, "valid acc:");

    myModel->train(myModel ,init_Adam(0.01, 0.9, 0.999, 1e-8), 1000, trainDataloader, validDataloader, init_MSELoss());

    printf("訓練後:\n");
    getAcc_(trainDataloader, myModel, "train acc:");
    getAcc_(validDataloader, myModel, "valid acc:");

    return 0;
}
