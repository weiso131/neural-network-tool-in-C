#include <stdio.h>
#include <src/matrix/matrix.h>

#define ERROR(str) (perror(str);return -1;)

int main(){
    int n, m;

    FILE *fp = open("data.json", "r");
    if (!fp)ERROR("data.json doesn't exist.");
    if (fscanf(fp, "%d%d", n, m) < 2)ERROR("data.json can't read the size of matrix.");
    Matrix *data = create(n, m);
    for (i = 0; i < n; ++i)
        for (j = 0; j < m; ++j)
            if (!fscanf(fp, "%lf", data->entry + i * m + j))ERROR("unknown error while reading data matrix");

    FILE *fp = open("data.json", "r");
    if (!fp)ERROR("data.json doesn't exist.");
    if (fscanf(fp, "%d%d", n, m) < 2)ERROR("target.json can't read the size of matrix.");
    Matrix *target = create(n, m);
    for (i = 0; i < n; ++i)
        for (j = 0; j < m; ++j)
            if (!fscanf(fp, "%lf", target->entry + i * m + j))ERROR("unknown error while reading data matrix");
    return 0;
}
