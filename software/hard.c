#include "include.h"

unsigned long fosc_get(void)
{
	unsigned long FOSC;
	FOSC = 0x0;
	FOSC |= *((unsigned char *)(0xF8));
	FOSC = FOSC << 8;
	FOSC |= *((unsigned char *)(0xF9));
	FOSC = FOSC << 8;
	FOSC |= *((unsigned char *)(0xFa));
	FOSC = FOSC << 8;
	FOSC |= *((unsigned char *)(0xFb));

	return FOSC;
}
