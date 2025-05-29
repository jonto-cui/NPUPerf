#ifndef INSTR_H
#define INSTR_H

#include "common.h"

SC_MODULE(InstrDispatcher) {
    sc_in<bool> clk;
    sc_in<bool> start;
    sc_in<Instruction> instr;
    sc_out<bool> done;
    
    // Ports to other modules
    sc_out<bool> dma_start;
    sc_out<bool> dma_direction;
    sc_out<unsigned> dma_l2_addr;
    sc_out<unsigned> dma_l1_bank;
    sc_out<unsigned> dma_l1_addr;
    sc_out<unsigned> dma_length;
    sc_in<bool> dma_done;
    
    sc_out<bool> mat_start;
    sc_out<unsigned> mat_bank_a;
    sc_out<unsigned> mat_bank_b;
    sc_out<unsigned> mat_bank_result;
    sc_out<unsigned> mat_M;
    sc_out<unsigned> mat_N;
    sc_out<unsigned> mat_K;
    sc_in<bool> mat_done;
    
    sc_out<bool> vec_start;
    sc_out<VecOpType> vec_op;
    sc_out<unsigned> vec_src_bank;
    sc_out<unsigned> vec_dst_bank;
    sc_out<unsigned> vec_length;
    sc_in<bool> vec_done;
    
    SC_CTOR(InstrDispatcher) {
        SC_CTHREAD(dispatch, clk.pos());
    }
    
    void dispatch();
};

#endif // INSTR_H