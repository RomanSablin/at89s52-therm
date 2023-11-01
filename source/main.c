#include "C7Segment3.h"
#include "Misc.h"
#include "Mcu.h"
#include "uart.h"
#include "ds18b20.h"

void main() {
//	uint8_t temp;
//	char *rx;

	McuInit();
//	C7Segment3Init();
	uart_init_t1(BAUD_9600);
//	McuEnableInterrupts();
//	temp = 0;
	while (1) {
		uart_send("Hello, World!\r\n", 15);
//		temp = Ds18b20_GetTemp();
		Delay(10000);
//		C7SegmentSet(temp, 0);
	}
}
