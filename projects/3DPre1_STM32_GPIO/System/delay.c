#include "delay.h"

static u8  fac_us=0;							// us��ʱ������			   
static u16 fac_ms=0;							// ms��ʱ������

			   
/*
 * ��ʼ����ʱ����
 */
void delay_init()
{

	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	// ѡ���ⲿʱ��  HCLK/8
	fac_us = SystemCoreClock / 8000000;				// �ⲿʱ��Ϊϵͳʱ�ӵ�1/8 ��8M����CPUƵ��72M��

	fac_ms = (u16)fac_us*1000;					// ms

}								    
  	
/*
 * ��ʱus
 */
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD = nus*fac_us; 					// ���ؼ���	  		 
	SysTick->VAL = 0x00;        					// ��ռ�����
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;	    // ��ʼ����
	do
	{
		temp = SysTick->CTRL;
	}while((temp & 0x01) && !(temp & (1 << 16)));		// �ȴ�ʱ�䵽�� 
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;	// �رռ�����
	SysTick->VAL = 0X00;      					 // ��ռ�����	 
}

/* 
 * ��ʱms����
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


