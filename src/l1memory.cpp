#include "l1memory.h"

void L1Bank::read_write() {
    if (write_en.read()) {
        memory[addr.read()] = data_in.read();
    }
    data_out.write(memory[addr.read()]);
}

L1Memory::L1Memory(sc_module_name name) : sc_module(name) {
    banks.resize(NUM_BANKS);
    for (int i = 0; i < NUM_BANKS; i++) {
        banks[i] = new L1Bank(sc_gen_unique_name("bank"));
        banks[i]->clk(clk);
        banks[i]->write_en(write_en[i]);
        banks[i]->addr(addr[i]);
        banks[i]->data_in(data_in[i]);
        banks[i]->data_out(data_out[i]);
    }
}