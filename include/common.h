// common.h
#ifndef COMMON_H
#define COMMON_H

#include <systemc>
#include <vector>
#include <iostream>

using namespace sc_core;
using namespace sc_dt;
using namespace std;

const int DATA_WIDTH = 128;      // 每个bank位宽
const int BANK_NUM = 128;        // L1Memory中的bank数
const int BANK_DEPTH = 256;      // 每个bank的深度
const int L2_SIZE_BYTES = 6 * 1024 * 1024; // 6MiB

using data128_t = sc_biguint<DATA_WIDTH>;
typedef sc_uint<32> addr_t;

enum VecOpType {
    DOT_ADD,
    DOT_MUL,
    ACC
};

#endif
 