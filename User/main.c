#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Servo.h"
#include "Key.h"
#include "Serial.h"
#include "string.h"
#include "openmv.h"
uint8_t RxData;			//定义用于接收串口数据的变量
int openmv[7];//stm32接收数据数组
int16_t data1;
int16_t data2;
int16_t data3;
int16_t data4;
// 摄像头图像尺寸  
#define CAMERA_WIDTH 320  
#define CAMERA_HEIGHT 240  
// 假设的小球位置  
float ballX = CAMERA_WIDTH / 2; // 小球在图像中的x位置  
float ballY = CAMERA_HEIGHT / 2; // 小球在图像中的y位置  
uint8_t KeyNum;			//定义用于接收键码的变量
float Angle;			//定义角度变量
PID_Controller panPID;  
PID_Controller tiltPID;
float servo_rotation_value=70.0;
float servo_pitch_value=70.0;
uint8_t servo_rotation_direction=0;
uint8_t servo_pitch_direction=1;
int main(void)
{
	/*模块初始化*/
	Servo_Init();		//舵机初始化
	Key_Init();			//按键初始化
	uart_init(115200);
	//Serial_Init();		//串口初始化
  // 初始化PID控制器  
	//目前程序中没用的该PID结构体，仅仅使用P控制器控制舵机，但保留了PID接口，可根据实际情况修改
  PID_Init(&panPID,  0.01f, 0.001f, 0.0f); // 水平轴PID参数需要根据实际情况调整  
  PID_Init(&tiltPID, 0.01f, 0.001f, 0.0f); // 垂直轴PID参数需要根据实际情况调整  
	PID_SetSetpoint(&panPID,0);
	PID_SetSetpoint(&tiltPID,0);
	Angle=90;
	while (1)
	{
    // 假设这里更新了小球的位置  
        // ...  
    // 计算舵机应该调整的角度
		ballX=(uint8_t)data1;
		ballY=(uint8_t)data2;
    float deltaX = ballX - CAMERA_WIDTH / 2;  
    float deltaY = ballY - CAMERA_HEIGHT / 2;  
		camera_move_to_target_close_loop(ballX, ballY, CAMERA_WIDTH/2, CAMERA_HEIGHT/2);
	}
}
