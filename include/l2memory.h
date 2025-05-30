// l2memory.h
#ifndef L2MEMORY_H
#define L2MEMORY_H

#include "common.h"

SC_MODULE(L2Memory) {
    std::vector<data128_t> memory;

    SC_CTOR(L2Memory) {
        memory.resize(L2_SIZE_BYTES / (DATA_WIDTH / 8)); // 每128bit算一个slot
    }

    void write(addr_t addr, data128_t data);
    data128_t read(addr_t addr);
};

#endif
