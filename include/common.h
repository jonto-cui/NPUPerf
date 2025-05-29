#ifndef COMMON_H
#define COMMON_H

#include <systemc.h>
#include <vector>
#include <queue>
#include <map>
#include <cstdint>  // 添加cstdint头文件

using namespace sc_core;
using namespace std;

// 数据类型定义
using int8_t = std::int8_t;
using int32_t = std::int32_t;
typedef sc_dt::sc_uint<128> uint128_t;  // 添加sc_dt命名空间

// 常量定义
const unsigned L2_SIZE = 6 * 1024 * 1024;  // 6MiB
const unsigned L1_SIZE = 512 * 1024;       // 512KiB
const unsigned NUM_BANKS = 128;
const unsigned BANK_DEPTH = 256;
const unsigned BANK_WIDTH = 128;           // 128 bits

// 指令类型
enum InstrType {
    LOAD,
    SAVE,
    MAT_MUL,
    VEC_OP,
    NOP
};

// 向量操作类型
enum VecOpType {
    DOT_ADD,
    DOT_MUL,
    ACCUMULATE,
    SHIFT_RELU
};

// 指令格式
struct Instruction {
    InstrType type;
    unsigned src_addr;
    unsigned dst_addr;
    unsigned length;
    VecOpType vec_op;
    unsigned M;
    unsigned N;
    unsigned K;
};


#endif // COMMON_H