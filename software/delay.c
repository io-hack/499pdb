#include "include.h"

void delay_ms(unsigned int times)
{
	unsigned int count;
 	while(times--)
	{
		count = 0x106;
		while(count--);
	}
}


void delay_10us(unsigned int times)
{
 	while(times--);
}
