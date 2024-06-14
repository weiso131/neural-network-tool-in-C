#include "model.h"

int main(){
    Model *myModel = create_model();
    myModel->add(myModel, Linear_init(16, 5, NULL, NULL)); 
    myModel->add(myModel, ReLU_init());
    myModel->add(myModel, Linear_init(3, 16, NULL, NULL));   
    printf("Forward:\n");
    nn_node *start = myModel->begin;
    while (start != NULL){
        if (start->menber_type == LINEAR){
            Linear *linear = (Linear*)start->nn_menber;
            printf("LINEAR, n:%d, m:%d\n", linear->w->row, linear->w->col);
            
        }
            
        else if(start->menber_type == ACTIVATE)
            printf("ACTIVE\n");

        start = start->next;
    }

    printf("backward:\n");
    nn_node *end = myModel->end;
    while (end != NULL){
        if (end->menber_type == LINEAR){
            Linear *linear = (Linear*)end->nn_menber;
            printf("LINEAR, n:%d, m:%d\n", linear->w->row, linear->w->col);
            
        }
            
        else if(end->menber_type == ACTIVATE)
            printf("ACTIVE\n");

        end = end->prev;
    }
    Matrix **data = (Matrix**)malloc(sizeof(Matrix*) * 20);
    Matrix **label = (Matrix**)malloc(sizeof(Matrix*) * 20);

    for (int i = 0;i < 20;i++){
        double input_entry[] = {0.1, 0.5, 0.6, 0.89, 0.34};
        double target_entry[] = {1.0, 0.0, 0.0};
        
        data[i] = create(5, 1);
        label[i] = create(3, 1);
        
        data[i]->entry = input_entry;
        label[i]->entry = target_entry;
    }

    Matrix* input = create(5, 1);
    double input_entry[] = {0.1, 0.5, 0.6, 0.89, 0.34};
    input->entry = input_entry;

    dataloader *trainLoader = init_dataloader(data, label, 4, 20, 0);
    dataloader *validLoader = init_dataloader(data, label, 4, 14, 0);

    myModel->train(myModel, init_Adam(0.01, 0.9, 0.999, 1e-8), 100, trainLoader, validLoader, init_MSELoss());


    Matrix *predict = myModel->predict(myModel, input);
    print_matrix(predict);
}


//gcc test_model.c model.c linear.c drop.c act_f/act_f.c act_f/act_f_impl.c matrix/matrix.c matrix/matrix_ops.c loss_function.c optimizer.c dataloader.c -o test_model -lm