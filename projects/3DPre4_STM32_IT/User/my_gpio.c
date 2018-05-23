#include "my_gpio.h"
#include "delay.h"

void initGPIO(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  // ʹ�ܶ˿ڸ���ʱ��
	GPIO_InitTypeDef gpio_InitStruct;
	gpio_InitStruct.GPIO_Mode = GPIO_Mode_IPU;  // ��������
	gpio_InitStruct.GPIO_Pin = BUTTON_PIN;
	gpio_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(BUTTON_PORT, &gpio_InitStruct);
}

void initEXTI(void) {
	/* GPIO���ⲿ�ж���·ӳ�� */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2);
	
	EXTI_InitTypeDef exti_InitStruct;
	exti_InitStruct.EXTI_Line = EXTI_Line2;
	exti_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	/* �½��ش��� */
	exti_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	exti_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti_InitStruct);
}

void initNVIC(void) {
	/* �������ȼ�����Ϊ�ڶ��� -- 2λ��ռ2λ��Ӧ */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;//����ṹ��

	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn; //ʹ���ⲿ�ж����ڵ�ͨ��

	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02; //��ռ���ȼ� 2�� 

	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02; //�����ȼ� 2

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ⲿ�ж�ͨ�� 

	NVIC_Init(&NVIC_InitStructure); //���ݽṹ����Ϣ�������ȼ���ʼ�� 
}

void EXTI2_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line2) != RESET) {
		/* �жϷ��� */
		
		/* д�ж��߼����� */
		delay_ms(10);  // ����
		if (READ_BUTTON == RESET) {
			/* ���� */
			/* ������Ӧ���� */
		}
		while(READ_BUTTON == RESET);  // �ȴ�����
		/* ����жϱ�־λ */
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}
