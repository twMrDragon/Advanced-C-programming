# 編譯器與選項
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Iinclude

# 原始碼與目標檔
SRCS := $(wildcard src/*.cpp) main.cpp
OBJS := $(SRCS:.cpp=.o)

# 最終執行檔
TARGET := main

# 預設目標
all: $(TARGET)

# 編譯執行檔
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# 編譯每個 .cpp 檔為 .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清除編譯產物
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
