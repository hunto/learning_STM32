#include "delay.h"

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


