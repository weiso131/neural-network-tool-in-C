#include<stdio.h>
#include "matrix.h"

int main(){
    Matrix *m1 = create(2, 2, sizeof(double), DOUBLE), *m2 = create(2, 2, sizeof(double), DOUBLE);
    
    
    fill(m1, 2, double)
    fill(m2, 4, double)
    print_matrix(m1, double);
    printf("\n");
    print_matrix(m2, double);

    Matrix *mDot = dot(m1, m2);

    printf("\n");
    print_matrix(mDot, double);

    printf("\n");
    Matrix *mDot_copy = copy(mDot);
    printf("%p\n", mDot);
    printf("%p\n", mDot_copy);
    print_matrix(mDot_copy, double);
}

