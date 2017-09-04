# Component makefile for extras/ws2812_uart

# expected anyone using ws2812_uart driver includes it as 'ws2812_uart/ws2812_uart.h'
INC_DIRS += $(ws2812_uart_ROOT)..

# args for passing into compile rule generation
ws2812_uart_SRC_DIR =  $(ws2812_uart_ROOT)

$(eval $(call component_compile_rules,ws2812_uart))
