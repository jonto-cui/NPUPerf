#include "instr.h"

void Instr::run() {
    wait(10); // 等待初始化完成

    dma->set_load(0, 0, 16); // L2 addr=0 → bank0
    wait(20); // load完成

    dma->set_load(100, 1, 16); // L2 addr=100 → bank1
    wait(20);

    mat->configure(0, 1, 2, 16);
    wait(100); // 等待mat完成计算

    vec->configure(2, 3, DOT_ADD);
    wait(50);

    dma->set_save(3, 200, 16); // bank3 → L2 addr=200
    wait(20);
}
