# 演示效果
https://www.bilibili.com/video/BV1w6421u7JX
# 项目环境

本项目为基于STM32及OpenMV的云台追踪装置，在keil和OpenMV IDE上进行开发

# OpenMV程序思路

openmv程序见文件openmv.py，通过OpenMV对被测物体检测，使用绿色瓶盖作为被测物体，通过查找最大色块程序检测目标，并在图像上绘制目标的轮廓和质心，并将质心的坐标通过串口传给stm32

# STM32F103C8T6程序思路

根据实时接收到的质心坐标，使用PID控制器，通过控制两个舵机的角度使质心一直保持在图像中心附近
# 注意事项
将openmv的P4接到stm32的PA10，P5接到PA9，舵机接线根据自己的硬件分别将信号线接在PA0和PA1，另外舵机的限位也需要根据自己的硬件修改
