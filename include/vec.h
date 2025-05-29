#ifndef VEC_H
#define VEC_H

#include "common.h"

SC_MODULE(VecModule) {
    sc_in<bool> clk;
    sc_in<bool> start;
    sc_in<VecOpType> op;
    sc_in<unsigned> src_bank;
    sc_in<unsigned> dst_bank;
    sc_in<unsigned> length;
    sc_out<bool> done;
    
    sc_port<sc_signal_out_if<bool>> l1_write_en;
    sc_port<sc_signal_out_if<unsigned>> l1_bank_out;
    sc_port<sc_signal_out_if<unsigned>> l1_addr_out;
    sc_port<sc_signal_out_if<uint128_t>> l1_data_out;
    sc_port<sc_signal_in_if<uint128_t>> l1_data_in;
    
    SC_CTOR(VecModule) {
        SC_CTHREAD(vector_operation, clk.pos());
    }
    
    void vector_operation();
};

#endif // VEC_H