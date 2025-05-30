#include "mat.h"

void MAT::configure(int b0, int b1, int db, int K) {
    job = {b0, b1, db, K, true};
}

void MAT::run() {
    while (true) {
        wait();
        if (!job.valid) continue;

        for (int i = 0; i < job.K_len; i += 3) {
            auto a = l1->read(job.bank0, i);
            auto b = l1->read(job.bank1, i);

            data128_t result = a ^ b; // 占位符，真实应是外积+累加
            l1->write(job.dst_bank, i / 3, result);
            wait(3); // 每3cycle一次外积
        }

        job.valid = false;
    }
}
