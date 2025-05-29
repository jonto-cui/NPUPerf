#ifndef MAT_H
#define MAT_H

#include "common.h"

SC_MODULE(MatModule) {
    sc_in<bool> clk;
    sc_in<bool> start;
    sc_in<unsigned> bank_a;
    sc_in<unsigned> bank_b;
    sc_in<unsigned> bank_result;
    sc_in<unsigned> M;
    sc_in<unsigned> N;
    sc_in<unsigned> K;
    sc_out<bool> done;
    
    sc_port<sc_signal_out_if<bool>> l1_write_en;
    sc_port<sc_signal_out_if<unsigned>> l1_bank_out;
    sc_port<sc_signal_out_if<unsigned>> l1_addr_out;
    sc_port<sc_signal_out_if<uint128_t>> l1_data_out;
    sc_port<sc_signal_in_if<uint128_t>> l1_data_in_a;
    sc_port<sc_signal_in_if<uint128_t>> l1_data_in_b;
    
    SC_CTOR(MatModule) {
        SC_CTHREAD(matrix_multiply, clk.pos());
    }
    
    void matrix_multiply();
};

#endif // MAT_H