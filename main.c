#include "C7Segment3.h"
#include "Misc.h"
#include "Mcu.h"

void main() {
	uint8_t temp;
	C7Segment3Init();
	McuEnableInterrupts();
	temp = 0;
	while (1) {
		Delay(10000);
		C7SegmentSet(temp, 0);
		if (++temp > 120)
			temp = 0;
	}
}
