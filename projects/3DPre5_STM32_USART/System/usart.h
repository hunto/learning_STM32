#ifndef _USART_H_
#define _USART_H_

#include "stm32f10x_conf.h"
#define REDIRECT_PRINTF  // 是否重定向printf

/* RX缓冲区大小 */
#define RX_BUFFER_SIZE 1000

extern uint8_t RxBuffer1[RX_BUFFER_SIZE];
extern uint16_t RxCount;

/* USART初始化 */
void USART_Config(USART_TypeDef* USARTx);

/* USART发送一个字符 */
void USART_SendChar(USART_TypeDef* USARTx, uint8_t data);

/* USART发送字符串 */
void USART_SendStr(USART_TypeDef* USARTx, uint8_t* str);

#endif
