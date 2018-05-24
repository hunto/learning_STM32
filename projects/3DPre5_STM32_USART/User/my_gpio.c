#include "my_gpio.h"
#include "delay.h"

void initGPIO(void) {
	/* 使能时钟 */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 |
							RCC_APB2Periph_GPIOA | 
							RCC_APB2Periph_AFIO  , ENABLE);  
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;                      //USART1 TX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;             //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);                     //A端口 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                  //USART1 RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //复用开漏输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);                      //A端口 
}

void initNVIC(void) {
	/*  结构声明*/
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Configure the NVIC Preemption Priority Bits */  
	/* Configure one bit for preemption priority */
	/* 优先级组 说明了抢占优先级所用的位数，和子优先级所用的位数   在这里是1， 7 */    
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);      
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;                     //设置串口1中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;             //抢占优先级 0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                //子优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                    //使能
	NVIC_Init(&NVIC_InitStructure);
}

