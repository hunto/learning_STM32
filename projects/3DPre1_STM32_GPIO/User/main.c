#include "my_gpio.h"
#include "delay.h"

void beep1(void);
void beep2(void);

int main(void) {
	init_GPIO();
	delay_init();
	
	beep2();
	
	return 0;
}

void beep1(void) {
	while (1) {
		BEEP_ON;
		delay_ms(1000);
		BEEP_OFF;
		delay_ms(1000);
	}
}

void beep2(void) {
	u8 beepSatus = 0;
	while (1) {
		int keyType = Key_scan();
		switch (keyType) {
			case KEY_BEEP:
				if (beepSatus == 0) {
					beepSatus = 1;
					BEEP_ON;
				}
				else {
					beepSatus = 0;
					BEEP_OFF;
				}
				break;
			default:
				break;
		}
	}
}

