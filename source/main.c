#include "C7Segment3.h"
#include "ds18b20.h"
#include "Misc.h"
#include "Mcu.h"

void main() {
	char temp;
	char sign;

	McuInit();
	C7Segment3Init();
	C7SegmentReset();
	McuEnableInterrupts();
	UartInit(BAUD_9600);
	while (1) {
		Delay(10000);
		if (Ds18b20_GetTemp(&temp, &sign) == 0)
			C7SegmentSet(temp, sign);
	}
}
