#include<stdio.h>
#include<omp.h>
#include "matrix.h"
#include "matrix_ops.h"

int main(){
    Matrix *m1 = create(3, 3), *m2 = create(3, 1);
    fill(m1, 2)
    fill(m2, 4)

    printf("test fill, create\n");
    print_matrix(m1);
    print_matrix(m2);
    Matrix *mDot = dot(m1, m2);
    printf("test dot\n");
    print_matrix(mDot);

    printf("test copy\n");
    Matrix *mDot_copy = copy(mDot);
    printf("origin addr: %p, copy addr:%p\n", mDot, mDot_copy);
    print_matrix(mDot_copy);

    free_matrix(mDot_copy)
    free_matrix(mDot)
    free_matrix(m1)
    free_matrix(m2)

    Matrix* identity_matrix = identity(2);
    printf("test identity matrix\n");
    print_matrix(identity_matrix)
    
    flatten_matrix(identity_matrix)
    printf("test flatten\n");

    print_matrix(identity_matrix)

    free_matrix(identity_matrix);


    Matrix *normal = create(4, 3);
    random_fill(normal)
    printf("test random\n");
    print_matrix(normal);

    printf("test argmax\n");
    Matrix* argmax0 = argmax(normal, 0);
    Matrix* argmax1 = argmax(normal, 1);
    printf("dim = 0\n");
    print_matrix(argmax0);
    printf("dim = 1\n");
    print_matrix(argmax1);

    free_matrix(normal)
    free_matrix(argmax0);
    free_matrix(argmax1);


    m1 = create(3, 3), m2 = create(3, 3);
    fill(m1, 2)
    fill(m2, 4)
    Matrix *mAdd = add(m1, m2);
    printf("test add\n");
    print_matrix(mAdd);

    free_matrix(m1);
    free_matrix(m2);

    double start_time, time_count = 0;
    
    m1 = create(1000, 1000), m2 = create(1000, 1000);
    fill(m1, 2)
    fill(m2, 4)
    //multi thread time test
    for (int i = 0;i < 100;i++){
        start_time = omp_get_wtime();
        add(m1, m2);
        time_count += omp_get_wtime() - start_time;
    }

    
    printf("avg time: %lf", time_count / 100);
}

