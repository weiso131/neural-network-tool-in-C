#include "model.h"

#define Forward_type_transfor(type, void_member, result, data){\
    type *member = (type *)void_member;\
    result = member->forward(member, data);\
}
#define Backward_type_transfor(type, void_member, dz, last_layer_output, optimizer){\
    type *member = (type *)void_member;\
    Matrix *trash = dz;\
    dz = member->backward(member, dz, last_layer_output, optimizer);\
    free_matrix(trash);\
}

typedef struct outputNode_{
    Matrix* output;
    struct outputNode_* prev;
}outputNode;

outputNode *outputNode_create(Matrix* output){
    outputNode *node = malloc(sizeof(outputNode));
    *node = (outputNode){output, NULL};
    return node;
}

void add_outputNode(outputNode **head, outputNode *node){
    node->prev = *head;
    *head = node;
}
void pop_outputNode(outputNode **head){
    if ((*head) == NULL) return;
    outputNode *trash = *head;
    *head = (*head)->prev;
    free(trash);
}



Model* create_model(){
    Model* model = malloc(sizeof(Model));
    *model = (Model){NULL, NULL, model_add_impl, predict_impl, train_impl};
    return model;
}

void model_add_impl(Model *self, nn_node* newNode){
    if (self->begin == NULL)
        self->begin = newNode;
    if (self->end != NULL)
        self->end->next = newNode;
    newNode->prev = self->end;
    self->end = newNode;
}

Matrix* forward(Model *self, Matrix *data, outputNode **outputLinklist){
    nn_node *SerialNode = self->begin;
    Matrix* result = data;
    while (SerialNode != NULL){
        Matrix* new_result;
        NNtype member_type = SerialNode->menber_type;
        if (member_type == LINEAR){
            Forward_type_transfor(Linear, SerialNode->nn_menber, new_result, result);
        }
        else if(member_type == ACTIVATE){
            Forward_type_transfor(Act_func, SerialNode->nn_menber, new_result, result);
        }
        else if(member_type == DROP){
            Forward_type_transfor(Drop, SerialNode->nn_menber, new_result, result);
        }
        else {
            Forward_type_transfor(Softmax, SerialNode->nn_menber, new_result, result);
        }
        
        SerialNode = SerialNode->next;
        if (outputLinklist != NULL && member_type != SOFTMAX){//softmax會跳過
            printf("test: %d, %d\n", new_result->row, new_result->col);
            print_matrix(new_result);
            add_outputNode(outputLinklist, outputNode_create(new_result));
        }
            
        else if (result != data)
            free_matrix(result);
        result = new_result;
        
            
    }
    return result;
}

Matrix* predict_impl(Model *self, Matrix *data){
    return forward(self, data, NULL);
}

void train_impl(Model *self, optim* optimizer, int epoch, dataloader* train_data, dataloader* valid_data, loss_f* loss_function){
    
    
    Matrix* input = create(5, 1);
    Matrix* target = create(3, 1);
    double input_entry[] = {0.1, 0.5, 0.6, 0.89, 0.34};
    double target_entry[] = {1.0, 0.0, 0.0};
    input->entry = input_entry;
    target->entry = target_entry;
    
    for (int t = 0;t < epoch;t++){
        outputNode *outputLinklist = outputNode_create(NULL);
        Matrix *predict = forward(self, input, &outputLinklist);
        Matrix *dz = loss_function->get_gredient(outputLinklist->output, target);//反向傳播會跳過softmax，直接使用前一層的輸出
        // printf("test dz\n");
        double loss = loss_function->get_loss_item(predict, target);
        pop_outputNode(&outputLinklist);

        nn_node *SerialNode = self->end;
        
        while (SerialNode != NULL){
            if (SerialNode->menber_type == SOFTMAX){
                SerialNode = SerialNode->prev;
                continue;
            }

            //決定上一層輸出是誰
            Matrix *last_layer_output = outputLinklist->output;
            if (outputLinklist->output == NULL)
                last_layer_output = input;
            
            if (SerialNode->menber_type == LINEAR){
                Backward_type_transfor(Linear, SerialNode->nn_menber, dz, last_layer_output, optimizer);
            }
            else if(SerialNode->menber_type == ACTIVATE){
                Backward_type_transfor(Act_func, SerialNode->nn_menber, dz, last_layer_output, optimizer);
            }
            else if(SerialNode->menber_type == DROP){
                Backward_type_transfor(Drop, SerialNode->nn_menber, dz, last_layer_output, optimizer);
            }

            pop_outputNode(&outputLinklist);
            SerialNode = SerialNode->prev;
        }

        free_matrix(dz);
        free_matrix(predict);
    }

    
}


