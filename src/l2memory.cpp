// l2memory.cpp
#include "l2memory.h"

void L2Memory::write(addr_t addr, data128_t data) {
    if (addr < memory.size()) {
        memory[addr] = data;
    } else {
        SC_REPORT_WARNING("L2Memory", "Invalid write address.");
    }
}

data128_t L2Memory::read(addr_t addr) {
    if (addr < memory.size()) {
        return memory[addr];
    } else {
        SC_REPORT_WARNING("L2Memory", "Invalid read address.");
        return 0;
    }
}
