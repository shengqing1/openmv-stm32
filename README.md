# 演示效果
https://www.bilibili.com/video/BV1w6421u7JX
# 项目环境

本项目为基于STM32及OpenMV的云台追踪装置，在keil和OpenMV IDE上进行开发

# OpenMV程序思路

openmv程序见文件openmv.py，通过OpenMV对被测物体检测，使用绿色瓶盖作为被测物体，通过查找最大色块程序检测目标，并在图像上绘制目标的轮廓和质心，并将质心的坐标通过串口传给stm32

# STM32F103C8T6程序思路

根据实时接收到的质心坐标，使用PID控制器，通过控制两个舵机的角度使质心一直保持在图像中心附近
