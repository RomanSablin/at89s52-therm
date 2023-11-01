#include <REG52.H>

#include "Mcu.h"

void McuEnableInterrupts() {
	EA = 1;
}

void McuDisableInterrupts() {
	EA = 0;
}

