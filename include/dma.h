// dma.h
#ifndef DMA_H
#define DMA_H

#include "common.h"
#include "l1memory.h"
#include "l2memory.h"

SC_MODULE(DMA) {
    sc_in<bool> clk;
    L1Memory* l1;
    L2Memory* l2;

    SC_CTOR(DMA) {
        SC_THREAD(run);
        sensitive << clk.pos();
    }

    // load指令
    struct LoadJob {
        int l2_addr;
        int l1_bank;
        int length; // unit: 128bit
        bool valid = false;
    } load_job;

    // save指令
    struct SaveJob {
        int l1_bank;
        int l2_addr;
        int length;
        bool valid = false;
    } save_job;

    void set_load(int l2_addr, int bank, int len);
    void set_save(int bank, int l2_addr, int len);

private:
    void run();
};

#endif
