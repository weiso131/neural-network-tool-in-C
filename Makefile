# 定義編譯器
CC = gcc

# 定義編譯選項
CFLAGS = -Wall -g

# 定義目標文件名
TARGET = test_model

# 定義源文件資料夾
SRC_DIR = src

# 查找源文件資料夾及其子資料夾中的所有 .c 文件
SOURCES = $(shell find $(SRC_DIR) -name "*.c")

# 定義主文件
MAIN = test_model.c

# 定義對象文件列表，包含main.c編譯的對象文件
OBJECTS = $(MAIN:.c=.o) $(SOURCES:.c=.o)

# 規則：編譯所有對象文件並鏈接成最終可執行文件
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) -lm

# 規則：生成對象文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理命令
clean:
	rm -f $(TARGET) $(OBJECTS)
