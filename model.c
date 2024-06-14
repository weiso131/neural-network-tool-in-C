#include "model.h"

#define Forward_type_transfor(type, void_member, result, data){\
    type *member = (type *)void_member;\
    result = member->forward(member, data);\
}

Model* create_model(){
    Model* model = malloc(sizeof(Model));
    *model = (Model){NULL, NULL, add_impl, predict_impl, train_impl};
    return model;
}

void add_impl(Model *self, nn_node* newNode){
    if (self->begin == NULL)
        self->begin = newNode;
    if (self->end != NULL)
        self->end->next = newNode;
    newNode->prev = self->end;
    self->end = newNode;
}

Matrix* predict_impl(Model *self, Matrix *data){
    nn_node *start = self->begin;
    Matrix* result = data;
    
    while (start != NULL){
        Matrix* new_result;
        if (start->menber_type == LINEAR){
            Forward_type_transfor(Linear, start->nn_menber, new_result, result);
        }
        else if(start->menber_type == ACTIVATE){
            Forward_type_transfor(Act_func, start->nn_menber, new_result, result);
        }
        else if(start->menber_type == DROP){
            Forward_type_transfor(Drop, start->nn_menber, new_result, result);
        }
        else {
            Forward_type_transfor(Softmax, start->nn_menber, new_result, result);
        }
        start = start->next;
        if (result != data)
            free_matrix(result);
        result = new_result;
    }
    return result;
}

void train_impl(Model *self, optim* optimizer, int epoch, dataloader* train_data, dataloader* valid_data, loss_f* loss_function){

}