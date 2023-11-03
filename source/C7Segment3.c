#include <mcs51/at89x52.h>

#include "C7Segment3.h"
#include "Misc.h"

#define TABLE_SIZE 12
volatile uint8_t mMemory[3];
volatile uint8_t mCur;

static const uint8_t mDigitTable[TABLE_SIZE] = {dig_0, dig_1, dig_2, dig_3, dig_4, dig_5, dig_6, dig_7, dig_8, dig_9, dig_minus, dig_off};

void C7Segment3Init()
{
	mCur = 0;
	mMemory[0] = 0;
	mMemory[1] = 0;
	mMemory[2] = 0;
	P1 |= ~((1<<simDIG1)|(1<<simDIG2)|(1<<simDIG3));
	P2 = 0xFF;
	Timer0Init(C7Segment3Show);
}

void C7SegmentSet(uint8_t _val, uint8_t _sign)
{
	Char2Bcd(_val, mMemory);
	if(_sign != 0)
		mMemory[0] = 10;
}

void C7Segment3SetDigit(uint8_t _dig)
{
	if(_dig < TABLE_SIZE)
		P2 = mDigitTable[_dig];
	else
		P2 = mDigitTable[10];
}

void C7Segment3Show()
{
	switch (mCur)
	{
		case 0:
			mCur=1;
			P1 &= ~(1<<simDIG3);
			C7Segment3SetDigit(mMemory[0]);
			P1 |= (1<<simDIG1);
		break;
		case 1:
			mCur=2;
			P1 &= ~(1<<simDIG1);
			C7Segment3SetDigit(mMemory[1]);
			P1 |= (1<<simDIG2);
		break;
		default: 
			mCur=0;
			P1 &= ~(1<<simDIG2);
			C7Segment3SetDigit(mMemory[2]);
			P1 |= (1<<simDIG3);
		break;
	}
}

void SetSegmentWait()
{
	mMemory[0] = 11;
	mMemory[1] = 11;
	mMemory[2] = 11;
	Delay(10000);
	mMemory[0] = 10;
	mMemory[1] = 11;
	mMemory[2] = 11;
	Delay(10000);
	mMemory[0] = 11;
	mMemory[1] = 10;
	mMemory[2] = 11;
	Delay(10000);
	mMemory[0] = 11;
	mMemory[1] = 11;
	mMemory[2] = 10;
	Delay(10000);
}

void C7SegmentReset()
{
	mMemory[0] = dig_minus;
	mMemory[1] = dig_minus;
	mMemory[2] = dig_minus;
}
