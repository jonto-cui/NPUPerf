#include "instr.h"

void InstrDispatcher::dispatch() {
    while (true) {
        done.write(false);
        wait();
        
        if (start.read()) {
            Instruction current_instr = instr.read();
            
            switch (current_instr.type) {
                case LOAD:
                    dma_direction.write(false); // L2->L1
                    dma_l2_addr.write(current_instr.src_addr);
                    dma_l1_bank.write(current_instr.dst_addr);
                    dma_l1_addr.write(0);
                    dma_length.write(current_instr.length);
                    dma_start.write(true);
                    wait();
                    while (!dma_done.read()) wait();
                    dma_start.write(false);
                    break;
                    
                case SAVE:
                    dma_direction.write(true); // L1->L2
                    dma_l2_addr.write(current_instr.dst_addr);
                    dma_l1_bank.write(current_instr.src_addr);
                    dma_l1_addr.write(0);
                    dma_length.write(current_instr.length);
                    dma_start.write(true);
                    wait();
                    while (!dma_done.read()) wait();
                    dma_start.write(false);
                    break;
                    
                case MAT_MUL:
                    mat_bank_a.write(current_instr.src_addr);
                    mat_bank_b.write(current_instr.src_addr + 1);
                    mat_bank_result.write(current_instr.dst_addr);
                    mat_M.write(current_instr.M);
                    mat_N.write(current_instr.N);
                    mat_K.write(current_instr.K);
                    mat_start.write(true);
                    wait();
                    while (!mat_done.read()) wait();
                    mat_start.write(false);
                    break;
                    
                case VEC_OP:
                    vec_src_bank.write(current_instr.src_addr);
                    vec_dst_bank.write(current_instr.dst_addr);
                    vec_length.write(current_instr.length);
                    vec_op.write(current_instr.vec_op);
                    vec_start.write(true);
                    wait();
                    while (!vec_done.read()) wait();
                    vec_start.write(false);
                    break;
                    
                default:
                    break;
            }
            
            done.write(true);
        }
    }
}