#include<stdio.h>
#include<omp.h>
#include "matrix.h"
#include "matrix_ops.h"

int main(){
    Matrix *m1 = NULL, *m2 = NULL;
    

    double start_time, time_count = 0;
    
    m1 = create(10000, 10000), m2 = create(10000, 10000);
    fill(m1, 2)
    fill(m2, 4)
    //multi thread time test
    for (int i = 0;i < 100;i++){
        start_time = omp_get_wtime();
        Matrix* output = dot(m1, m2);
        time_count += omp_get_wtime() - start_time;
        free_matrix(output);
    }
    free_matrix(m1);
    free_matrix(m2);
    
    printf("avg time: %lf", time_count / 100);
}

