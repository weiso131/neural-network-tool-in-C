#include<stdio.h>
#include "matrix.h"
#include "matrix_ops.h"

int main(){
    Matrix *m1 = create(2, 2, sizeof(double), DOUBLE), *m2 = create(2, 2, sizeof(double), DOUBLE);
    
    
    fill(m1, 2, double)
    fill(m2, 4, double)

    printf("test fill, create\n");
    print_matrix(m1, double);
    printf("\n");
    print_matrix(m2, double);
    printf("\n");
    Matrix *mDot = dot(m1, m2);

    printf("test dot\n");
    print_matrix(mDot, double);

    printf("test copy\n");
    Matrix *mDot_copy = copy(mDot);
    printf("origin addr: %p, copy addr:%p\n", mDot, mDot_copy);
    print_matrix(mDot_copy, double);

    free_matrix(mDot_copy)
    free_matrix(mDot)
    free_matrix(m1)
    free_matrix(m2)

    

    

    

    Matrix* identity_matrix = identity(2, sizeof(int), INT);
    printf("test identity matrix\n");
    print_matrix(identity_matrix, int)
    
    flatten_matrix(identity_matrix)
    printf("test flatten\n");

    print_matrix(identity_matrix, int)

    free_matrix(identity_matrix);


    Matrix *normal = create(4, 3, sizeof(double), DOUBLE);
    random_fill(normal, double)
    printf("test random\n");
    print_matrix(normal, double);

    printf("test argmax\n");
    Matrix* argmax0 = argmax(normal, 0);
    Matrix* argmax1 = argmax(normal, 1);
    printf("dim = 0\n");
    print_matrix(argmax0, int);
    printf("dim = 1\n");
    print_matrix(argmax1, int);

    free_matrix(normal)
    free_matrix(argmax0);
    free_matrix(argmax1);


}

