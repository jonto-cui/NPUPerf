TARGET = soc_top

# 找到 src 目录下的所有 cpp 文件
SRC = $(wildcard src/**/*.cpp) $(wildcard src/*.cpp) soc_top.cpp
CXX = g++
CXXFLAGS = -g -O0 -Wall -Iinclude -I/home/cuijt/systemc_project/systemc-2.3.4/include
LDFLAGS = -L/home/cuijt/systemc_project/systemc-2.3.4/lib-linux64 -lsystemc -lm
RPATH = -Wl,-rpath,/home/cuijt/systemc_project/systemc-2.3.4/lib-linux64

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(RPATH) $^ $(LDFLAGS) -o $@

clean:
	$(RM) $(TARGET)
