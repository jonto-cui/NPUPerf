#include "mat.h"
#include "common.h"
void MatModule::matrix_multiply() {
    while (true) {
        done.write(false);
        wait();
        
        if (start.read()) {
            unsigned m = M.read();
            unsigned n = N.read();
            unsigned k = K.read();
            
            // For each output element
            for (unsigned mi = 0; mi < m; mi++) {
                for (unsigned ni = 0; ni < n; ni++) {
                    int32_t result = 0;
                    
                    // Outer product accumulation
                    for (unsigned ki = 0; ki < k; ki += 16) {
                        // Read from bank A and B
                        l1_bank_out->write(bank_a.read());
                        l1_addr_out->write(mi * (k/16) + (ki/16));
                        wait();
                        uint128_t a_data = l1_data_in_a->read();
                        
                        l1_bank_out->write(bank_b.read());
                        l1_addr_out->write(ni * (k/16) + (ki/16));
                        wait();
                        uint128_t b_data = l1_data_in_b->read();
                        
                        // Perform outer product (3 cycles per 16 elements)
                        for (int i = 0; i < 16; i += 2) {
                            int8_t a0 = a_data.range((i+0)*8+7, (i+0)*8);
                            int8_t a1 = a_data.range((i+1)*8+7, (i+1)*8);
                            int8_t b0 = b_data.range((i+0)*8+7, (i+0)*8);
                            int8_t b1 = b_data.range((i+1)*8+7, (i+1)*8);
                            
                            // Outer product and accumulate (3 cycles)
                            wait(); // Cycle 1: multiply
                            int32_t prod0 = a0 * b0;
                            int32_t prod1 = a1 * b1;
                            
                            wait(); // Cycle 2: multiply
                            result += prod0 + prod1;
                            
                            wait(); // Cycle 3: accumulate
                        }
                    }
                    
                    // Write result to bank_result
                    uint128_t out_data = 0;
                    out_data.range(31, 0) = result;
                    
                    l1_write_en->write(true);
                    l1_bank_out->write(bank_result.read());
                    l1_addr_out->write(mi * n + ni);
                    l1_data_out->write(out_data);
                    wait();
                    l1_write_en->write(false);
                }
            }
            
            done.write(true);
        }
    }
}