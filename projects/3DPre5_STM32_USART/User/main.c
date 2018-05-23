#include "stm32f10x_conf.h"
#include "my_gpio.h"
#include "usart.h"

int main(void) {
	/* ≥ı ºªØ */
	initGPIO();
	initNVIC();
	USART_Config(USART1);
	
	while(1);
	return 0;
}
