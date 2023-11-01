#include <mcs51/at89x52.h>
#include <string.h>

#include "uart.h"

#ifndef F_CPU
#define F_CPU 11059200UL
#endif

#define UART_TX_SIZE 16
#define UART_RX_SIZE 16

static uint8_t uart_rx_buf[UART_RX_SIZE];
static uint8_t uart_rx_count;

static uint8_t uart_tx_buf[UART_TX_SIZE];
static uint8_t uart_tx_count;
static uint8_t uart_tx_size;

void uart_rx_enable(void)
{
	RI = 0;
	REN = 1;  // Receive Enable
}

void uart_rx_disable(void)
{
	RI = 0;
	REN = 0;  // Receive Enable
}

void uart_init_t1(UartBaudrate_t _baudrate) {
	SCON = 0x50;
	TMOD |= 0x20;
	TH1 = 0xFD;
	TL1 = 0xFD;
	TR1 = 1;    /* 19200bps with 11.059MHz crystal */
	ES = 1;
	uart_rx_count = 0;
	uart_tx_count = 0;
	uart_tx_size = 0;
}

void uart_init_t2(UartBaudrate_t _baudrate) {
	SCON = 0x50;
	T2CON = 0x34; // RCLK, TCLK
	PS = 1;
	T2CON = 0x34; // RCLK, TCLK
	RCAP2H = 0xFF;
	RCAP2L = _baudrate;
	RI = 0;
	TI = 0;
//	uart_rx_enable();
	uart_rx_count = 0;
	uart_tx_count = 0;
	uart_tx_size = 0;
//	ES = 1;    // UART/SPI Interrupt enable
}

void uart_put(char _c) {
	SBUF = _c;
	uart_rx_count = 0;
	while (TI == 0);
	TI = 0;
}

void uart_send(uint8_t *_data, uint8_t _size) {
#if 0
	uint8_t i;
	for (i=0; i<_size; i++)
		uart_tx_buf[i] = _data[i];
	uart_rx_count = 0;
	uart_tx_size = _size;
	uart_tx_count = 0;
	SBUF = uart_tx_buf[uart_tx_count++];
#else
	for (int i=0; i<_size; i++)
		uart_put(_data[i]);
#endif
}

uint8_t uart_wait_rx(uint8_t _size)
{
	uint16_t error = 0;
	while(1)
	{
		if ((++error == 0xffff) || (uart_rx_count >= _size))
			break;
	}
	return uart_rx_count;
}

uint8_t uart_get_rx_size(void)
{
	return uart_rx_count;
}

uint8_t * uart_get(void)
{
	return uart_rx_buf;
}

void UartISR(void) __interrupt (SI0_VECTOR) __using (1)
{
	ES = 0;
	if (TI)
	{
		TI = 0;
		if (uart_tx_count < uart_tx_size)
		{
			SBUF = uart_tx_buf[uart_tx_count++];
		}
	}

	if (RI)
	{
		char temp;
		temp = SBUF;
		RI = 0;
		if ( uart_rx_count < (UART_RX_SIZE-1))
		{
			uart_rx_buf[uart_rx_count++] = temp;
		}
	}
	ES = 1;
}
