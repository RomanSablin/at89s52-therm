#include "ds18b20.h"

#define RESET_CODE 0xE0

static uint8_t Ds18b20_Reset() {
	uint8_t *rx;
	uint8_t rx_size;
	UartSetBaud(BAUD_9600);
	UartPut(RESET_CODE);
	rx_size = UartWaitRx(1);
	if (rx_size != 1)
		return 2;
	rx = UartGet();
	if (rx[0] == RESET_CODE)
		return 3;

		return 0;
}

static void Ds18b20_Write(uint8_t _data)
{
	uint8_t bitMask;
	uint8_t data;
	for (bitMask = 0x01; bitMask; bitMask <<= 1)
	{
		data = (bitMask & _data)?0xff:0x00;
		UartPut(data);
		UartPut(data);
	}
	UartFlush();
}

#define DS18B20_CMD_SKIPROM 0xcc
#define DS18B20_CMD_CONVERTTEMP 0x44

int Ds18b20_GetTemp() {
	uint8_t temp = 0;
	temp = Ds18b20_Reset();
	if (temp != 0) //reset
		return temp;
	UartFlush();
	UartSetBaud(BAUD_57600);
	Ds18b20_Write(DS18B20_CMD_SKIPROM);
	Ds18b20_Write(DS18B20_CMD_CONVERTTEMP);
	return 44;
}

