#include "include.h"

void init_sys(void);
void spi_send_byte(unsigned char addr, unsigned char val);
void flcos_send(void);
unsigned char buf;
void main(void)
{
	unsigned char val;
	uart_init();
#ifndef DEBUG
	printf("卧槽!你偷偷调试我的串口想干嘛!!!\r\n");
#endif
#ifdef DEBUG
	printf("FOSC : %luHz\r\n",fosc_get());
#endif
	init_sys();
	for(;;)
	{
		if(iic_read_byte(0xB8, 0x88) != 0x0E)
		{
			if(iic_read_byte(0xB8, 0x88) != 0x0E)
			{
#ifdef DEBUG
				printf("IIC 0xB8 0x88 != 0x0E fail\r\n");
#endif
				delay_ms(10);		
			}
			else
			{
#ifdef DEBUG
				printf("IIC 0xB8 0x88 == 0x0E ok\r\n");
#endif	
				delay_ms(10);
				flcos_send();
			}		
		}
		else
		{
#ifdef DEBUG
			printf("IIC 0xB8 0x88 == 0x0E ok\r\n");
#endif	
			delay_ms(10);
			flcos_send();
		}
		
		delay_ms(10);
		if(BL_U == L)
		{
			val = iic_read_byte(0xB8, 0x09);
			if((int)val + 3 > 255)
			{
				val = 255;
			}
			else
			{
				val += 3;
			}
			iic_write_byte(0xB8, 0x09, val);	
		}
		else
		{
			if(BL_D == L)
			{
				val = iic_read_byte(0xB8, 0x09);
				if((int)val - 3 < 0)
				{
					val = 0;
				}
				else
				{
					val -= 3;
				}
				iic_write_byte(0xB8, 0x09, val);		
			}
		}
		delay_ms(10);	
	}

}

void init_sys(void)
{

	TVP_SDA = H;
	TVP_SCL = H;
	FLCOS_SDAT = H;
	FLCOS_SCLK = H;
	FLCOS_SEN = H;
	FLCOS_nRST = H;
	TVP_RESETB = H;
	TVP_PDN = H;
	BL_U = H;
	BL_D = H;
	delay_ms(10);
	TVP_RESETB = L;
	delay_ms(10);
	TVP_RESETB = H;
	delay_ms(600);

	iic_write_check(0xB8, 0x03, 0xFD);
   	iic_write_check(0xB8, 0x04, 0x00);
	iic_write_check(0xB8, 0x0D, 0x40);
	iic_write_check(0xB8, 0x12, 0x04);
	iic_write_check(0xB8, 0x16, 0x68);
	iic_write_check(0xB8, 0x09, 0xB1);
	while(!iic_write_check(0xB8, 0x09, 0xB1));

	FLCOS_nRST = L;
	delay_ms(10);
	FLCOS_nRST = H;
	delay_ms(10);

	while(iic_read_byte(0xB8, 0x88) != 0x0E)
	{
#ifdef DEBUG
		printf("IIC while check 0xB8 0x88 == 0x0E\r\n");
#endif
	}
#ifdef DEBUG
	printf("IIC 0xB8 0x88 == 0x0E ok\r\n");
#endif
}

void spi_send_byte(unsigned char addr, unsigned char val)
{
	int index;
	FLCOS_SEN = L;
	delay_10us(2);

	for(index = 7; index>=0; index--)
	{
		if((addr>>index)&0x1 == 1)
		{
			FLCOS_SDAT = H;
		}
		else
		{
			FLCOS_SDAT = L;
		}
		delay_10us(1);
		FLCOS_SCLK = H;
		delay_10us(1);
		FLCOS_SCLK = L;
		delay_10us(1);
	}

	delay_10us(2);

	for(index = 7; index>=0; index--)
	{
		if((val>>index)&0x1 == 1)
		{
			FLCOS_SDAT = H;
		}
		else
		{
			FLCOS_SDAT = L;
		}
		delay_10us(1);
		FLCOS_SCLK = H;
		delay_10us(1);
		FLCOS_SCLK = L;
		delay_10us(1);
	}

	delay_10us(2);
   	FLCOS_SEN = H;
	delay_10us(2);
}

void flcos_send(void)
{	
	spi_send_byte(0x01, 0x35);
	spi_send_byte(0x04, 0x08);
	spi_send_byte(0x05, 0x00);
	spi_send_byte(0x07, 0x08);
	spi_send_byte(0x08, 0xEB);
	spi_send_byte(0x09, 0x10);
	spi_send_byte(0x0A, 0x16);
	spi_send_byte(0x0B, 0x05);
	spi_send_byte(0x0C, 0x16);
	spi_send_byte(0x06, 0x68);
}

