#include "dma.h"

void DMA::set_load(int l2_addr, int bank, int len) {
    load_job = {l2_addr, bank, len, true};
}

void DMA::set_save(int bank, int l2_addr, int len) {
    save_job = {bank, l2_addr, len, true};
}

void DMA::run() { 
    while (true) {
        wait();
        if (load_job.valid) {
            for (int i = 0; i < load_job.length; ++i) {
                auto data = l2->read(load_job.l2_addr + i);
                l1->write(load_job.l1_bank, i, data);
                wait(); // 每个cycle搬一个128bit
            }
            load_job.valid = false;
        }

        if (save_job.valid) {
            for (int i = 0; i < save_job.length; ++i) {
                auto data = l1->read(save_job.l1_bank, i);
                l2->write(save_job.l2_addr + i, data);
                wait();
            }
            save_job.valid = false;
        }
    }
}
