#include "usart.h"
#include <stdio.h>

/* Rx缓冲区 */
uint8_t RxBuffer1[RX_BUFFER_SIZE];
uint16_t RxCount;


void USART_Config(USART_TypeDef* USARTx){
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 19200;                        //速率19200bps
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;        //数据位8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;            //停止位1位
	USART_InitStructure.USART_Parity = USART_Parity_No;                //无校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //无硬件流控
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    //收发模式
	/* Configure USART1 */
	USART_Init(USARTx, &USART_InitStructure);                //配置串口参数函数
	/* Enable USART1 Receive and Transmit interrupts */
	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);                //使能接收中断
	USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);                //使能发送缓冲空中断   
	/* Enable the USART1 */
	USART_Cmd(USARTx, ENABLE);    
}


void USART_SendChar(USART_TypeDef* USARTx, uint8_t data){
	USART_SendData(USARTx, data);
	/* 等待发送完成 */
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET);
}

void USART_SendStr(USART_TypeDef* USARTx, uint8_t* str) {
	uint8_t* tmp = str;
	while((*tmp) != '\0') {
		USART_SendChar(USARTx, (*tmp));
		tmp++;
	}
}


#ifdef REDIRECT_PRINTF 

/* printf重定向 */
int fputc(int ch, FILE* stream)
{
    USART_SendChar(USART1, (uint8_t)ch);
    return ch;
}
#endif

void USART1_IRQHandler(void)      //串口1 中断服务程序
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)       //判断读寄存器是否非空
	{    
		RxBuffer1[RxCount++] = USART_ReceiveData(USART1);   //将读寄存器的数据缓存到接收缓冲区里
		if(RxBuffer1[RxCount - 2]==0x0d
		   &&RxBuffer1[RxCount - 1]==0x0a)//判断结束标志是否是0x0d 0x0a
		{
			RxCount=0;
			/* 读取串口结束， 这里可以写一些结束后的操作 */
			RxBuffer1[RxCount - 2] = '\0';
			USART_SendStr(USART1, RxBuffer1);
		}
	}
	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)  //这段是为了避免STM32 USART 第一个字节发不出去的BUG 
	{ 
		USART_ITConfig(USART1, USART_IT_TXE, DISABLE);    //禁止发缓冲器空中断， 
	}     
}
