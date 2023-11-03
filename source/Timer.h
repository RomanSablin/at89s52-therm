#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

#include <mcs51/at89x52.h>

void Timer0Init(void * _interrupt);
void Timer0SetCounter(const uint16_t _value);
void Timer0Enable();
void Timer0Disable();
void Timer0Interrupt (void) __interrupt(TF0_VECTOR);// __using(1);

#endif /* TIMER_H_ */
