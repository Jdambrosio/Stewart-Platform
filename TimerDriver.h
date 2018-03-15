/*
 * TimerDriver.h
 *
 * Created: 2/15/2018 8:11:03 AM
 *  Author: John
 */ 


#ifndef TIMERDRIVER_H_
#define TIMERDRIVER_H_

#include <stdlib.h>                         // Prototype declarations for I/O functions
#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/wdt.h>                        // Watchdog timer header
#include <avr/interrupt.h>
#include <string.h>
#include <util/delay.h>

class TimerDriver
{
		protected:
		
		PORT_t* pport;
		TC0_t* ptimer0;
		TC1_t* ptimer1;
		uint8_t type;

		
		public:
		
		TimerDriver(PORT_t* pport, TC0_t* ptimer0, uint8_t type);
		TimerDriver(PORT_t* pport, TC1_t* ptimer0);
	
	
	
	};

#endif /* TIMERDRIVER_H_ */