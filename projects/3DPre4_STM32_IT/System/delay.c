#include "delay.h"

//#define DELAY_SYSTICK

#ifdef DELAY_SYSTICK		
static u8  fac_us=0;							// us延时倍乘数			   
static u16 fac_ms=0;							// ms延时倍乘数

/*
 * 初始化延时函数
 */
void delay_init()
{

	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	// 选择外部时钟  HCLK/8
	fac_us = SystemCoreClock / 8000000;				// 外部时钟为系统时钟的1/8 （8M晶振，CPU频率72M）

	fac_ms = (u16)fac_us*1000;					// ms

}								    
  	
/*
 * 延时us
 */
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD = nus*fac_us; 					// 加载计数	  		 
	SysTick->VAL = 0x00;        					// 清空计数器
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;	    // 开始倒数
	do
	{
		temp = SysTick->CTRL;
	}while((temp & 0x01) && !(temp & (1 << 16)));		// 等待时间到达 
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;	// 关闭计数器
	SysTick->VAL = 0X00;      					 // 清空计数器	 
}

/* 
 * 延时ms函数
 */
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;				
	SysTick->VAL =0x00;						
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		  
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	
	SysTick->VAL =0X00;       				 	    
} 
#else

/* 1us中断一次 */
#define SYSTICKPERIOD 1e-6
#define SYSTICKFREQUENCY (1/SYSTICKPERIOD)

/*
 * 初始化延时函数
 */
void delay_init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // 使能TIM2时钟
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	TIM_TimeBaseStructure.TIM_Period = 999;  // 寄存器重载值
	/* 预分频: 计数器+1时间为：预分频/CPU主频 */
	TIM_TimeBaseStructure.TIM_Prescaler = SystemCoreClock / SYSTICKFREQUENCY - 1;
	/* 向上计数 */
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	/* 使能TIMx 在 ARR 上的预装载寄存器 */
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	
	/* 设置更新请求源只在计数器上溢或下溢时产生中断 */
	TIM_UpdateRequestConfig(TIM2, TIM_UpdateSource_Global);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);

}								    
  	
/*
 * 延时us
 */
void delay_us(u32 nus)
{		
 
}

/* 
 * 延时ms函数
 */
void delay_ms(u16 nms)
{	 		  	  
	/* 清零计数器 */
	TIM2->CNT = 0;
	TIM_Cmd(TIM2, ENABLE);
	
	for (int n = 0; n < nms; n++) {
		/* 等待一个延时单位结束 */
		while (TIM_GetFlagStatus(TIM2, TIM_FLAG_Update) != SET) ;
		TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	} 
	TIM_Cmd(TIM2, DISABLE);
} 

#endif



