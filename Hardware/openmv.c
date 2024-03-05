#include "openmv.h"
#include "Serial.h"
extern int openmv[7];//stm32接收数据数组
extern int16_t data1;
extern int16_t data2;
extern int16_t data3;
extern int16_t data4;
 
 
 
int i=0;
 
void Openmv_Receive_Data(int16_t data)//接收Openmv传过来的数据
{
	static u8 state = 0;
	if(state==0&&data==0x2C)
	{
		state=1;
		openmv[0]=data;
	}
	else if(state==1&&data==7)
	{
		state=2;
		openmv[1]=data;
	}
	else if(state==2)
	{
		state=3;
		openmv[2]=data;
	}
	else if(state==3)
	{
		state = 4;
		openmv[3]=data;
	}
	else if(state==4)
	{
        state = 5;
        openmv[4]=data;
	}
	else if(state==5)
	{
        state = 6;
        openmv[5]=data;
	}
	else if(state==6)		//检测是否接受到结束标志
	{
        if(data == 0x5B)
        {
            state = 0;
            openmv[6]=data;
            Openmv_Data();
        }
        else if(data != 0x5B)
        {
            state = 0;
            for(i=0;i<7;i++)
            {
                openmv[i]=0x00;
            }           
        }
	}    
	else
		{
			state = 0;
            for(i=0;i<7;i++)
            {
                openmv[i]=0x00;
            }
		}
}
 
void Openmv_Data(void)
{
    data1=openmv[2];
    data2=openmv[3];
    data3=openmv[4];
    data4=openmv[5];
 
}
