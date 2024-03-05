#include "stm32f10x.h"                  // Device header

/**
  * 函    数：PWM初始化
  * 参    数：无
  * 返 回 值：无
  */
void PWM_Init(void)  
{  
    /* 开启时钟 */  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // 开启TIM2的时钟  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 开启GPIOA的时钟  
  
    /* GPIO初始化 */  
    GPIO_InitTypeDef GPIO_InitStructure;  
      
    // 初始化PA1为TIM2的CH1  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; // 改为PA0  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_Init(GPIOA, &GPIO_InitStructure); // 将PA0引脚初始化为复用推挽输出  
      
    // 初始化PA2为TIM2的CH2  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; // 改为PA1  
    GPIO_Init(GPIOA, &GPIO_InitStructure); // 将PA1引脚初始化为复用推挽输出  
  
    /* 配置时钟源 */  
    TIM_InternalClockConfig(TIM2); // 选择TIM2为内部时钟  
  
    /* 时基单元初始化 */  
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;  
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;  
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  
    TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1; // 计数周期  
    TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1; // 预分频器  
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;  
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);  
  
    /* 输出比较初始化 - CH1 */  
    TIM_OCInitTypeDef TIM_OCInitStructure;  
    TIM_OCStructInit(&TIM_OCInitStructure);  
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
    TIM_OCInitStructure.TIM_Pulse = 0; // 初始的CCR值  
    TIM_OC1Init(TIM2, &TIM_OCInitStructure); // 配置TIM2的输出比较通道1  
  
    /* 输出比较初始化 - CH2 */  
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; // CH2同样使用PWM模式1  
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; // CH2输出极性也设置为高  
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // CH2输出使能  
    TIM_OCInitStructure.TIM_Pulse = 0; // CH2初始的CCR值  
    TIM_OC2Init(TIM2, &TIM_OCInitStructure); // 配置TIM2的输出比较通道2  
  
    /* TIM使能 */  
    TIM_Cmd(TIM2, ENABLE);  
  
    /* 自动重载预装载使能 */  
    TIM_ARRPreloadConfig(TIM2, ENABLE);  
}
/**
  * 函    数：PWM设置CCR
  * 参    数：Compare 要写入的CCR的值，范围：0~100
  * 返 回 值：无
  * 注意事项：CCR和ARR共同决定占空比，此函数仅设置CCR的值，并不直接是占空比
  *           占空比Duty = CCR / (ARR + 1)
  */
void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM2, Compare);		//设置CCR2的值
}
void PWM_SetCompare2(uint16_t Compare)
{
	TIM_SetCompare2(TIM2, Compare);		//设置CCR2的值
}

