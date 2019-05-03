/*
 * ServoDriver.cpp
 *
 * Created: 2/13/2018 10:47:13 AM
 *  Author: John
 */ 

#include "ServoDriver.h"

ServoDriver::ServoDriver(TC0_t* p_timer_0, TC1_t* p_timer_1)
{
	p_timer0 = p_timer_0;
	p_timer1 = p_timer_1;
}

uint16_t ServoDriver::PWMConvert(uint8_t data)
{
	uint16_t x;
	x = (data * 40) + 3520;
	return x;
}

void ServoDriver::ServoOperate(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4, uint8_t data5, uint8_t data6)
{
	p_timer0->CCA = PWMConvert(data1);

	p_timer0->CCB = PWMConvert(data2);

	p_timer0->CCC = PWMConvert(data3);

	p_timer0->CCD = PWMConvert(data4);

	p_timer1->CCA = PWMConvert(data5);

	p_timer1->CCB = PWMConvert(data6);
}


void ServoDriver::ServoReset(void)
{
	p_timer0->CCA = 5920;
	_delay_ms(500);
	p_timer0->CCB = 5920;
	_delay_ms(500);
	p_timer0->CCC = 5920;
	_delay_ms(500);
	p_timer0->CCD = 5920;
	_delay_ms(500);
	p_timer1->CCA = 5920;
	_delay_ms(500);
	p_timer1->CCB = 5920;
	_delay_ms(500);
}