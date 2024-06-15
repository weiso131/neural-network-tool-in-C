#include "src/matrix/matrix.h"
#include <stdio.h>


#define ERROR(format, ...) {fprintf(stderr, format, __VA_ARGS__);return NULL;}

Matrix **create_vectors(int nums, int each_len){
    Matrix **vectors = malloc(nums * sizeof(Matrix*));
    for (int i = 0; i < nums; ++i)
        vectors[i] = create(each_len, 1);
    return vectors;
}

Matrix **read_vectors(char* file){
    int n, m;
    FILE *fp = fopen(file, "r");
    if (!fp)ERROR("%s doesn't exist.\n", file);
    if (fscanf(fp, "%d%d", &n, &m) < 2)ERROR("%s can't read the size of matrix.\n", file);
    printf("%d, %d", n, m);
    Matrix **vectors = create_vectors(n, m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (!fscanf(fp, "%lf", vectors[i]->entry + j))ERROR("unknown error while reading matrix in %s\n", file);
    return vectors;
}

int main(){
    Matrix **data = read_vectors("data.json");
    Matrix **target = read_vectors("target.json");

    print_matrix(data[0]);
    return 0;
}
