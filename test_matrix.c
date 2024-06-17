#include<stdio.h>
#include<omp.h>
#include "src/matrix/matrix.h"
#include "src/matrix/matrix_ops.h"

double test_apply(double x){
    return 0;
}


int main(){
    Matrix *m1 = init_matrix(3, 3), *m2 = init_matrix(3, 1);
    fill(m1, 2);
    fill(m2, 4);

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
    print_matrix(identity_matrix);
    
    flatten_matrix(identity_matrix)
    printf("test flatten\n");

    print_matrix(identity_matrix);

    free_matrix(identity_matrix);


    Matrix *normal = init_matrix(4, 3);
    random_fill(normal);
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


    m1 = init_matrix(3, 3), m2 = init_matrix(3, 3);
    fill(m1, 2);
    fill(m2, 4);
    Matrix *mAdd = add(m1, m2);
    printf("test add\n");
    print_matrix(mAdd);

    free_matrix(m1);
    free_matrix(m2);

    double start_time, time_count = 0;
    
    

    m1 = identity(10), m2 = init_matrix(10, 1);
    fill(m2, 4);

    Matrix *mul_result = mul(m1, m2);

    printf("test mul\n");
    print_matrix(mul_result);

    free_matrix(m1);
    free_matrix(m2);


    m1 = identity(4);
    Matrix* scale_result = scale(m1, 4);

    printf("test scale\n");
    print_matrix(scale_result);


    random_fill(m1);
    

    Matrix *m1_T = transpose(m1);
    printf("test transpose\n");
    printf("origin:\n");
    print_matrix(m1);
    printf("transpose:\n");
    print_matrix(m1_T);

    Matrix *apply0 = apply(m1_T, test_apply);
    printf("test apply\n");
    print_matrix(apply0);
    
    free_matrix(m1);
    printf("test sub\n");
    m1 = init_matrix(4, 4), m2 = init_matrix(4, 4);
    fill(m1, 2);
    fill(m2, 1);
    
    Matrix *sub_result = sub(m1 , m2);

    
    print_matrix(sub_result);


}

