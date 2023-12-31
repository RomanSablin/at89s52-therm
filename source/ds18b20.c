#include <stdlib.h>
#include "ds18b20.h"
#include "Misc.h"

#define RESET_CODE 0xE0
static uint8_t Ds18b20_data[9];

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
	for (bitMask = 0x01; bitMask; bitMask <<= 1)
	{
		if (bitMask & _data) {
			UartPut(0xff);
		}
		else {
			UartPut(0xf0);
		}
	}
	UartFlush();
}

static uint8_t Ds18b20_Read()
{
	uint8_t bitMask;
	uint8_t data;
	uint8_t output = 0;
	do {
		if (UartGetRxSize() > 0)
			UartGet();
		else
			break;
	} while (1);
	for (bitMask = 0x01; bitMask; bitMask <<= 1)
	{
		UartPut(0xff);
		data = UartGet();

		if (data == 0xff)
			output |= bitMask;
	}

	return output;
}

#define DS18B20_CMD_SKIPROM 0xcc
#define DS18B20_CMD_CONVERTTEMP 0x44
#define DS18B20_CMD_RSCRATCHPAD 0xbe


char Ds18b20_GetTemp(char *_temperature, char *_sign) {
	char temp = 0;
	temp = Ds18b20_Reset();
	if (temp != 0) //reset
		return -1;

	UartFlush();
	UartSetBaud(BAUD_57600);

	Ds18b20_Write(DS18B20_CMD_SKIPROM);
	Ds18b20_Write(DS18B20_CMD_CONVERTTEMP);

	Delay(35000); // 800 ms

	temp = Ds18b20_Reset();
	if (temp != 0) //reset
		return -1;

	UartSetBaud(BAUD_57600);
	Ds18b20_Write(DS18B20_CMD_SKIPROM); //skip ROM
	Ds18b20_Write(DS18B20_CMD_RSCRATCHPAD); //read scratchpad

	for(int i=0; i<9; i++)
		Ds18b20_data[i] = Ds18b20_Read();

	if(Crc8(Ds18b20_data, 8) == Ds18b20_data[8])
	{
		uint16_t raw;
		raw = Ds18b20_data[1];
		raw <<= 8;
		raw &= 0xff00;
		raw |= Ds18b20_data[0];

		if(raw < 0x7d0)
		{
			raw >>= 4;
			*_sign = 0;
			*_temperature = (uint8_t) raw & 0x7f;
		}
		else
		{
			raw = ((uint16_t)0xffff-(uint16_t)raw)>>4;
			*_sign = 1;
			int8_t st = (int8_t) raw & 0xff;
			*_temperature = abs(st);
		}
		temp = 0;
	}
	else
		temp = -1;

	return temp;
}

