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

//儲存各層output的stack
typedef struct outputNode_{
    Matrix *output;
    struct outputNode_ *prev;
}outputNode;

outputNode *outputNode_create(Matrix *output){
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



Model* init_model(){
    Model *model = malloc(sizeof(Model));
    *model = (Model){NULL, NULL, model_add_impl, predict_impl, train_impl};
    return model;
}

void model_add_impl(Model *self, nn_node *newNode){
    if (self->begin == NULL)
        self->begin = newNode;
    if (self->end != NULL)
        self->end->next = newNode;
    newNode->prev = self->end;
    self->end = newNode;
}

Matrix* forward(Model *self, Matrix *data, outputNode **outputLinklist){
    nn_node *SerialNode = self->begin;
    Matrix *result = data;
    while (SerialNode != NULL){
        Matrix *new_result;
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
        SerialNode = SerialNode->next;
        if (outputLinklist != NULL)
            add_outputNode(outputLinklist, outputNode_create(new_result));
        result = new_result;
        
            
    }
    return result;
}

Matrix* predict_impl(Model *self, Matrix *data){
    return forward(self, data, NULL);
}

void train_impl(Model *self, optim *optimizer, int epoch, dataloader *train_data, dataloader *valid_data, loss_f *loss_function){
    
    
    for (int t = 0;t < epoch;t++){
        double train_loss = 0, valid_loss = 0;
        int trainBatchLength = train_data->data_length / train_data->batch_size;
        int validBatchLength = valid_data->data_length / valid_data->batch_size;
        for (int batchNum = 0;batchNum < trainBatchLength;batchNum++){
            outputNode *outputLinklist = outputNode_create(NULL);
            Matrix *data = train_data->batches[batchNum]->data;
            Matrix *label = train_data->batches[batchNum]->label;

            Matrix *predict = forward(self, data, &outputLinklist);
            Matrix *dz = loss_function->get_gredient(predict, label);
            train_loss += loss_function->get_loss_item(predict, label);
            pop_outputNode(&outputLinklist);
            nn_node *SerialNode = self->end;
            
            while (SerialNode != NULL){
                //決定上一層輸出是誰
                Matrix *last_layer_output = outputLinklist->output;
                if (outputLinklist->output == NULL)
                    last_layer_output = data;
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
        for (int batchNum = 0;batchNum < validBatchLength;batchNum++){
            Matrix *data = valid_data->batches[batchNum]->data;
            Matrix *label = valid_data->batches[batchNum]->label;
            Matrix *predict = forward(self, data, NULL);
            valid_loss += loss_function->get_loss_item(predict, label);
            free_matrix(predict);
        }

        if ((t + 1) % (epoch / 10) == 0){
            printf("epoch: %d, train loss: %lf, valid loss: %lf\n", t + 1, \
            train_loss / trainBatchLength, valid_loss / validBatchLength);
        }


        
    }

    
}


