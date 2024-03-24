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
float x,y;
//uint8_t KeyNum;			//定义用于接收键码的变量
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
	//Key_Init();			//按键初始化
	OLED_Init();
	uart_init(115200);
  // 初始化PID控制器  
  PID_Init(&panPID,  0.005f, 0.0f, 0.003f); // 水平轴PID参数需要根据实际情况调整  
  PID_Init(&tiltPID, 0.005f, 0.0f, 0.003f); // 垂直轴PID参数需要根据实际情况调整  
	PID_SetSetpoint(&panPID,CAMERA_WIDTH/2);
	PID_SetSetpoint(&tiltPID,CAMERA_HEIGHT/2);
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
		if(ballX==0){
			ballX=160;
			ballY=120;
		}
		ballX = (ballX > MAX_X) ? MAX_X : ((ballX < MIN_X) ? MIN_X : ballX);  
    // 使用PID计算误差（图像像素）  
    x=PID_Compute(&panPID, ballX);  
    y=PID_Compute(&tiltPID, ballY);
		//x=(float)(deltaX)*0.005;
		//y=(float)(deltaY)*0.005;
		if (!servo_rotation_direction) { // 如果servo_rotation_direction为false  
        x = -x; // x取反  
    }  
    if (!servo_pitch_direction) { // 如果servo_pitch_direction为false  
        y = -y; // y取反  
    }  
    //在限位内，驱动X轴，Y轴移动 
    if (MIN_ANGLE_X < servo_rotation_value + x && servo_rotation_value + x < MAX_ANGLE_X) {  
        servo_rotation_value += x; // 更新旋转值  
				Servo_SetAngle1(servo_rotation_value); // 控制水平轴舵机  
    }  
    if (MIN_ANGLE_Y < servo_pitch_value + y && servo_pitch_value + y < MAX_ANGLE_Y) { // 假设俯仰值也有类似的有效范围检查  
        servo_pitch_value += y; // 更新俯仰值  
				Servo_SetAngle2(servo_pitch_value); // 控制水平轴舵机  
    }
    Delay_ms(5);		
	}
}
