#ifndef UART_H_
#define UART_H_

#include <stdint.h>

#include <mcs51/at89x52.h>

typedef enum
{
	BAUD_9600 = 0xDC,
	BAUD_57600 = 0xFA
}UartBaudrate_t;

void UartRxEnable(void);
void UartRxDisable(void);
void UartSetBaud(UartBaudrate_t _baudrate);
void UartInit(UartBaudrate_t _baudrate);
void UartPut(char _c);
uint8_t UartGet();
void UartSend(uint8_t *_data, uint8_t _size);
uint8_t UartWaitRx(uint8_t _size);
uint8_t UartGetRxSize(void);
void UartFlush();
void UartInterrupt(void) __interrupt (SI0_VECTOR) __using (1);

#endif /* UART_H_ */
