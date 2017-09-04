/**
 * Example of ws2812_uart library usage.
 *
 * This example shows a simple fixed R, G, B pattern.
 * It's using the ws2812_uart library and output on pin GPIO2 (TXD1) and
 * can not be changed.
 *
 * This sample code is in the public domain.,
 */
#include "espressif/esp_common.h"
#include "FreeRTOS.h"
#include "task.h"
#include "esp/uart.h"

#include "ws2812_uart/ws2812_uart.h"

static void demo(void *pvParameters)
{
	uint32_t ledcount = 3;
	ws2812_uart_init(ledcount);

	rgb_t *leds = malloc(ledcount * sizeof(rgb_t));
	leds[0].R = 255;
	leds[0].G = 0;
	leds[0].B = 0;
	leds[1].R = 0;
	leds[1].G = 255;
	leds[1].B = 0;
	leds[2].R = 0;
	leds[2].G = 0;
	leds[2].B = 255;

	while (1) {
		ws2812_uart_update(leds);

		vTaskDelay(10 / portTICK_PERIOD_MS);
	}
}

void user_init(void)
{
	uart_set_baud(0, 115200);

	xTaskCreate(&demo, "ws2812_task", 256, NULL, 2, NULL);
}

