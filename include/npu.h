#ifndef NPU_H
#define NPU_H

#include "common.h"
#include "l1memory.h"
#include "l2memory.h"
#include "dma.h"
#include "mat.h"
#include "vec.h"
#include "instr.h"

SC_MODULE(NPU) {
    sc_clock clk;

    L1Memory l1;
    L2Memory l2;
    DMA dma;
    MAT mat;
    VEC vec;
    Instr instr;

    SC_CTOR(NPU)
        : clk("clk", 1, SC_NS),
          l1("l1"), l2("l2"),
          dma("dma"), mat("mat"), vec("vec"), instr("instr")
    {
        dma.clk(clk);
        dma.l1 = &l1;
        dma.l2 = &l2;

        mat.clk(clk);
        mat.l1 = &l1;

        vec.clk(clk);
        vec.l1 = &l1;

        instr.clk(clk);
        instr.dma = &dma;
        instr.mat = &mat;
        instr.vec = &vec;
    }
};

#endif
