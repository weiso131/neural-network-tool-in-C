#include <stdio.h>
#include <src/matrix/matrix.h>

#define ERROR(format, ...) (fprintf(strerr, format, __VA_ARGS__);return -1;)

Matrix **create_vectors(int nums, int each_len){
    Matrix **vectors = malloc(nums * sizeof(Matrix*));
    for (int i = 0; i < nums; ++i)
        vectors[i] = create(each_len, 1);
    return vectors;
}

Matrix *read_vectors(char* file){
    int n, m;
    FILE *fp = open(file, "r");
    if (!fp)ERROR("%s doesn't exist.", file);
    if (fscanf(fp, "%d%d", n, m) < 2)ERROR("%s can't read the size of matrix.", file);
    Matrix **vectors = create_vectors(n, m);
    for (i = 0; i < n; ++i)
        for (j = 0; j < m; ++j)
            if (!fscanf(fp, "%lf", vectors[i]->entry + j))ERROR("unknown error while reading matrix in %s", file);
    return vectors;
}

int main(){
    Matrix **data = read_vectors("data.json");
    Matrix **target = read_vectors("target.json");
    return 0;
}
