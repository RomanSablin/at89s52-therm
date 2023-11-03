#include "Timer.h"

void (*sT0Handler)(void);

#define TIMER_VALUE 0xD700

void Timer0Init(void *_handler) {
	sT0Handler = _handler;
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

void Timer0Interrupt (void) __interrupt(TF0_VECTOR) //__using(1)
{
	Timer0SetCounter(TIMER_VALUE);
	sT0Handler();
}

