#include "PWM.h"
#include "PID.h"
#ifndef __SERVO_H
#define __SERVO_H
// ¶æ»ú½Ç¶È·¶Î§ 
#define MIN_ANGLE 0.0f  
#define MAX_ANGLE 150.0f  
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
