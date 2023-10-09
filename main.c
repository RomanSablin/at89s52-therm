#include "C7Segment3.h"

void delay(uint16_t _delay)
{
	int i;
	for(i=0; i<_delay; i++)
	{
		i++;
		--i;
	}
}

void main()
{
	C7Segment3Init();
//	C7SegmentSet(123, 0);
//	C7Segment3SetDigit(1);

	while(1)
	{
	  P2 = 0xBB; // 1
  	P1 = (1<<simDIG2);
		delay(10000);
/*
	  P2 = 0x8d; // 2
  	P1 = (1<<simDIG2);
		delay(10000);

	  P2 = 0xd5; // 3
  	P1 = (1<<simDIG3);
		delay(10000);
*/
		//		C7Segment3Show();
	}
}