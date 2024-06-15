#include <stdio.h>
#include "src/matrix/matrix.h"

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

int main(){
    int data_row, data_col, target_row, target_col;
    Matrix **data = read_vectors("data.json", &data_row, &data_col);
    if (data == NULL)return -1;
    Matrix **target = read_vectors("target.json", &target_row, &target_col);
    if (target == NULL){
        free_vectors(data, data_col);
        return -1;
    }
    return 0;
}
