#ifndef L2MEMORY_H
#define L2MEMORY_H

#include "common.h"

SC_MODULE(L2Memory) {
    sc_in<bool> clk;
    sc_in<bool> write_en;
    sc_in<unsigned> addr;
    sc_in<uint128_t> data_in;
    sc_out<uint128_t> data_out;
    
    uint8_t memory[L2_SIZE];
    
    SC_CTOR(L2Memory) {
        SC_METHOD(read_write);
        sensitive << clk.pos();
    }
    
    void read_write();
};

#endif // L2MEMORY_H