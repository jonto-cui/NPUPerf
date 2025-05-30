#include "vec.h"

void VEC::configure(int s, int d, VecOpType o) {
    job = {s, d, o, true};
}

void VEC::run() {
    while (true) {
        wait();
        if (!job.valid) continue;

        for (int i = 0; i < 16; ++i) {
            auto val = l1->read(job.src, i);
            data128_t result = val; // 占位符操作
            l1->write(job.dst, i, result);
            wait();
        }

        job.valid = false;
    }
}
