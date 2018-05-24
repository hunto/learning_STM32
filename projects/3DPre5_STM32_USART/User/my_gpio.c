#include "my_gpio.h"
#include "delay.h"

void initGPIO(void) {
	/* ʹ��ʱ�� */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1 |
							RCC_APB2Periph_GPIOA | 
							RCC_APB2Periph_AFIO  , ENABLE);  
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;                      //USART1 TX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;             //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);                     //A�˿� 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                  //USART1 RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //���ÿ�©����
	GPIO_Init(GPIOA, &GPIO_InitStructure);                      //A�˿� 
}

void initNVIC(void) {
	/*  �ṹ����*/
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Configure the NVIC Preemption Priority Bits */  
	/* Configure one bit for preemption priority */
	/* ���ȼ��� ˵������ռ���ȼ����õ�λ�����������ȼ����õ�λ��   ��������1�� 7 */    
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);      
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;                     //���ô���1�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;             //��ռ���ȼ� 0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                //�����ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                    //ʹ��
	NVIC_Init(&NVIC_InitStructure);
}

