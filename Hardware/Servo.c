#include "stm32f10x.h"                  // Device header
#include "Servo.h"
#include "Delay.h"
extern PID_Controller panPID; // 水平轴（方位角）的PID控制器  
extern PID_Controller tiltPID; // 垂直轴（俯仰角）的PID控制器 
extern float servo_rotation_value;
extern float servo_pitch_value;
extern uint8_t servo_rotation_direction;
extern uint8_t servo_pitch_direction;
/**
  * 函    数：舵机初始化
  * 参    数：无
  * 返 回 值：无
  */
void Servo_Init(void)
{
	PWM_Init();									//初始化舵机的底层PWM
}
/**
  * 函    数：舵机设置角度
  * 参    数：Angle 要设置的舵机角度，范围：0~180
  * 返 回 值：无
  */
void Servo_SetAngle1(float Angle)
{
	Angle = (Angle > MAX_ANGLE_X) ? MAX_ANGLE_X : ((Angle < MIN_ANGLE_X) ? MIN_ANGLE_X : Angle);  
	PWM_SetCompare1(Angle / 180 * 2000 + 500);	//设置占空比
												//将角度线性变换，对应到舵机要求的占空比范围上
}
void Servo_SetAngle2(float Angle)
{
	Angle = (Angle > MAX_ANGLE_Y) ? MAX_ANGLE_Y : ((Angle < MIN_ANGLE_Y) ? MIN_ANGLE_Y : Angle);  
	PWM_SetCompare2(Angle / 180 * 2000 + 500);	//设置占空比
												//将角度线性变换，对应到舵机要求的占空比范围上
}

uint16_t PWM_GetCompare1()  
{  
    return (uint16_t)(TIM2->CCR1);  
}
uint16_t PWM_GetCompare2()  
{  
    return (uint16_t)(TIM2->CCR2);  
}
/**  
 * 函数：读取舵机角度1  
 * 返回值：舵机的当前估算角度，单位为度  
 */  
float ReadServoAngle1(void)  
{  
    uint16_t pwmValue = PWM_GetCompare1();; // 假设这是获取TIM2的CH1当前PWM值的函数  
    float angle = (pwmValue - 500) / 2000.0f * 180; // 反向计算角度  
    return angle;  
}  
/**  
 * 函数：读取舵机角度2  
 * 返回值：舵机的当前估算角度，单位为度  
 */  
float ReadServoAngle2(void)  
{  
    uint16_t pwmValue = PWM_GetCompare2(); // 假设这是获取TIM2的CH2当前PWM值的函数  
    float angle = (pwmValue - 500) / 2000.0f * 180; // 反向计算角度  
    return angle;  
}
void camera_move_increment(float x, float y) {  
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
    Delay_ms(10);		
}  
//移动摄像头使其对准目标
//target_x,target_y-希望对准的坐标
//camera_x,camera_y-图像中心的坐标
void camera_move_to_target_close_loop(int target_x, int target_y, int laser_x, int laser_y) {  
	camera_move_increment((float)(target_x - laser_x)*0.01, (float)(target_y - laser_y)*0.01);//只有P控制器
	//camera_move_increment((float)PID_Compute(&panPID,(target_x - laser_x)), (float)PID_Compute(&tiltPID,(target_y - laser_y)));//PID控制器
}
