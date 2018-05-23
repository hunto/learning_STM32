#ifndef _USART_H_
#define _USART_H_

#include "stm32f10x_conf.h"
#define REDIRECT_PRINTF  // �Ƿ��ض���printf

/* RX��������С */
#define RX_BUFFER_SIZE 1000

extern uint8_t RxBuffer1[RX_BUFFER_SIZE];
extern uint16_t RxCount;

/* USART��ʼ�� */
void USART_Config(USART_TypeDef* USARTx);

/* USART����һ���ַ� */
void USART_SendChar(USART_TypeDef* USARTx, uint8_t data);

/* USART�����ַ��� */
void USART_SendStr(USART_TypeDef* USARTx, uint8_t* str);

#endif
