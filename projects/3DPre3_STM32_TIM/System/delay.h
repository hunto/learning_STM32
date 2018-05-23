#ifndef __DELAY_H
#define __DELAY_H 			   

#include "stm32f10x_conf.h"

/* 延时初始化函数 -- 延时前必初始化 */
void delay_init(void);

/* 延时ms */
void delay_ms(u16 nms);

/* 延时us */
void delay_us(u32 nus);

#endif
