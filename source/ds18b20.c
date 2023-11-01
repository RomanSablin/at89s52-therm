#include "ds18b20.h"
#include "uart.h"

#define RESET_CODE 0xE0

static uint8_t Ds18b20_Reset() {
	uint8_t *rx;
	uint8_t rx_size;
	uart_init_t2(BAUD_9600);
	uart_rx_enable();
	uart_put(RESET_CODE);
	rx_size = uart_wait_rx(1);
	if (rx_size != 1)
		return 2;
	rx = uart_get();
	if (rx[0] == RESET_CODE)
		return 3;

		return 0;
}

static void Ds18b20_Write(uint8_t _data)
{
	uint8_t bitMask;
	uart_rx_disable();
	uart_init_t2(BAUD_115200);
	for (bitMask = 0x01; bitMask; bitMask <<= 1)
		uart_put((bitMask & _data)?0xff:0x00);
}

#define DS18B20_CMD_SKIPROM 0xcc
#define DS18B20_CMD_CONVERTTEMP 0x44

int Ds18b20_GetTemp() {
	uint8_t temp;
	temp = Ds18b20_Reset();
	if (temp != 0) //reset
		return temp;

	Ds18b20_Write(DS18B20_CMD_SKIPROM);
	Ds18b20_Write(DS18B20_CMD_CONVERTTEMP);
	return 0;
}

