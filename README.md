# $\pi^x$求解

> 作者：赵文亮
>
> 学号：2016011452

## 运行方式

- 运行x64/Release/PiXP.exe
- 输入$x$，确定精度（精确到小数位数），点击开始求解
- 结果框中显示求解结果，下方显示求解耗时（ms）

## 目录结构

- PiXP/: 源代码
  - Pi.h/Pi.cpp：求解$\pi$
  - LnX.h/LnX.cpp：求解$\ln\pi$
  - EXP.h/EXP.cpp：求解$e^{\ln\pi}=\pi^x$
  - Sqrt3.h/Sqrt3.cpp：求解$\sqrt{3}$
  - main.cpp：主函数
  - PiXP.h/PiXP.cpp：主界面
  - PiXPCalculator.h/PiXPCalculator.cpp：封装了求解全过程，在子线程运行
- PiXP.sln：工程文件
- x64/Release/PiXP.exe：可执行文件
- report.pdf：实验报告

