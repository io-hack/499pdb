#include "include.h"

void iic_start(void)
{
	SDA = H;
	SCL = H;
	delay_10us(1);

	SDA = L;
   	delay_10us(1);
	SCL = L;
	delay_10us(1);
}

void iic_stop(void)
{
	SDA = L;
	SCL = H;
	delay_10us(1);
	SDA = H;
	delay_10us(1);
}

unsigned char iic_read_byte(unsigned char addr, unsigned char reg)
{
	int i;
	unsigned char ret;

	addr >>= 1;
	addr <<= 1;
	addr |= 0;

	iic_start();

	for(i = 7; i >= 0; i--)
	{
		if((addr>>i)&0x01 == 1)
		{
			SDA = H;
		}
		else
		{
			SDA = L;
		}
		delay_10us(1);
		SCL = L;
		delay_10us(1);
		SCL = H;
		delay_10us(1);
		SCL = L;
		SDA = H;
		delay_10us(1);
	}
	
	while(SDA);
	delay_10us(1);
	SCL = L;
	delay_10us(1);
	SCL = H;
	delay_10us(1);
	SCL = L;
	delay_10us(1);

	for(i = 7; i >= 0; i--)
	{
		if((reg>>i)&0x01 == 1)
		{
			SDA = H;
		}
		else
		{
			SDA = L;
		}
		delay_10us(1);
		SCL = L;
		delay_10us(1);
		SCL = H;
		delay_10us(1);
		SCL = L;
		SDA = H;
		delay_10us(1);
	}
	
	while(SDA);
	delay_10us(1);
	SCL = L;
	delay_10us(1);
	SCL = H;
	delay_10us(1);
	SCL = L;
	delay_10us(1);

	//-----------------------------
	addr >>= 1;
	addr <<= 1;
	addr |= 1;

	iic_start();

	for(i = 7; i >= 0; i--)
	{
		if((addr>>i)&0x01 == 1)
		{
			SDA = H;
		}
		else
		{
			SDA = L;
		}
		delay_10us(1);
		SCL = L;
		delay_10us(1);
		SCL = H;
		delay_10us(1);
		SCL = L;
		SDA = H;
		delay_10us(1);
	}
	
	while(SDA);
	delay_10us(1);
	SCL = L;
	delay_10us(1);
	SCL = H;
	delay_10us(1);
	SCL = L;
	delay_10us(100);
 	
	ret = 0;
	for(i = 7; i >= 0; i--)
	{
		delay_10us(1);
		SCL = L;
		delay_10us(1);
		SCL = H;
		delay_10us(1);
		ret <<= 1;
		if(SDA == H)
		{
			ret |= 1;
		}		
	}

	delay_10us(1);
	SCL = L;
	delay_10us(1);
	SCL = H;
	delay_10us(1);
	SCL = L;
	delay_10us(1);
	
	iic_stop();	
	
	return ret;		
}

void iic_write_byte(unsigned char addr, unsigned char reg, unsigned char val)
{
	int i;

	addr >>= 1;
	addr <<= 1;
	addr |= 0;

	iic_start();

	for(i = 7; i >= 0; i--)
	{
		if((addr>>i)&0x01 == 1)
		{
			SDA = H;
		}
		else
		{
			SDA = L;
		}
		delay_10us(1);
		SCL = L;
		delay_10us(1);
		SCL = H;
		delay_10us(1);
		SCL = L;
		SDA = H;
		delay_10us(1);
	}
	
	while(SDA);
	delay_10us(1);
	SCL = L;
	delay_10us(1);
	SCL = H;
	delay_10us(1);
	SCL = L;
	delay_10us(1);

	for(i = 7; i >= 0; i--)
	{
		if((reg>>i)&0x01 == 1)
		{
			SDA = H;
		}
		else
		{
			SDA = L;
		}
		delay_10us(1);
		SCL = L;
		delay_10us(1);
		SCL = H;
		delay_10us(1);
		SCL = L;
		SDA = H;
		delay_10us(1);
	}
	
	while(SDA);
	delay_10us(1);
	SCL = L;
	delay_10us(1);
	SCL = H;
	delay_10us(1);
	SCL = L;
	delay_10us(1);

	for(i = 7; i >= 0; i--)
	{
		if((val>>i)&0x01 == 1)
		{
			SDA = H;
		}
		else
		{
			SDA = L;
		}
		delay_10us(1);
		SCL = L;
		delay_10us(1);
		SCL = H;
		delay_10us(1);
		SCL = L;
		SDA = H;
		delay_10us(1);
	}
	
	while(SDA);
	delay_10us(1);
	SCL = L;
	delay_10us(1);
	SCL = H;
	delay_10us(1);
	SCL = L;
	delay_10us(1);
	
	iic_stop();		
}

unsigned char iic_write_check(unsigned char addr, unsigned char reg, unsigned char val)
{
	iic_write_byte(addr, reg, val);
	delay_ms(20);
	if(iic_read_byte(addr, reg) != val)
	{
#ifdef DEBUG
		printf("IIC 0x%02X 0x%02X != 0x%02X failed\r\n", (unsigned int)addr, (unsigned int)reg, (unsigned int)val);
#endif
		return 0;
	}
	else
	{
#ifdef DEBUG
		printf("IIC 0x%02X 0x%02X == 0x%02X ok\r\n", (unsigned int)addr, (unsigned int)reg, (unsigned int)val);	
#endif
	}
	return 1;
}
