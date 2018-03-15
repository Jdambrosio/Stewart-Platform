/*
 * ServoDriver.h
 *
 * Created: 2/13/2018 10:14:15 AM
 *  Author: John
 */ 


#ifndef ServoDriver_H_
#define ServoDriver_H_

#include <stdlib.h>                         // Prototype declarations for I/O functions
#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/wdt.h>                        // Watchdog timer header
#include <avr/interrupt.h>
#include <string.h>
#include <util/delay.h>


class ServoDriver
{
	protected:
	
	uint8_t cycles;
	uint8_t servo_data[100];
	TC0_t* p_timer0;
	TC1_t* p_timer1;
		
	
	public:
	
	ServoDriver(TC0_t* p_timer0, TC1_t* p_timer1);
	
	uint16_t PWMConvert(uint8_t data);
	
	void ServoReset();

	void ServoOperate(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4, uint8_t data5, uint8_t data6);	
	
	

	};




#endif /* ServoDriver_H_ */