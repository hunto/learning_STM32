#ifndef _BEEP_H_
#define _BEEP_H_

#include <stm32f10x_gpio.h>
#include "stm32f10x.h"

#define GPIO_PORT(num) \
 ((num == 0) ? GPIOA : \
  (num == 1) ? GPIOB : \
  (num == 2) ? GPIOC : \
  (num == 3) ? GPIOD : \
  (num == 4) ? GPIOE : \
  (num == 5) ? GPIOF : \
  (num == 6) ? GPIOG : \
  0)
	
#define GPIO_PIN(num) \
 ((num == 0) ? GPIO_Pin_0 : \
  (num == 1) ? GPIO_Pin_1 : \
  (num == 2) ? GPIO_Pin_2 : \
  (num == 3) ? GPIO_Pin_3 : \
  (num == 4) ? GPIO_Pin_4 : \
  (num == 5) ? GPIO_Pin_5 : \
  (num == 6) ? GPIO_Pin_6 : \
  (num == 7) ? GPIO_Pin_7 : \
  (num == 8) ? GPIO_Pin_8 : \
  (num == 9) ? GPIO_Pin_9 : \
  (num == 10) ? GPIO_Pin_10 : \
  (num == 11) ? GPIO_Pin_11: \
  (num == 12) ? GPIO_Pin_12: \
	(num == 13) ? GPIO_Pin_13: \
  (num == 14) ? GPIO_Pin_14: \
  (num == 15) ? GPIO_Pin_15: \
  0)

// <<< Use Configuration Wizard in Context Menu >>>


// <h> ·äÃùÆ÷1_GPIO¿Ú
// 	<o> GPIO port
//		<0=> GPIOA
//		<1=> GPIOB
//		<2=> GPIOC
//    <3=> GPIOD
//		<4=> GPIOE
//    <5=> GPIOF
//    <6=> GPIOG
#define BEEP1_GPIO_PORT_NUM 0
//	<o> GPIO pin
#define BEEP1_GPIO_PIN_NUM 7

// </h>

// <h> ·äÃùÆ÷2_GPIO¿Ú
// 	<o> GPIO port
//		<0=> GPIOA
//		<1=> GPIOB
//		<2=> GPIOC
//    <3=> GPIOD
//		<4=> GPIOE
//    <5=> GPIOF
//    <6=> GPIOG
#define BEEP2_GPIO_PORT_NUM 0
//	<o> GPIO pin
#define BEEP2_GPIO_PIN_NUM 6

// </h>


void Beep1_Init(void);
void Beep2_Init(void);


#endif

// <<< end of configuration section >>>
