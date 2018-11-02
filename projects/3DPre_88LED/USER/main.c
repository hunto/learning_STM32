#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "misc.h"
#include "beep.h"
#include "display_task.h"
#include "display.h"

void LED0_Task(void * pvParameters);
void LED1_Task(void * pvParameters);

int main(void)
{
    xTaskCreate(display_task, (const char *)"Display", 
				configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 3, NULL);
	xTaskCreate(display_change_task, (const char *)"DisplayChange", 
				configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 3, NULL);
    vTaskStartScheduler();
	while(1);
}

void LED0_Task(void * pvParameters)
{
	Beep1_Init();
    while (1)
    {
		GPIO_SetBits(GPIO_PORT(BEEP1_GPIO_PORT_NUM),GPIO_PIN(BEEP1_GPIO_PIN_NUM));
        vTaskDelay(1000 / portTICK_RATE_MS);
		GPIO_ResetBits(GPIO_PORT(BEEP1_GPIO_PORT_NUM),GPIO_PIN(BEEP1_GPIO_PIN_NUM));
		vTaskDelay(100 / portTICK_RATE_MS);
    }
}

void LED1_Task(void * pvParameters)
{
	Beep2_Init();
    while (1)
    {
        GPIO_SetBits(GPIO_PORT(BEEP2_GPIO_PORT_NUM),GPIO_PIN(BEEP2_GPIO_PIN_NUM));
        vTaskDelay(10000 / portTICK_RATE_MS);
				GPIO_ResetBits(GPIO_PORT(BEEP2_GPIO_PORT_NUM),GPIO_PIN(BEEP2_GPIO_PIN_NUM));
				vTaskDelay(12 / portTICK_RATE_MS);
    }
}
