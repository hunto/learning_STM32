#include "usart.h"
#include <stdio.h>

/* Rx������ */
uint8_t RxBuffer1[RX_BUFFER_SIZE];
uint16_t RxCount;


void USART_Config(USART_TypeDef* USARTx){
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 19200;                        //����19200bps
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;        //����λ8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;            //ֹͣλ1λ
	USART_InitStructure.USART_Parity = USART_Parity_No;                //��У��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  //��Ӳ������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    //�շ�ģʽ
	/* Configure USART1 */
	USART_Init(USARTx, &USART_InitStructure);                //���ô��ڲ�������
	/* Enable USART1 Receive and Transmit interrupts */
	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);                //ʹ�ܽ����ж�
	USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);                //ʹ�ܷ��ͻ�����ж�   
	/* Enable the USART1 */
	USART_Cmd(USARTx, ENABLE);    
}


void USART_SendChar(USART_TypeDef* USARTx, uint8_t data){
	USART_SendData(USARTx, data);
	/* �ȴ�������� */
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

/* printf�ض��� */
int fputc(int ch, FILE* stream)
{
    USART_SendChar(USART1, (uint8_t)ch);
    return ch;
}
#endif

void USART1_IRQHandler(void)      //����1 �жϷ������
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)       //�ж϶��Ĵ����Ƿ�ǿ�
	{    
		RxBuffer1[RxCount++] = USART_ReceiveData(USART1);   //�����Ĵ��������ݻ��浽���ջ�������
		if(RxBuffer1[RxCount - 2]==0x0d
		   &&RxBuffer1[RxCount - 1]==0x0a)//�жϽ�����־�Ƿ���0x0d 0x0a
		{
			RxCount=0;
			/* ��ȡ���ڽ����� �������дһЩ������Ĳ��� */
			RxBuffer1[RxCount - 2] = '\0';
			USART_SendStr(USART1, RxBuffer1);
		}
	}
	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)  //�����Ϊ�˱���STM32 USART ��һ���ֽڷ�����ȥ��BUG 
	{ 
		USART_ITConfig(USART1, USART_IT_TXE, DISABLE);    //��ֹ�����������жϣ� 
	}     
}
