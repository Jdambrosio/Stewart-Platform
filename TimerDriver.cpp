/*
 * TimerDriver.cpp
 *
 * Created: 2/15/2018 9:46:13 AM
 *  Author: John
 */ 

#include "TimerDriver.h"

TimerDriver::TimerDriver(PORT_t* pport, TC0_t* p_timer0, uint8_t type) : type(type)
{
		pport->DIRSET = PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm;
		p_timer0->CTRLA = TC_CLKSEL_DIV8_gc;
		p_timer0->CTRLB = TC_WGMODE_SINGLESLOPE_gc| TC0_CCAEN_bm | TC0_CCBEN_bm | TC0_CCCEN_bm | TC0_CCDEN_bm;
		p_timer0->PER = 79999;		
}

TimerDriver::TimerDriver(PORT_t* pport, TC1_t* p_timer1)
{
		pport->DIRSET = PIN4_bm | PIN5_bm;
		p_timer1->CTRLA = TC_CLKSEL_DIV8_gc;
		p_timer1->CTRLB = TC_WGMODE_SINGLESLOPE_gc| TC1_CCAEN_bm | TC1_CCBEN_bm;
		p_timer1->PER = 79999;
		type = 0; 
}