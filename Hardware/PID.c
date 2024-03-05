#include "stm32f10x.h"  
#include "PID.h"

// PID控制器初始化函数  
void PID_Init(PID_Controller *pid, float kp, float ki, float kd)  
{  
    pid->Setpoint = 0.0f;  
    pid->Input = 0.0f;  
    pid->Output = 0.0f;  
    pid->Kp = kp;  
    pid->Ki = ki;  
    pid->Kd = kd;  
    pid->LastError = 0.0f;  
    pid->Integral = 0.0f;  
}  
  
// PID计算函数  
float PID_Compute(PID_Controller *pid, float input)  
{  
    float error = pid->Setpoint - input;  
    pid->Integral += error;  
    float derivative = error - pid->LastError;  
    pid->Output = pid->Kp * error + pid->Ki * pid->Integral + pid->Kd * derivative;  
    pid->LastError = error;  
    return pid->Output;  
}  
  
// 更新PID输入的函数  
void PID_SetInput(PID_Controller *pid, float input)  
{  
    pid->Input = input;  
}  
  
// 设置PID设定值的函数  
void PID_SetSetpoint(PID_Controller *pid, float setpoint)  
{  
    pid->Setpoint = setpoint;  
}
