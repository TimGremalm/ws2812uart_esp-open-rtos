#include "ws2812_uart.h"
#include "FreeRTOS.h"
#include "espressif/esp_common.h"
#include "esp/uart.h"

/* WS2812B
Data transfer time:	1.25μs (±150ns)
Reset time:			Above 50µs
Bit timing:			0 code	0.35	+	0.90	= 1.25µs
							T0H			T0L
					1 code	0.90	+	0.35	= 1.25µs
							T1H			T1L
LED packet 24 bit:
	-------------------------
	| Green	| Red	| Blue	|
	| 8 bit	| 8 bit	| 8 bit	|
	| G7-G0	| R7-R0	| B7-B0	|
	-------------------------
*/
const char T0 = 0b00011110;		//1100000	2/7 = 72%
const char T1 = 0b00010000;		//1110000	5/7 = 28%

static uint32_t lednum;

void create_led_byte(char* target, int value) {
	for (int i=0; i<8; i++) {
		target[i] = (1 << (7-i)) & value ? T1 : T0;
	}
}

int uart_write(int uart, const char *ptr, int len) {
	for (int i = 0; i < len; i++) {
		uart_putc(uart, ptr[i]);
	}
	return len;
}

void ws2812_uart_init(uint32_t pixels_number) {
	//Enable GPIO2
	iomux_set_pullup_flags(gpio_to_iomux(2), IOMUX_PIN_OUTPUT_ENABLE);

	//Redirect UART1 to GPIO2
	iomux_set_function(gpio_to_iomux(2), IOMUX_GPIO2_FUNC_UART1_TXD);

	vPortEnterCritical();
	WRITE_PERI_REG(UART_CONF0(1), UART_TXD_INV | (1 << UART_STOP_BIT_NUM_S) | (0 << UART_BIT_NUM_S));
	vPortExitCritical();

	//Set baud rate
	uart_set_baud(1, 6000000);

	lednum = pixels_number;
}

void ws2812_uart_update(rgb_t *pixels) {
	char bufferout[24*lednum];

	for (int led=0; led<lednum; led++) {
		create_led_byte(&bufferout[led*24+0], pixels[led].G);
		create_led_byte(&bufferout[led*24+8], pixels[led].R);
		create_led_byte(&bufferout[led*24+16], pixels[led].B);
	}

	vPortEnterCritical();
	uart_write(1, bufferout, 24*lednum);
	vPortExitCritical();
}

