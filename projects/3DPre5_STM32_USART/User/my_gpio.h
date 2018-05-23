#ifndef _MY_GPIO_H_
#define _MY_GPIO_H_

#include "stm32f10x_conf.h"

#define BUTTON_PIN GPIO_Pin_2
#define BUTTON_PORT GPIOE

#define READ_BUTTON GPIO_ReadInputDataBit(BUTTON_PORT, BUTTON_PIN)

/* ��ʼ��GPIO���� */
void initGPIO(void);

/* �����ж����ȼ����� */
void initNVIC(void);

#endif
