#include "dma.h"

void DMA::transfer() {
    while (true) {
        done.write(false);
        wait();
        
        if (start.read()) {
            unsigned remaining = length.read();
            unsigned current_l2 = l2_addr.read();
            unsigned current_l1_bank = l1_bank.read();
            unsigned current_l1_addr = l1_addr.read();
            
            while (remaining > 0) {
                if (!direction.read()) { // L2 -> L1
                    l2_addr_out->write(current_l2);
                    wait();
                    
                    uint128_t data = l2_data_in->read();
                    l1_write_en->write(true);
                    l1_bank_out->write(current_l1_bank);
                    l1_addr_out->write(current_l1_addr);
                    l1_data_out->write(data);
                } else { // L1 -> L2
                    l1_bank_out->write(current_l1_bank);
                    l1_addr_out->write(current_l1_addr);
                    wait();
                    
                    uint128_t data = l1_data_in->read();
                    l2_write_en->write(true);
                    l2_addr_out->write(current_l2);
                    l2_data_out->write(data);
                }
                
                wait();
                l1_write_en->write(false);
                l2_write_en->write(false);
                
                current_l2++;
                current_l1_addr++;
                remaining--;
                
                wait();
            }
            
            done.write(true);
        }
    }
}