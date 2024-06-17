# 用C實作深度學習訓練工具

## 簡介
一個簡單的深度學習工具，能訓練自定義的順序模型

## 目錄
- [使用方法](#使用方法)
- [功能介紹](#功能介紹)


## 使用方法

### 準備資料
- 將資料分成兩個Matrix ** input, target
- input每個Matrix *的大小是(n, 1)，n是input dim
- target每個Matrix *的大小是(n, 1)，n是output dim
- 詳細參考[matrix使用教學](https://github.com/weiso131/neural-network-tool-in-C/blob/main/src/matrix/README.md)

### 初始化dataloader
- 將準備好的data, target傳給dataloader

#### 範例
```c
dataloader *trainDataloader = init_dataloader(trainInput, trainTarget, trainBatchSize, trainBataLength, shuffle);
dataloader *validDataloader = init_dataloader(validInput, validTarget, validBatchSize, validDataLength, shuffle);
```

### 初始化model
- 初始化model將所需要的物件塞給它

#### 範例
```c
Model *myModel = init_model();
myModel->add(myModel, init_Linear(16, input_dim, NULL, NULL));
myModel->add(myModel, init_ReLU());
myModel->add(myModel, init_Linear(4, 16, NULL, NULL));
myModel->add(myModel, init_ReLU());
myModel->add(myModel, init_Linear(target_dim, 4, NULL, NULL));
```

### 開始訓練以及使用
#### 範例
```c
myModel->train(myModel ,init_Adam(0.01, 0.9, 0.999, 1e-8), 1000, trainDataloader, validDataloader, init_CrossEntropy());

Matrix *predict = myModel->predict(myModel, trainInput[0]);
print_matrix(predict);
```



## 功能介紹

