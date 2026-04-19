# --- 變數設定 ---
CC = gcc
CFLAGS = -Wall -Wextra -I include
LDFLAGS = -lm
TARGET = financial_calc

# --- 尋找所有的 .c 檔案並轉換成對應的 .o 檔名 ---
SRCS = src/main.c src/stack.c src/calculator.c
OBJS = $(SRCS:.c=.o)

# --- 預設目標 ---
all: $(TARGET)

# --- 連結執行檔 ---
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# --- 編譯各個 .c 成為 .o ---
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# --- 清除編譯產生的檔案 ---
clean:
	rm -f $(OBJS) $(TARGET)