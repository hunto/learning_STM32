#include "my_gpio.h"

/* 初始化GPIO */
void init_GPIO(void) {
	BEEP_Init();
	
	/* 初始化输入 */
	Key_Init();
}

void BEEP_Init(void) {
	/* GPIO初始化结构体 */
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	/* 使能PB端口时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	
	GPIO_InitStructure.GPIO_Pin = BEEP_PIN;	// 要初始化的IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 // GPIO模式为推挽输出(Push-Pull)
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // GPIO频率
	GPIO_Init(BEEP_PORT, &GPIO_InitStructure);			 // 初始化GPIO
	BEEP_OFF;						                     
}

void Key_Init(void) {
	/* GPIO初始化结构体 */
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	/* 使能PA,PB端口时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	
	GPIO_InitStructure.GPIO_Pin = KEY_IN;	// 要初始化的IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 // GPIO模式为上拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		 // GPIO频率
	GPIO_Init(KEY_PORT, &GPIO_InitStructure);			 // 初始化GPIO
	
}
#define KEY_UP 1
u8 Key_scan(void) {
#if KEY_UP
	static u8 key_down_0 = 0, key_down_1 = 0;
	if (READ_KEY == KEY_ON) {
		/* 按下状态 */
		delay_ms(10); // 消抖
		if (READ_KEY == KEY_ON) {
			key_down_0 = 1;
		}
	}
	else {
		delay_ms(10); // 消抖
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
