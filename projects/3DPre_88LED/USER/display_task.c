#include "display_task.h"
#include "display.h"
#include "FreeRTOS.h"
#include "task.h"

void display_task(void * pvParameters) {
	init_display();
	//while(1);
	u8 buffer[8] = CONTENT_H;
	set_buffer(buffer);
	while (1) {
		display_flash(NULL);
		/* 1ms per row */
		vTaskDelay(1 / portTICK_RATE_MS);
	}
}

void display_change_task(void * pvParameters) {
	u8 index = 1;
	u8 count = 0;
	while(1) {
		count += 1;
		if (count == 10) {
			switch (index) {
				case 1: {
					u8 buffer[8] = CONTENT_D1;
					set_buffer(buffer);
					break;
				}
				case 2: {
					u8 buffer[8] = CONTENT_D2;
					set_buffer(buffer);
					break;
				}
				case 3: {
					u8 buffer[8] = CONTENT_D3;
					set_buffer(buffer);
					break;
				}
				case 4: {
					u8 buffer[8] = CONTENT_D4;
					set_buffer(buffer);
					break;
				}
				case 5: {
					u8 buffer[8] = CONTENT_D5;
					set_buffer(buffer);
					break;
				}
				case 6: {
					u8 buffer[8] = CONTENT_D6;
					set_buffer(buffer);
					break;
				}
				case 7: {
					u8 buffer[8] = CONTENT_D7;
					set_buffer(buffer);
					break;
				}
			}
			if (++index == 8) {
				index = 1;
			}
			count = 0;
		}
		else if (count == 9) {
			u8 buffer[8] = CONTENT_EMPTY;
			set_buffer(buffer);
		}
		vTaskDelay(100 / portTICK_RATE_MS);
	}
}
