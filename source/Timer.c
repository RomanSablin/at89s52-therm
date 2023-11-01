#include <mcs51/at89x52.h>

#include "Timer.h"

void (*sInterrupt)(void);

#define TIMER_VALUE 0xD700

void Timer0Init(void *_interrupt) {
	sInterrupt = _interrupt;
	TMOD |= 0x01;       //Timer0 mode 1
	TR0 = 1;           //turn ON Timer0
	Timer0SetCounter(TIMER_VALUE);
	Timer0Enable();
}

void Timer0SetCounter(const uint16_t _value) {
	TH0 = _value >> 8;
	TL0 = _value & 0xff;
}

void Timer0Enable() {
	ET0 = 1;
}

void Timer0Disable() {
	ET0 = 0;
}

void Timer0ISR(void) __interrupt (TF0_VECTOR) __using (1)
{
	static char stat = 0;
	Timer0SetCounter(TIMER_VALUE);
	sInterrupt();
}

