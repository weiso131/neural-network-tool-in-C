#include "src/optimizer.h"

int main(){
    optim *adam = init_Adam(0.1, 0.9, 0.9, 1e-8);

    double dw_entry[] = {1, 3, 1, 2};
    double Sdw_entry[] = {1, 1, 1, 1};
    double Vdw_entry[] = {1, 1, 1, 1};

    Matrix *dw = init_matrix(2, 2);
    Matrix *Sdw = init_matrix(2, 2);
    Matrix *Vdw = init_matrix(2, 2);

    dw->entry = dw_entry;
    Sdw->entry = Sdw_entry;
    Vdw->entry = Vdw_entry;
    printf("dw:\n");
    print_matrix(dw);
    printf("optim:\n");
    print_matrix(adam->optimize(adam, dw, Vdw, Sdw));
    printf("Vdw:\n");
    print_matrix(Vdw);
    printf("Sdw:\n");
    print_matrix(Sdw);


}