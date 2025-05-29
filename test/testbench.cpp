#include "npu.h"
#include <systemc.h>
int sc_main(int argc, char* argv[]) {
    sc_clock clk("clk", 10, SC_NS); // 100MHz clock
    
    NPU npu("npu");
    npu.clk(clk);
    
    sc_signal<bool> start, done;
    sc_signal<Instruction> instr;
    
    npu.start(start);
    npu.instr(instr);
    npu.done(done);
    

    
    // Test sequence for 4096x2048x4096 matrix multiplication + ReLU
    start.write(false);
    sc_start(100, SC_NS);
    
    // 1. Load matrix A (4096x2048) to L1 bank 0
    Instruction load_a;
    load_a.type = LOAD;
    load_a.src_addr = 0; // L2 address
    load_a.dst_addr = 0; // L1 bank
    load_a.length = 4096 * 2048/16; // Number of 128-bit words (16 elements per word)
    instr.write(load_a);
    
    start.write(true);
    sc_start(10, SC_NS);
    start.write(false);
    
    while (!done.read()) {
        sc_start(10, SC_NS);
    }
    
    // 2. Load matrix B (2048x4096) to L1 bank 1
    Instruction load_b;
    load_b.type = LOAD;
    load_b.src_addr = 4096 * 2048/16; // L2 address after matrix A
    load_b.dst_addr = 1; // L1 bank
    load_b.length = 2048 * 4096/16; // Number of 128-bit words
    instr.write(load_b);
    
    start.write(true);
    sc_start(10, SC_NS);
    start.write(false);
    
    while (!done.read()) {
        sc_start(10, SC_NS);
    }
    
    // 3. Matrix multiplication (4096x2048) * (2048x4096) = (4096x4096)
    Instruction mat_instr;
    mat_instr.type = MAT_MUL;
    mat_instr.src_addr = 0; // Use bank 0 and 1 as input
    mat_instr.dst_addr = 2; // Store result in bank 2
    mat_instr.M = 4096;
    mat_instr.N = 4096;
    mat_instr.K = 2048;
    instr.write(mat_instr);
    
    start.write(true);
    sc_start(10, SC_NS);
    start.write(false);
    
    while (!done.read()) {
        sc_start(10, SC_NS);
    }
    
    // 4. ReLU operation on result (bank 2 -> bank 3)
    Instruction vec_instr;
    vec_instr.type = VEC_OP;
    vec_instr.src_addr = 2; // From bank 2
    vec_instr.dst_addr = 3; // To bank 3
    vec_instr.length = 4096 * 4096/16; // Number of 128-bit words
    vec_instr.vec_op = SHIFT_RELU;
    instr.write(vec_instr);
    
    start.write(true);
    sc_start(10, SC_NS);
    start.write(false);
    
    while (!done.read()) {
        sc_start(10, SC_NS);
    }
    
    // 5. Save result (bank 3) to L2
    Instruction save_instr;
    save_instr.type = SAVE;
    save_instr.src_addr = 3; // L1 bank
    save_instr.dst_addr = (4096 * 2048 + 2048 * 4096)/16; // L2 address after A and B
    save_instr.length = 4096 * 4096/16; // Number of 128-bit words
    instr.write(save_instr);
    
    start.write(true);
    sc_start(10, SC_NS);
    start.write(false);
    
    while (!done.read()) {
        sc_start(10, SC_NS);
    }
    return 0;
}