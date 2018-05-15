#ifndef __DELAY_H
#define __DELAY_H 			   

#include "stm32f10x_conf.h"

/* ��ʱ��ʼ������ -- ��ʱǰ�س�ʼ�� */
void delay_init(void);

/* ��ʱms */
void delay_ms(u16 nms);

/* ��ʱus */
void delay_us(u32 nus);

#endif
