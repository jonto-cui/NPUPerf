TARGET = npu_out

# 找到 src 目录下的所有 cpp 文件和测试文件
SRC = $(wildcard src/*.cpp) 
TEST_SRC = test/testbench.cpp
CXX = g++
CXXFLAGS = -g -O0 -w -Iinclude -I/home/cuijt/systemc_project/systemc-2.3.4/include
LDFLAGS = -L/home/cuijt/systemc_project/systemc-2.3.4/lib-linux64 -lsystemc -lm
RPATH = -Wl,-rpath,/home/cuijt/systemc_project/systemc-2.3.4/lib-linux64

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(RPATH) $^ $(LDFLAGS) -o $@

clean:
	$(RM) $(TARGET) *.vcd