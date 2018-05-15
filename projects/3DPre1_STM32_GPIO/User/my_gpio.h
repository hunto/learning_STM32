#ifndef _MY_GPIO_H_
#define _MY_GPIO_H_

#include "stm32f10x_conf.h"
#include "delay.h"

#define BEEP_PIN GPIO_Pin_5  // 蜂鸣器使用的IO号
#define BEEP_PORT GPIOB      // 蜂鸣器使用的IO口

#define KEY_PORT GPIOA
#define KEY_IN GPIO_Pin_0  // 按键

#define KEY_ON  0
#define KEY_OFF 1

void init_GPIO(void);
void BEEP_Init(void);
void Key_Init(void);

/* 打开蜂鸣器 -- 端口置1 */
#define BEEP_ON (GPIO_SetBits(BEEP_PORT,BEEP_PIN))

/* 关闭蜂鸣器 -- 端口置0 */
#define BEEP_OFF (GPIO_ResetBits(BEEP_PORT,BEEP_PIN))

/* 输入 */
#define READ_KEY  GPIO_ReadInputDataBit(KEY_PORT,KEY_IN) //读取按键

/* 按键类型 */
enum key_type {
	KEY_BEEP, KEY_NONE
};

/* 按键检测函数 */
u8 Key_scan(void);

#endif
