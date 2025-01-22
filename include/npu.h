#include <systemc.h>

SC_MODULE(NPU) {
    sc_in<bool> clk;
    sc_in<double> data_in;
    sc_out<double> data_out; // 输出到外部
    sc_out<bool> ack;

    sc_in<bool> req;       // 数据请求信号
    sc_in<bool> conv_start; // 卷积开始信号
    sc_out<double> mul_result; // 卷积结果

    int process_result;    // 数据处理结果（内部变量）
    int mul_result_internal; // 卷积结果（内部变量）

    void control_logic();          // 数据请求处理
    void update_signals();         // 统一信号更新
    void conv();                   // 卷积操作

    SC_CTOR(NPU) {
        SC_THREAD(control_logic);
        sensitive << clk.pos();

        SC_THREAD(update_signals);
        sensitive << clk.pos();
    }
};
