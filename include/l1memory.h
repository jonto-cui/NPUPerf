#ifndef L1MEMORY_H
#define L1MEMORY_H

#include "common.h"

SC_MODULE(L1Bank) {
    sc_in<bool> clk;
    sc_in<bool> write_en;
    sc_in<unsigned> addr;
    sc_in<uint128_t> data_in;
    sc_out<uint128_t> data_out;
    
    uint128_t memory[BANK_DEPTH];
    
    SC_CTOR(L1Bank) {
        SC_METHOD(read_write);
        sensitive << clk.pos();
    }
    
    void read_write();
};

SC_MODULE(L1Memory) {
    sc_in<bool> clk;
    vector<sc_in<bool>> write_en;
    vector<sc_in<unsigned>> addr;
    vector<sc_in<uint128_t>> data_in;
    vector<sc_out<uint128_t>> data_out;
    
    vector<L1Bank*> banks;
    
    SC_CTOR(L1Memory);
};

#endif // L1MEMORY_H