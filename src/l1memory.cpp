#include "l1memory.h"

void L1Memory::write(int bank_id, int addr, data128_t data) {
    if (bank_id < BANK_NUM && addr < BANK_DEPTH) {
        banks[bank_id][addr].write(data);
    } else {
        SC_REPORT_WARNING("L1Memory", "Invalid write access.");
    }
}

data128_t L1Memory::read(int bank_id, int addr) {
    if (bank_id < BANK_NUM && addr < BANK_DEPTH) {
        return banks[bank_id][addr].read();
    } else {
        SC_REPORT_WARNING("L1Memory", "Invalid read access.");
        return 0;
    }
}
