#ifndef __WS2812_UART_H__
#define __WS2812_UART_H__

#include <stdint.h>
#include <stdbool.h>

#ifdef  __cplusplus
extern "C" {
#endif

typedef struct {
	unsigned char R;
	unsigned char G;
	unsigned char B;
} rgb_t;

/**
 * Initialize UART to work with ws2812 led strip.
 *
 * @param pixels_number Number of pixels in the strip.
 */
void ws2812_uart_init(uint32_t pixels_number);

/**
 * Update ws2812 pixels.
 *
 * @param pixels Array of 'pixels_number' pixels. The array must contain all
 * the pixels.
 */
void ws2812_uart_update(rgb_t *pixels);

#ifdef  __cplusplus
}
#endif

#endif  // __WS2812_UART_H__

