#ifndef NPU_H
#define NPU_H

#include "common.h"
#include "l2memory.h"
#include "l1memory.h"
#include "dma.h"
#include "mat.h"
#include "vec.h"
#include "instr.h"

SC_MODULE(NPU) {
    sc_in<bool> clk;
    sc_in<bool> start;
    sc_in<Instruction> instr;
    sc_out<bool> done;
    
    // Instantiate all modules
    L2Memory l2_mem;
    L1Memory l1_mem;
    DMA dma;
    MatModule mat;
    VecModule vec;
    InstrDispatcher instr_disp;
    
    // Signals
    sc_signal<bool> dma_start, dma_direction, dma_done;
    sc_signal<unsigned> dma_l2_addr, dma_l1_bank, dma_l1_addr, dma_length;
    sc_signal<uint128_t> dma_l2_data_out, dma_l2_data_in;
    sc_signal<bool> dma_l2_write_en;
    sc_signal<unsigned> dma_l2_addr_out;
    
    sc_signal<bool> dma_l1_write_en;
    sc_signal<unsigned> dma_l1_bank_out, dma_l1_addr_out;
    sc_signal<uint128_t> dma_l1_data_out, dma_l1_data_in;
    
    sc_signal<bool> mat_start, mat_done;
    sc_signal<unsigned> mat_bank_a, mat_bank_b, mat_bank_result;
    sc_signal<unsigned> mat_M, mat_N, mat_K;
    
    sc_signal<bool> mat_l1_write_en;
    sc_signal<unsigned> mat_l1_bank_out, mat_l1_addr_out;
    sc_signal<uint128_t> mat_l1_data_out, mat_l1_data_in_a, mat_l1_data_in_b;
    
    sc_signal<bool> vec_start, vec_done;
    sc_signal<VecOpType> vec_op;
    sc_signal<unsigned> vec_src_bank, vec_dst_bank, vec_length;
    
    sc_signal<bool> vec_l1_write_en;
    sc_signal<unsigned> vec_l1_bank_out, vec_l1_addr_out;
    sc_signal<uint128_t> vec_l1_data_out, vec_l1_data_in;
    
    // L1 memory signals
    vector<sc_signal<bool>> l1_write_en;
    vector<sc_signal<unsigned>> l1_addr;
    vector<sc_signal<uint128_t>> l1_data_in;
    vector<sc_signal<uint128_t>> l1_data_out;
    
    SC_CTOR(NPU);
    
    void l1_arbiter();
};

#endif // NPU_H