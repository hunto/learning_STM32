#ifndef _MY_GPIO_H_
#define _MY_GPIO_H_

#include "stm32f10x_conf.h"

#define BUTTON_PIN GPIO_Pin_2
#define BUTTON_PORT GPIOE

#define READ_BUTTON GPIO_ReadInputDataBit(BUTTON_PORT, BUTTON_PIN)

/* 初始化GPIO函数 */
void initGPIO(void);

/* 配置中断优先级函数 */
void initNVIC(void);

#endif
