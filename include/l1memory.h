#ifndef L1MEMORY_H
#define L1MEMORY_H

#include "common.h"

#define BANK_NUM   128
#define BANK_DEPTH 256

SC_MODULE(L1Memory) {
    // 二维 sc_signal 向量：128 个 bank，每个有 256 depth
    sc_vector<sc_vector<sc_signal<data128_t>>> banks;

    SC_CTOR(L1Memory) : banks("banks") {
        banks.init(BANK_NUM);
        for (int i = 0; i < BANK_NUM; ++i)
            banks[i].init(BANK_DEPTH);
    }
    void write(int bank_id, int addr, data128_t data);
    data128_t read(int bank_id, int addr);
};

#endif
