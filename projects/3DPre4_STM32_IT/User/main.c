#include "stm32f10x_conf.h"
#include "my_gpio.h"

int main(void) {
	/* ��ʼ�� */
	initGPIO();
	initEXTI();
	initNVIC();
	
	while(1);
	return 0;
}
