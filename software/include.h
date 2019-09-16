#ifndef INCLUDE_H
#define INCLUDE_H

#include <reg51.h>
#include <stdio.h>
#include "reg51.h"
#include "intrins.h"

#define H (1)
#define L (0)

sbit TVP_PDN = P1^6;
sbit TVP_RESETB = P1^5;
sbit FLCOS_nRST = P1^2;
sbit FLCOS_SEN = P1^1;
sbit FLCOS_SCLK = P1^0;
sbit FLCOS_SDAT = P3^7;
sbit TVP_SDA = P3^3;
sbit TVP_SCL = P3^4;
sbit BL_U = P3^1;
sbit BL_D = P3^0;

#define SDA TVP_SDA
#define SCL TVP_SCL

//#define DEBUG

void uart_init(void);
unsigned long fosc_get(void);
void delay_ms(unsigned int times);
void delay_10us(unsigned int times);
unsigned char iic_write_check(unsigned char addr, unsigned char reg, unsigned char val);
unsigned char iic_read_byte(unsigned char addr, unsigned char reg);
void iic_write_byte(unsigned char addr, unsigned char reg, unsigned char val);

#endif
