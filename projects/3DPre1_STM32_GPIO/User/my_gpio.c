#include "my_gpio.h"

/* ��ʼ��GPIO */
void init_GPIO(void) {
	BEEP_Init();
	
	/* ��ʼ������ */
	Key_Init();
}

void BEEP_Init(void) {
	/* GPIO��ʼ���ṹ�� */
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	/* ʹ��PB�˿�ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	
	GPIO_InitStructure.GPIO_Pin = BEEP_PIN;	// Ҫ��ʼ����IO��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 // GPIOģʽΪ�������(Push-Pull)
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // GPIOƵ��
	GPIO_Init(BEEP_PORT, &GPIO_InitStructure);			 // ��ʼ��GPIO
	BEEP_OFF;						                     
}

void Key_Init(void) {
	/* GPIO��ʼ���ṹ�� */
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	/* ʹ��PA,PB�˿�ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	
	GPIO_InitStructure.GPIO_Pin = KEY_IN;	// Ҫ��ʼ����IO��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 // GPIOģʽΪ��������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		 // GPIOƵ��
	GPIO_Init(KEY_PORT, &GPIO_InitStructure);			 // ��ʼ��GPIO
	
}
#define KEY_UP 1
u8 Key_scan(void) {
#if KEY_UP
	static u8 key_down_0 = 0, key_down_1 = 0;
	if (READ_KEY == KEY_ON) {
		/* ����״̬ */
		delay_ms(10); // ����
		if (READ_KEY == KEY_ON) {
			key_down_0 = 1;
		}
	}
	else {
		delay_ms(10); // ����
		if (READ_KEY == KEY_OFF) {
			if (key_down_0 == 1) {
				key_down_0 = 0;
				return KEY_BEEP;
			}
		}
	}
	
#else
	if (READ_KEY == KEY_ON) {
		delay_ms(10);
		if (READ_KEY == KEY_ON) {
			return KEY_BEEP;
		}
	}
	if (READ_KEY == KEY_ON) {
		delay_ms(10);
		if (READ_KEY == KEY_ON) {
			return KEY_BEEP;
		}
	}
#endif
	return KEY_NONE;
}
