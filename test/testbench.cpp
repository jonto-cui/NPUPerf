#include "npu.h"

int sc_main(int argc, char* argv[]) {
    NPU npu("npu");

    sc_start(1000, SC_NS); // 运行模拟
    return 0;
}
