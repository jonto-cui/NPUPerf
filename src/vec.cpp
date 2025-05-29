#include "vec.h"

void VecModule::vector_operation() {
    while (true) {
        done.write(false);
        wait();
        
        if (start.read()) {
            unsigned len = length.read();
            VecOpType operation = op.read();
            
            if (operation == ACCUMULATE) {
                int32_t sum = 0;
                
                for (unsigned i = 0; i < len; i++) {
                    l1_bank_out->write(src_bank.read());
                    l1_addr_out->write(i);
                    wait();
                    uint128_t data = l1_data_in->read();
                    
                    for (int j = 0; j < 4; j++) { // 128b = 4x32b
                        sum += data.range((j+1)*32-1, j*32);
                    }
                    
                    wait(); // N cycles for accumulation
                }
                
                // Write back the sum
                uint128_t out_data = 0;
                out_data.range(31, 0) = sum;
                
                l1_write_en->write(true);
                l1_bank_out->write(dst_bank.read());
                l1_addr_out->write(0);
                l1_data_out->write(out_data);
                wait();
                l1_write_en->write(false);
            } else {
                // SHIFT_RELU operation
                for (unsigned i = 0; i < len; i++) {
                    l1_bank_out->write(src_bank.read());
                    l1_addr_out->write(i);
                    wait();
                    uint128_t data = l1_data_in->read();
                    
                    uint128_t out_data;
                    // ReLU: shift right by 1 and set negative to 0
                    for (int j = 0; j < 16; j++) {
                        int8_t val = data.range((j+1)*8-1, j*8);
                        int8_t shifted = val >> 1;
                        out_data.range((j+1)*8-1, j*8) = shifted > 0 ? shifted : 0;
                    }
                    
                    // Write back (1 cycle)
                    l1_write_en->write(true);
                    l1_bank_out->write(dst_bank.read());
                    l1_addr_out->write(i);
                    l1_data_out->write(out_data);
                    wait();
                    l1_write_en->write(false);
                }
            }
            
            done.write(true);
        }
    }
}