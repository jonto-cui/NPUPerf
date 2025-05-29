#include "npu.h"

NPU::NPU(sc_module_name name) : 
    sc_module(name),
    l2_mem("l2_mem"), 
    l1_mem("l1_mem"), 
    dma("dma"), 
    mat("mat"), 
    vec("vec"), 
    instr_disp("instr_disp") 
{
    // Initialize L1 memory signals
    l1_write_en.resize(NUM_BANKS);
    l1_addr.resize(NUM_BANKS);
    l1_data_in.resize(NUM_BANKS);
    l1_data_out.resize(NUM_BANKS);
    
    // Connect L1 memory
    for (int i = 0; i < NUM_BANKS; i++) {
        l1_mem.write_en[i](l1_write_en[i]);
        l1_mem.addr[i](l1_addr[i]);
        l1_mem.data_in[i](l1_data_in[i]);
        l1_mem.data_out[i](l1_data_out[i]);
    }
    
    // Connect DMA
    dma.clk(clk);
    dma.start(dma_start);
    dma.direction(dma_direction);
    dma.l2_addr(dma_l2_addr);
    dma.l1_bank(dma_l1_bank);
    dma.l1_addr(dma_l1_addr);
    dma.length(dma_length);
    dma.done(dma_done);
    
    dma.l2_data_out(dma_l2_data_out);
    dma.l2_data_in(dma_l2_data_in);
    dma.l2_write_en(dma_l2_write_en);
    dma.l2_addr_out(dma_l2_addr_out);
    
    dma.l1_write_en(dma_l1_write_en);
    dma.l1_bank_out(dma_l1_bank_out);
    dma.l1_addr_out(dma_l1_addr_out);
    dma.l1_data_out(dma_l1_data_out);
    dma.l1_data_in(dma_l1_data_in);
    
    // Connect MAT
    mat.clk(clk);
    mat.start(mat_start);
    mat.bank_a(mat_bank_a);
    mat.bank_b(mat_bank_b);
    mat.bank_result(mat_bank_result);
    mat.M(mat_M);
    mat.N(mat_N);
    mat.K(mat_K);
    mat.done(mat_done);
    
    mat.l1_write_en(mat_l1_write_en);
    mat.l1_bank_out(mat_l1_bank_out);
    mat.l1_addr_out(mat_l1_addr_out);
    mat.l1_data_out(mat_l1_data_out);
    mat.l1_data_in_a(mat_l1_data_in_a);
    mat.l1_data_in_b(mat_l1_data_in_b);
    
    // Connect VEC
    vec.clk(clk);
    vec.start(vec_start);
    vec.op(vec_op);
    vec.src_bank(vec_src_bank);
    vec.dst_bank(vec_dst_bank);
    vec.length(vec_length);
    vec.done(vec_done);
    
    vec.l1_write_en(vec_l1_write_en);
    vec.l1_bank_out(vec_l1_bank_out);
    vec.l1_addr_out(vec_l1_addr_out);
    vec.l1_data_out(vec_l1_data_out);
    vec.l1_data_in(vec_l1_data_in);
    
    // Connect Instruction Dispatcher
    instr_disp.clk(clk);
    instr_disp.start(start);
    instr_disp.instr(instr);
    instr_disp.done(done);
    
    instr_disp.dma_start(dma_start);
    instr_disp.dma_direction(dma_direction);
    instr_disp.dma_l2_addr(dma_l2_addr);
    instr_disp.dma_l1_bank(dma_l1_bank);
    instr_disp.dma_l1_addr(dma_l1_addr);
    instr_disp.dma_length(dma_length);
    instr_disp.dma_done(dma_done);
    
    instr_disp.mat_start(mat_start);
    instr_disp.mat_bank_a(mat_bank_a);
    instr_disp.mat_bank_b(mat_bank_b);
    instr_disp.mat_bank_result(mat_bank_result);
    instr_disp.mat_M(mat_M);
    instr_disp.mat_N(mat_N);
    instr_disp.mat_K(mat_K);
    instr_disp.mat_done(mat_done);
    
    instr_disp.vec_start(vec_start);
    instr_disp.vec_op(vec_op);
    instr_disp.vec_src_bank(vec_src_bank);
    instr_disp.vec_dst_bank(vec_dst_bank);
    instr_disp.vec_length(vec_length);
    instr_disp.vec_done(vec_done);
    
    // Connect L2 memory
    l2_mem.clk(clk);
    l2_mem.write_en(dma_l2_write_en);
    l2_mem.addr(dma_l2_addr_out);
    l2_mem.data_in(dma_l2_data_out);
    l2_mem.data_out(dma_l2_data_in);
    
    // Arbitration for L1 memory access
    SC_METHOD(l1_arbiter);
    sensitive << dma_l1_write_en << dma_l1_bank_out << dma_l1_addr_out << dma_l1_data_out
             << mat_l1_write_en << mat_l1_bank_out << mat_l1_addr_out << mat_l1_data_out
             << vec_l1_write_en << vec_l1_bank_out << vec_l1_addr_out << vec_l1_data_out;
    
    // Connect L1 memory data inputs
    dma_l1_data_in = l1_data_out[dma_l1_bank_out.read()];
    mat_l1_data_in_a = l1_data_out[mat_l1_bank_out.read()];
    mat_l1_data_in_b = l1_data_out[mat_l1_bank_out.read() + 1];
    vec_l1_data_in = l1_data_out[vec_l1_bank_out.read()];
}

void NPU::l1_arbiter() {
    // Priority: DMA > MAT > VEC
    if (dma_l1_write_en.read()) {
        l1_write_en[dma_l1_bank_out.read()].write(true);
        l1_addr[dma_l1_bank_out.read()].write(dma_l1_addr_out.read());
        l1_data_in[dma_l1_bank_out.read()].write(dma_l1_data_out.read());
    } else if (mat_l1_write_en.read()) {
        l1_write_en[mat_l1_bank_out.read()].write(true);
        l1_addr[mat_l1_bank_out.read()].write(mat_l1_addr_out.read());
        l1_data_in[mat_l1_bank_out.read()].write(mat_l1_data_out.read());
    } else if (vec_l1_write_en.read()) {
        l1_write_en[vec_l1_bank_out.read()].write(true);
        l1_addr[vec_l1_bank_out.read()].write(vec_l1_addr_out.read());
        l1_data_in[vec_l1_bank_out.read()].write(vec_l1_data_out.read());
    } else {
        for (int i = 0; i < NUM_BANKS; i++) {
            l1_write_en[i].write(false);
        }
    }
}