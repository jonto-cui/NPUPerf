TARGET = npu_out

# 找到 src 目录下的所有 cpp 文件和测试文件
SRC = $(wildcard src/*.cpp) 
TEST_SRC = test/testbench.cpp
CXX = g++
CXXFLAGS = -g -O0 -w -Iinclude -I/home/jordan/workspace/systemC/systemc-3.0.1/include
LDFLAGS = -L/home/jordan/workspace/systemC/systemc-3.0.1/lib-linux64 -lsystemc -lm
RPATH = -Wl,-rpath,/home/jordan/workspace/systemC/systemc-3.0.1/lib-linux64

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(RPATH) $^ $(LDFLAGS) -o $@

clean:
	$(RM) $(TARGET) *.vcd