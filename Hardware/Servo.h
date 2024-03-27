#include "PWM.h"
#include "PID.h"
#ifndef __SERVO_H
#define __SERVO_H
// 舵机角度范围 
#define MIN_ANGLE_X 0.0f  
#define MAX_ANGLE_X 180.0f  
#define MIN_ANGLE_Y 0.0f  
#define MAX_ANGLE_Y 180.0f  
void Servo_Init(void);
void Servo_SetAngle1(float Angle);
void Servo_SetAngle2(float Angle);
void Servo_SetAngleWithPID1(float Angle, PID_Controller *pid);
void Servo_SetAngleWithPID2(float Angle, PID_Controller *pid);
uint16_t PWM_GetCompare1();
uint16_t PWM_GetCompare1();
float ReadServoAngle1(void);
float ReadServoAngle2(void);
#endif
