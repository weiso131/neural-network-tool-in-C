#include<stdio.h>
#include "number.h"
#include "matrix.h"

int main(){
    Matrix* m = create(9, 9, INT);
    
    printf("%p\n", m->entry);
    
    fill(m, 10);
    print_matrix(m);

}

