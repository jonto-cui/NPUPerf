#ifndef MAT_H
#define MAT_H

#include "common.h"
#include "l1memory.h"

SC_MODULE(MAT) {
    sc_in<bool> clk;
    L1Memory* l1;

    SC_CTOR(MAT) {
        SC_THREAD(run);
        sensitive << clk.pos();
    }

    void configure(int bank0, int bank1, int dst_bank, int K_len);

private:
    struct Job {
        int bank0, bank1, dst_bank, K_len;
        bool valid = false;
    } job;

    void run();
};

#endif
