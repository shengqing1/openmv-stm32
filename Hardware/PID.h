#ifndef __PID_H
#define __PID_H
// PID�������ṹ��  
typedef struct  
{  
    float Setpoint;     // �趨Ŀ��ֵ  
    float Input;        // ��ǰ����ֵ  
    float Output;       // �������  
    float Kp;           // ����ϵ��  
    float Ki;           // ����ϵ��  
    float Kd;           // ΢��ϵ��  
    float LastError;     // ��һ�ε����  
    float Integral;     // ������  
} PID_Controller;  
// ���PID������
extern PID_Controller panPID; // ˮƽ�ᣨ��λ�ǣ���PID������  
extern PID_Controller tiltPID; // ��ֱ�ᣨ�����ǣ���PID������    
void PID_Init(PID_Controller *pid, float kp, float ki, float kd);
float PID_Compute(PID_Controller *pid, float input);
void PID_SetInput(PID_Controller *pid, float input); 
void PID_SetSetpoint(PID_Controller *pid, float setpoint);  	
#endif
