#include "l2memory.h"

void L2Memory::read_write() {
    unsigned word_addr = addr.read() * (BANK_WIDTH/8);
    if (write_en.read()) {
        for (int i = 0; i < BANK_WIDTH/8; i++) {
            memory[word_addr + i] = data_in.read().range((i+1)*8-1, i*8);
        }
    } else {
        uint128_t temp;
        for (int i = 0; i < BANK_WIDTH/8; i++) {
            temp.range((i+1)*8-1, i*8) = memory[word_addr + i];
        }
        data_out.write(temp);
    }
}