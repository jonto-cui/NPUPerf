#ifndef VEC_H
#define VEC_H

#include "common.h"
#include "l1memory.h"

SC_MODULE(VEC) {
    sc_in<bool> clk;
    L1Memory* l1;

    SC_CTOR(VEC) {
        SC_THREAD(run);
        sensitive << clk.pos();
    }

    void configure(int src, int dst, VecOpType op);

private:
    struct Job {
        int src, dst;
        VecOpType op;
        bool valid = false;
    } job;

    void run();
};

#endif
