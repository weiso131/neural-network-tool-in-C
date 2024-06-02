#include "matrix/matrix.h"

typedef struct {
    Matrix* (*get_gredient)(Matrix*, Matrix*);//模型預測, 正確答案值
    double (*get_loss_item)(Matrix*, Matrix*);//模型預測, 正確答案值
}loss_f;

loss_f* init_CrossEntropy();
//回傳一個實作是依據crossentropy的loss_f
//要檢查是否經過softmax，沒有的話要噴錯之類的
loss_f* init_MSELoss();
//回傳一個實作是依據MSELoss的loss_f
