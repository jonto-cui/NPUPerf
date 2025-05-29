#ifndef DMA_H
#define DMA_H

#include "common.h"

SC_MODULE(DMA) {
    sc_in<bool> clk;
    sc_in<bool> start;
    sc_in<bool> direction;  // 0: L2->L1, 1: L1->L2
    sc_in<unsigned> l2_addr;
    sc_in<unsigned> l1_bank;
    sc_in<unsigned> l1_addr;
    sc_in<unsigned> length;
    sc_out<bool> done;
    
    sc_port<sc_signal_out_if<uint128_t>> l2_data_out;
    sc_port<sc_signal_in_if<uint128_t>> l2_data_in;
    sc_port<sc_signal_out_if<bool>> l2_write_en;
    sc_port<sc_signal_out_if<unsigned>> l2_addr_out;
    
    sc_port<sc_signal_out_if<bool>> l1_write_en;
    sc_port<sc_signal_out_if<unsigned>> l1_bank_out;
    sc_port<sc_signal_out_if<unsigned>> l1_addr_out;
    sc_port<sc_signal_out_if<uint128_t>> l1_data_out;
    sc_port<sc_signal_in_if<uint128_t>> l1_data_in;
    
    SC_CTOR(DMA) {
        SC_CTHREAD(transfer, clk.pos());
    }
    
    void transfer();
};

#endif // DMA_H