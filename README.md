 ---

# JTSoC: A Simple SystemC-Based SoC Simulation

## 项目简介  
JTSoC 是一个基于 SystemC 的简单 SoC 模拟项目。该项目包含以下模块：  
- **CPU**: 负责发起数据处理请求。  
- **NPU**: 接收 CPU 数据并进行处理（例如简单的倍增操作）。  
- **DDR**: 用于数据的存储和读取。  
- **SharedMemory**: 提供一个共享存储区域，供 CPU 和其他模块交换数据。  

整个系统通过信号连接，每个模块独立运行。通过仿真，展示了一个完整的数据流处理流程。

---

## 目录结构  
```
JTSoC/
├── src/               # 源代码
│   ├── cpu.cpp        # CPU 模块实现
│   ├── npu.cpp        # NPU 模块实现
│   ├── ddr.cpp        # DDR 模块实现
│   ├── sharememory.cpp# SharedMemory 模块实现
│   ├── top.cpp        # 顶层模块连接与系统仿真逻辑
│   ├── cpu.h          # CPU 模块头文件
│   ├── npu.h          # NPU 模块头文件
│   ├── ddr.h          # DDR 模块头文件
│   ├── sharememory.h  # SharedMemory 模块头文件
├── Makefile           # 项目构建脚本
├── README.md          # 项目说明文件
└── .gitignore         # Git 忽略配置
```

---

## 环境要求  
- **SystemC**: 版本 2.3.4  
- **编译器**: GCC 4.8 或更高版本，支持 C++11  

---

## 编译与运行  
### 1. 编译项目  
在项目根目录运行以下命令：  
```bash
make
```

成功后，会生成可执行文件 `SoC_Simulation`。

### 2. 运行仿真  
执行以下命令运行仿真：  
```bash
./SoC_Simulation
```

---

## 模块说明  
### **1. CPU**  
- 发起数据处理请求，并将数据发送给 NPU 或 SharedMemory。  
- 支持简单的请求和应答机制。

### **2. NPU**  
- 接收来自 CPU 的数据并进行处理，例如执行简单的算术运算（数据倍增）。  
- 将处理后的数据转发至 DDR。

### **3. DDR**  
- 模拟数据存储功能，可以接收和发送数据。  
- 支持读/写操作。

### **4. SharedMemory**  
- 提供一个共享存储空间，用于模块间数据传输。

---

## 仿真示例  
运行仿真后，日志中会打印关键信息，类似以下内容：  
```
[System] CPU starts sending data to NPU at 10 ns
[CPU] Sending data: 5 at 10 ns
[NPU] Received data: 5, Processed data: 10 at 20 ns
[System] CPU data transfer to NPU complete at 30 ns
[System] NPU starts processing and transferring data to DDR at 30 ns
[DDR] Writing data: 10 at 40 ns
...
```

日志清晰记录了数据流的每一步，包括各模块的交互时间点和操作状态。

---

## 项目扩展  
- 支持更多的 NPU 算法，例如矩阵运算、卷积操作等。  
- 实现更复杂的存储管理机制（例如分块存储）。  
- 集成 DMA 模块进行高效数据传输。  

---

## 贡献与支持  
欢迎提交代码优化和功能扩展的建议！如果在运行项目时遇到问题，请联系开发者或提交 issue。

--- 

## 开发者  
CUIJT  

---