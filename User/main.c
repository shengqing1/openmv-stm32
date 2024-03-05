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
  PID_Init(&panPID,  0.03f, 0.001f, 0.0f); // 水平轴PID参数需要根据实际情况调整  
  PID_Init(&tiltPID, 0.03f, 0.001f, 0.0f); // 垂直轴PID参数需要根据实际情况调整  
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
		//deltaX=deltaX*0.01;
		//deltaY=deltaY*0.01;
		//deltaX=-deltaX;
    // 使用PID计算误差（图像像素）  
    //PID_Compute(&panPID, ballX);  
    //PID_Compute(&tiltPID, ballY);
		camera_move_to_target_close_loop(ballX, ballY, CAMERA_WIDTH/2, CAMERA_HEIGHT/2);
	  // 控制舵机到PID计算出的角度  
    //Servo_SetAngleWithPID1(panPID.Output, &panPID); // 控制水平轴舵机  
    //Servo_SetAngleWithPID2(tiltPID.Output, &tiltPID); // 控制垂直轴舵机 
    // 延时或其他操作 
		
		// ...
		/*
		if(ballX!=0&&ballY!=0){
		 if (MIN_ANGLE < servo_rotation_value + deltaX && servo_rotation_value + deltaX < MAX_ANGLE){
		servo_rotation_value += deltaX; // 更新旋转值
		 }			 
		 if (MIN_ANGLE < servo_pitch_value + deltaY && servo_pitch_value + deltaY < 90) { // 假设俯仰值也有类似的有效范围检查  
        servo_pitch_value += deltaY; // 更新俯仰值   
    }  
		
	  }
		Servo_SetAngle1(servo_rotation_value);
		Servo_SetAngle2(servo_pitch_value); // 控制水平轴舵机 
		Delay_ms(10);*/
		
		KeyNum = Key_GetNum();			//获取按键键码
		if (KeyNum == 1)				//按键1按下
		{
			Angle = (uint8_t)data4;				//角度变量自增30
			if (Angle > 180)			//角度变量超过180后
			{
				Angle = 0;				//角度变量归零
			}
		}
		//panPID.Output=tiltPID.Output=Angle;
		//Servo_SetAngle1(180.0-(float)ballX*180.0/240.0);			//设置舵机的角度为角度变量Servo_SetAngle1(Angle);			//设置舵机的角度为角度变量
		//Servo_SetAngle2((float)ballY*180.0/240.0);			//设置舵机的角度为角度变量
		
	}
}
