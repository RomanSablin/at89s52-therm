#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

void Timer0Init(void * _interrupt);
void Timer0SetCounter(const uint16_t _value);
void Timer0Enable();
void Timer0Disable();

#endif /* TIMER_H_ */
