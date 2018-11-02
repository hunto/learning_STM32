#include "display.h"

/* 
 * init dispay: set port as output mode
 */
/*
 * B0 - r1
 * B1 - r2
 * B2 - r3
 * A8 - r4
 * A9 - r5
 * B5 - r6
 * B6 - r7
 * B7 - r8
 */ 
void init_display(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = 0xFFFF; // all pin
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DISPLAY_H_PORT, &GPIO_InitStructure);
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(DISPLAY_H_PORT, 0xFFFF);
	GPIO_ResetBits(GPIOA, 0xFFFF);
	GPIO_SetBits(GPIOA, GPIO_Pin_9|GPIO_Pin_8);
	//GPIO_ResetBits(DISPLAY_H_PORT, GPIO_Pin_15);
	GPIO_SetBits(GPIOB, 0x00FF);
}

void display_row(u8 index, u8 content) {
	/* transpose content: high2low, low-high, exp: 10010010 -> 01001001 */
	u8 tmp = 0;
	for (u8 j = 0; j < 8; j++) {
		tmp = tmp | ((content >> (7 - j) & 0x01) << j); 
	}
	content = tmp;
	/* set all H pins to low-level */
	GPIO_ResetBits(GPIOB, 0x00FF);
	GPIO_ResetBits(GPIOA, 0x0300);
	//GPIO_ResetBits(GPIOA, 0xFFFF);
	/* set H port (row) to high-level */
	if (index == 3) {
		GPIO_SetBits(GPIOA, 0x0100);
	}
	else if (index == 4) {
		GPIO_SetBits(GPIOA, 0x0200);
	}
	else {
		GPIO_SetBits(GPIOB, 0x01 << index);
	}
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
	GPIO_SetBits(GPIOB, 0xFF00);
	GPIO_ResetBits(GPIOB, ((uint16_t)content) << 8);
}

void trans_buffer(u8* content) {
	
	for (u8 i = 0; i < 8; i++) {
		u8 tmp = 0;
		for (u8 j = 0; j < 8; j++) {
			tmp = tmp | ((content[i] >> (7 - j) & 0x01) << j); 
		}
		content[i] = tmp;
	}
}

u8* set_buffer(u8* content) {
	static u8 buffer[8] = {0,};
	if (content != NULL) {
		for (u8 i = 0; i < 8; i++) {
			buffer[i] = content[i];
		}
	}
	//trans_buffer(buffer);
	return buffer;
}


u8* display_flash(u8* content) {
	static u8 row = 0;
	if (content != NULL) {
		row = 0;
		set_buffer(content);
	}
	u8* buffer = set_buffer(NULL); // get buffer
	display_row(row, buffer[row]);
	if (++row == 8) {
		row = 0;
	}
	return buffer;
}


