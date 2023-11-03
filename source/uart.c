#include <string.h>

#include "uart.h"

#define XBUFLEN 8
#define RBUFLEN 8

static uint8_t rbuf[RBUFLEN];
static uint8_t xbuf[XBUFLEN];
static uint8_t rcnt, xcnt, rpos, xpos;
static __bit busy;

static void UartSetDefault()
{
	rcnt = 0;
	xcnt = 0;
	rpos = 0;
	xpos = 0;
	busy = 0;
}

void UartRxEnable(void)
{
	RI = 0;
	REN = 1;
	rcnt = 0;
}

void UartRxDisable(void)
{
	RI = 0;
	REN = 0;
}

void UartSetBaud(UartBaudrate_t _baudrate)
{
	TR2 = 0;
	UartSetDefault();
	RCAP2H = 0xFF;
	RCAP2L = _baudrate;
	TR2 = 1;
}

void UartInit(UartBaudrate_t _baudrate) {
	ES = 0;
	UartSetDefault();
	SCON = 0x50;
	T2CON = 0x34; // RCLK, TCLK
	PS = 1;
	T2CON = 0x34; // RCLK, TCLK
	RI = 0;
	TI = 0;
	UartSetBaud(_baudrate);
///	UartRxEnable();
	ES = 1;    // UART/SPI Interrupt enable
}

void UartPut(char _c) {
	while (xcnt >= XBUFLEN); /* wait for room in buffer */
	ES = 0;
	if (busy) {
		xbuf[(unsigned char) (xpos + xcnt++) % XBUFLEN] = _c;
	} else {
		SBUF = _c;
		busy = 1;
	}
	ES = 1;
}

uint8_t UartGet()
{
	unsigned char c;
	while (!rcnt); /* wait for character */
	ES = 0;
	rcnt--;
	c = rbuf[rpos++];
	if (rpos >= RBUFLEN)
		rpos = 0;
	ES = 1;
	return (c);
}

#pragma save
#pragma noinduction
void UartSend(uint8_t *_data, uint8_t _size) {
	for (int i=0; i<_size; i++)
		UartPut(_data[i]);
}
#pragma restore

uint8_t UartWaitRx(uint8_t _size)
{
	uint16_t error = 0;
	while(1)
	{
		if ((++error == 0xffff) || (rcnt >= _size))
			break;
	}
	return rcnt;
}

uint8_t UartGetRxSize(void)
{
	return rcnt;
}

void UartFlush()
{
	while(xcnt > 0);
}

void UartInterrupt(void) __interrupt (SI0_VECTOR) __using (1)
{
	if (RI) {
		RI = 0;
		/* don't overwrite chars already in buffer */
		if (rcnt < RBUFLEN)
			rbuf [(uint8_t)(rpos+rcnt++) % RBUFLEN] = SBUF;
	}
	if (TI) {
		TI = 0;
		if (busy = xcnt) { /* Assignment, _not_ comparison! */
			xcnt--;
			SBUF = xbuf [xpos++];
			if (xpos >= XBUFLEN)
				xpos = 0;
		}
	}
}

