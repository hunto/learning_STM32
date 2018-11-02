#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "stm32f10x.h"

#define DISPLAY_H_PORT GPIOB
#define DISPLAY_L_PORT GPIOB

#define NULL 0

typedef unsigned char u8;

void init_display(void);

void display_row(u8 index, u8 content);

u8* set_buffer(u8* content);

u8* display_flash(u8* content);

#endif // _DISPLAY_H_
