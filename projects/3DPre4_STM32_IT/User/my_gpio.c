#include "my_gpio.h"
#include "delay.h"

void initGPIO(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  // 使能端口复用时钟
	GPIO_InitTypeDef gpio_InitStruct;
	gpio_InitStruct.GPIO_Mode = GPIO_Mode_IPU;  // 上拉输入
	gpio_InitStruct.GPIO_Pin = BUTTON_PIN;
	gpio_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(BUTTON_PORT, &gpio_InitStruct);
}

void initEXTI(void) {
	/* GPIO与外部中断线路映射 */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2);
	
	EXTI_InitTypeDef exti_InitStruct;
	exti_InitStruct.EXTI_Line = EXTI_Line2;
	exti_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	/* 下降沿触发 */
	exti_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	exti_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti_InitStruct);
}

void initNVIC(void) {
	/* 设置优先级分组为第二组 -- 2位抢占2位响应 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;//定义结构体

	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn; //使能外部中断所在的通道

	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02; //抢占优先级 2， 

	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02; //子优先级 2

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能外部中断通道 

	NVIC_Init(&NVIC_InitStructure); //根据结构体信息进行优先级初始化 
}

void EXTI2_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line2) != RESET) {
		/* 中断发生 */
		
		/* 写中断逻辑代码 */
		delay_ms(10);  // 消抖
		if (READ_BUTTON == RESET) {
			/* 按下 */
			/* 做出对应操作 */
		}
		while(READ_BUTTON == RESET);  // 等待松手
		/* 清除中断标志位 */
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}
