#include "beep.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"


void Beep1_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN(BEEP1_GPIO_PIN_NUM);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_PORT(BEEP1_GPIO_PORT_NUM), &GPIO_InitStructure);
	GPIO_ResetBits(GPIO_PORT(BEEP1_GPIO_PORT_NUM),GPIO_PIN(BEEP1_GPIO_PIN_NUM));
}

void Beep2_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN(BEEP2_GPIO_PIN_NUM);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_PORT(BEEP1_GPIO_PORT_NUM), &GPIO_InitStructure);
	GPIO_ResetBits(GPIO_PORT(BEEP2_GPIO_PORT_NUM),GPIO_PIN(BEEP2_GPIO_PIN_NUM));
}
