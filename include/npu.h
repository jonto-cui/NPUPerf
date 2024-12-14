#include <systemc.h>

SC_MODULE(NPU) {
    sc_in<bool> clk;
    sc_in<int> data_in;
    sc_out<int> data_out; // 输出到外部
    sc_out<bool> ack;

    sc_in<bool> req;       // 数据请求信号
    sc_in<bool> mul_start; // 乘法开始信号
    sc_out<int> mul_result; // 乘法结果

    int process_result;    // 数据处理结果（内部变量）
    int mul_result_internal; // 乘法结果（内部变量）

    void control_logic();          // 数据请求处理
    void process_data();           // 数据处理
    void perform_multiplication(); // 乘法逻辑
    void update_signals();         // 统一信号更新
    void conv();                   // TODO:支持卷积运算，使用vector等

    SC_CTOR(NPU) {
        SC_THREAD(control_logic);
        sensitive << clk.pos();

        SC_METHOD(process_data);
        sensitive << data_in;

        SC_METHOD(perform_multiplication);
        sensitive << data_in << mul_start;

        SC_THREAD(update_signals);
        sensitive << clk.pos();
    }
};
