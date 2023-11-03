#ifndef __C7SEGMENT3_H__
#define __C7SEGMENT3_H__

#include <stdint.h>

#include "Timer.h"

// PORT 2
#define	simA  0
#define	simB  2
#define simC  6
#define simD  4
#define simE  3
#define simF  1
#define simG  7
	
#define simDP 5

// PORT 1
#define simDIG1 4
#define simDIG2 3
#define simDIG3 2

enum
{
	mA = (1<<simA),
	mB = (1<<simB),
	mC = (1<<simC),
	mD = (1<<simD),
	mE = (1<<simE),
	mF = (1<<simF),
	mG = (1<<simG)
};

enum
{
	dig_0 = ~(mA|mB|mC|mD|mE|mF),//  ; 0
	dig_1 = ~(mB|mC),// ; 1
	dig_2 = ~(mA|mB|mD|mE|mG),// ; 2
	dig_3 = ~(mA|mB|mC|mD|mG),// ; 3
	dig_4 = ~(mB|mC|mF|mG),// ; 4
	dig_5 = ~(mA|mC|mD|mF|mG),// ; 5
	dig_6 = ~(mA|mC|mD|mE|mF|mG),// ; 6
	dig_7 = ~(mA|mB|mC),// ; 7
	dig_8 = ~(mA|mB|mC|mD|mE|mF|mG),// ; 8
	dig_9 = ~(mA|mB|mC|mD|mF|mG), // ; 9
	dig_minus = ~mG,// ; -
	dig_off = 0xff
};

void C7Segment3Init();
void C7Segment3SetDigit(uint8_t _dig);
void C7Segment3Show();
void C7SegmentSet(uint8_t _val, uint8_t _sign);
void SetSegmentWait();

#endif //__C7SEGMENT3_H__
