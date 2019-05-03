/*
 * Stewart Platform.cpp
 *
 * Created: 1/23/2018 8:55:26 AM
 * Author : John
 */ 


#include <stdlib.h>                         // Prototype declarations for I/O functions
#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/wdt.h>                        // Watchdog timer header
#include <avr/interrupt.h>
#include <string.h>
#include <util/delay.h>

uint8_t n;

/*void CCPWrite( volatile uint8_t * address, uint8_t value )
{
	#if defined __GNUC__
	uint8_t volatile saved_sreg = SREG;
	cli();
	volatile uint8_t * tmpAddr = address;
	#ifdef RAMPZ
	RAMPZ = 0;
	#endif
	asm volatile(
	"movw r30,  %0"	      "\n\t"
	"ldi  r16,  %2"	      "\n\t"
	"out   %3, r16"	      "\n\t"
	"st     Z,  %1"       "\n\t"
	:
	: "r" (tmpAddr), "r" (value), "M" (0xD8), "i" (&CCP)
	: "r16", "r30", "r31"
	);

	SREG = saved_sreg;
	#endif
}


int main(void)
{
	
	{	
		// Enable the 32MHz internal RC oscillator and the external 32KHz oscillator
		OSC.CTRL |= (1 << OSC_RC32MEN_bp);
		do {} while((OSC.STATUS & (1 << OSC_RC32MRDY_bp)) != (1 << OSC_RC32MRDY_bp));

		// Select the clock
		CCPWrite(&(CLK.CTRL),((CLK.CTRL & ~CLK_SCLKSEL_gm) | (1 << CLK_SCLKSEL0_bp)));
		
		// Disable the 2MHz internal RC oscillator
		OSC.CTRL &= ~(1 << OSC_RC2MEN_bp);
	}
	
	//wdt_disable();
	
	PORTC.DIRSET = PIN0_bm | PIN1_bm| PIN2_bm | PIN3_bm | PIN4_bm | PIN5_bm;
	TCC0.CTRLA = TC_CLKSEL_DIV2_gc;
	TCC0.CTRLB = TC_WGMODE_SINGLESLOPE_gc| TC0_CCAEN_bm | TC0_CCBEN_bm | TC0_CCCEN_bm | TC0_CCDEN_bm;
	TCC0.PER = 19999;
	//TCC0.CCA = 1480;
	//TCC0.CCB = 1480;
	//_delay_ms(500);
	//TCC0.CCA = 880;
	//TCC0.CCB = 880;
	//TCC0.CCA = 2080;
	
	
	TCC1.CTRLA = TC_CLKSEL_DIV2_gc;	
	TCC1.CTRLB = TC_WGMODE_SINGLESLOPE_gc| TC1_CCAEN_bm | TC1_CCBEN_bm;
	TCC1.PER = 19999;
	uint8_t servo1data[31] = {60, 50, 40, 30, 20, 10, 0, 10, 20, 30, 40, 50, 60, 50, 40, 30, 20, 10, 0, 10, 20, 30, 40, 50, 60, 50, 40, 30, 40, 50, 60};
	uint8_t servo2data[31] = {60, 70, 80, 90, 100, 110, 120, 110, 100, 90, 80, 70, 60, 70, 80, 90, 100, 110, 120, 110, 100, 90, 80, 70, 60, 70, 80, 90, 80, 70, 60};
	uint8_t servo3data[31] = {60, 50, 40, 30, 20, 10, 0, 10, 20, 30, 40, 50, 60, 50, 40, 30, 20, 10, 0, 10, 20, 30, 40, 50, 60, 50, 40, 30, 40, 50, 60};
	uint8_t servo4data[31] = {60, 70, 80, 90, 100, 110, 120, 110, 100, 90, 80, 70, 60, 70, 80, 90, 100, 110, 120, 110, 100, 90, 80, 70, 60, 70, 80, 90, 80, 70, 60};
	uint8_t servo5data[31] = {60, 50, 40, 30, 20, 10, 0, 10, 20, 30, 40, 50, 60, 50, 40, 30, 20, 10, 0, 10, 20, 30, 40, 50, 60, 50, 40, 30, 40, 50, 60};
	uint8_t servo6data[31] = {60, 70, 80, 90, 100, 110, 120, 110, 100, 90, 80, 70, 60, 70, 80, 90, 100, 110, 120, 110, 100, 90, 80, 70, 60, 70, 80, 90, 80, 70, 60};					
	
	n=0;

	//uint8_t x;
	
	USARTC0_BAUDCTRLB = 0;  //BSCALE, an additional scaling factor to adjust baud rate, initially set to 0
	USARTC0_BAUDCTRLA = 0x0C; //Set the BSEL value to 12, this gives a baud rate of 9600, a value said to be typical among USART applications
	USARTC0_CTRLC = USART_CHSIZE_8BIT_gc; //Not sure what this value is, will look more into it
	USARTC0_CTRLB = USART_RXEN_bm | USART_TXEN_bm; //Enable both receive and transmit
	USARTC0_CTRLA = 0;  //Interrupts set off
	
	
	
	
	
	
	
	
	
    while (1) 
    {
	
		if (n < 31)
		{
			TCC0.CCA = (servo1data[n] * 10) + 880;
			TCC0.CCB = (servo2data[n] * 10) + 880;
			TCC0.CCC = (servo3data[n] * 10) + 880;
			TCC0.CCD = (servo4data[n] * 10) + 880;
			TCC1.CCA = (servo5data[n] * 10) + 880;
			TCC1.CCB = (servo6data[n] * 10) + 880;
			_delay_ms(500);
			n++;			
		}
		else
		{
			n = 0;
		}
    }
	}
}*/

