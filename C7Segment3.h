/* 
* C7Segment3.h
*
* Created: 01.07.2020 17:23:37
* Author: r.sablin
*/


#ifndef __C7SEGMENT3_H__
#define __C7SEGMENT3_H__

#include <Atmel/AT89X52.H>

#define	simA  P2_0
#define	simB  P2_2
#define simC  P2_6
#define simD  P2_4
#define simE  P2_3
#define simF  P2_1
#define simG  P2_7
	
#define simDP P2_5
#define simDIG1 P1_4
#define simDIG2 P1_3
#define simDIG3 P1_2

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
	dig_0 = (mA|mB|mC|mD|mE|mF),//  ; 0
	dig_1 = (mB|mC),// ; 1
	dig_2 = (mA|mB|mD|mE|mG),// ; 2
	dig_3 = (mA|mB|mC|mD|mG),// ; 3
	dig_4 = (mB|mC|mF|mG),// ; 4
	dig_5 = (mA|mC|mD|mF|mG),// ; 5
	dig_6 = (mA|mC|mD|mE|mF|mG),// ; 6
	dig_7 = (mA|mB|mC),// ; 7
	dig_8 = (mA|mB|mC|mD|mE|mF|mG),// ; 8
	dig_9 = (mA|mB|mC|mD|mF|mG), // ; 9
	dig_minus = mG,// ; -
	dig_off = 0
};
	
void C7Segment3Init();
void C7Segment3SetDigit(uint8_t _dig);
void C7Segment3Show();
void C7SegmentSet(uint8_t _val, uint8_t _sign);
void SetSegmentWait();

#endif //__C7SEGMENT3_H__
