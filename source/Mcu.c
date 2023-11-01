#include <mcs51/at89x52.h>

#include "Mcu.h"

void McuInit() {
	TMOD = 0x00;
}

void McuEnableInterrupts() {
	EA = 1;
}

void McuDisableInterrupts() {
	EA = 0;
}

