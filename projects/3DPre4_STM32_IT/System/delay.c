#include "delay.h"

//#define DELAY_SYSTICK

#ifdef DELAY_SYSTICK		
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
#else

/* 1us�ж�һ�� */
#define SYSTICKPERIOD 1e-6
#define SYSTICKFREQUENCY (1/SYSTICKPERIOD)

/*
 * ��ʼ����ʱ����
 */
void delay_init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // ʹ��TIM2ʱ��
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	TIM_TimeBaseStructure.TIM_Period = 999;  // �Ĵ�������ֵ
	/* Ԥ��Ƶ: ������+1ʱ��Ϊ��Ԥ��Ƶ/CPU��Ƶ */
	TIM_TimeBaseStructure.TIM_Prescaler = SystemCoreClock / SYSTICKFREQUENCY - 1;
	/* ���ϼ��� */
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	/* ʹ��TIMx �� ARR �ϵ�Ԥװ�ؼĴ��� */
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	
	/* ���ø�������Դֻ�ڼ��������������ʱ�����ж� */
	TIM_UpdateRequestConfig(TIM2, TIM_UpdateSource_Global);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);

}								    
  	
/*
 * ��ʱus
 */
void delay_us(u32 nus)
{		
 
}

/* 
 * ��ʱms����
 */
void delay_ms(u16 nms)
{	 		  	  
	/* ��������� */
	TIM2->CNT = 0;
	TIM_Cmd(TIM2, ENABLE);
	
	for (int n = 0; n < nms; n++) {
		/* �ȴ�һ����ʱ��λ���� */
		while (TIM_GetFlagStatus(TIM2, TIM_FLAG_Update) != SET) ;
		TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	} 
	TIM_Cmd(TIM2, DISABLE);
} 

#endif



