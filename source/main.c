#include "C7Segment3.h"
#include "ds18b20.h"
#include "Misc.h"
#include "Mcu.h"

void main() {
	uint8_t temp;

	McuInit();
	C7Segment3Init();
	McuEnableInterrupts();
	temp = 11;
	UartInit(BAUD_9600);
	while (1) {
		Delay(10000);
		temp = Ds18b20_GetTemp();
		C7SegmentSet(temp, 0);
	}
}
