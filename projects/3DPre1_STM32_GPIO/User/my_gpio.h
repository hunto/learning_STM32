#ifndef _MY_GPIO_H_
#define _MY_GPIO_H_

#include "stm32f10x_conf.h"
#include "delay.h"

#define BEEP_PIN GPIO_Pin_5  // ������ʹ�õ�IO��
#define BEEP_PORT GPIOB      // ������ʹ�õ�IO��

#define KEY_PORT GPIOA
#define KEY_IN GPIO_Pin_0  // ����

#define KEY_ON  0
#define KEY_OFF 1

void init_GPIO(void);
void BEEP_Init(void);
void Key_Init(void);

/* �򿪷����� -- �˿���1 */
#define BEEP_ON (GPIO_SetBits(BEEP_PORT,BEEP_PIN))

/* �رշ����� -- �˿���0 */
#define BEEP_OFF (GPIO_ResetBits(BEEP_PORT,BEEP_PIN))

/* ���� */
#define READ_KEY  GPIO_ReadInputDataBit(KEY_PORT,KEY_IN) //��ȡ����

/* �������� */
enum key_type {
	KEY_BEEP, KEY_NONE
};

/* ������⺯�� */
u8 Key_scan(void);

#endif
