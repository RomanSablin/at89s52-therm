#include "C7Segment3.h"

void main()
{
	C7Segment3Init();
	C7SegmentSet(123, 0);
//	C7Segment3SetDigit(1);

	while(1)
	{
		C7Segment3Show();
		Delay(1000);
	}
}