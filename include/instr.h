#ifndef INSTR_H
#define INSTR_H

#include "common.h"
#include "dma.h"
#include "mat.h"
#include "vec.h"

SC_MODULE(Instr) {
    sc_in<bool> clk;
    DMA* dma;
    MAT* mat;
    VEC* vec;

    SC_CTOR(Instr) {
        SC_THREAD(run);
        sensitive << clk.pos();
    }

private:
    void run();
};

#endif
