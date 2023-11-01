#ifndef UART_H_
#define UART_H_

#include <stdint.h>

typedef enum
{
	BAUD_9600 = 0xDC,
	BAUD_115200 = 0xFA
}UartBaudrate_t;

void uart_rx_enable(void);
void uart_rx_disable(void);
void uart_init_t1(UartBaudrate_t _baudrate);
void uart_init_t2(UartBaudrate_t _baudrate);
void uart_put(char _c);
void uart_send(uint8_t *_data, uint8_t _size);
uint8_t uart_wait_rx(uint8_t _size);
uint8_t uart_get_rx_size(void);
uint8_t * uart_get(void);
#endif /* UART_H_ */
