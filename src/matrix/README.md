# matrix 使用教學

## 將double array指派給matrix
- 將double array的指標傳給matrix->entry即可

### 範例
```c
double input_entry[] = {0.1, 0.5, 0.6, 0.89, 0.34};
Matrix *data = init_matrix(5, 1);
data->entry = input_entry;
```
