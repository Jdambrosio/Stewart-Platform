/*
 * task_Servos.cpp
 *
 * Created: 3/1/2018 8:49:24 AM
 *  Author: John
 */ 
#include "task_Servos.h"


/** This constant sets how many RTOS ticks the task delays if the user's not talking.
 *  The duration is calculated to be about 5 ms.
 */
const portTickType ticks_to_delay = ((configTICK_RATE_HZ / 1000) * 5);


//-------------------------------------------------------------------------------------
/** This constructor creates a new data acquisition task. Its main job is to call the
 *  parent class's constructor which does most of the work.
 *  @param a_name A character string which will be the name of this task
 *  @param a_priority The priority at which this task will initially run (default: 0)
 *  @param a_stack_size The size of this task's stack in bytes 
 *                      (default: configMINIMAL_STACK_SIZE)
 *  @param p_ser_dev Pointer to a serial device (port, radio, SD card, etc.) which can
 *                   be used by this task to communicate (default: NULL)
 */

task_Servos::task_Servos (const char* a_name, 
					  unsigned portBASE_TYPE a_priority, 
					  size_t a_stack_size,
					  emstream* p_ser_dev, ServoDriver* pservo_driver)
	: frt_task (a_name, a_priority, a_stack_size, p_ser_dev)
{
	p_servo_driver = pservo_driver;
}


//-------------------------------------------------------------------------------------
/** This task interacts with the user for force him/her to do what he/she is told. It
 *  is just following the modern government model of "This is the land of the free...
 *  free to do exactly what you're told." 
 */

void task_Servos::run (void)
{
	//char char_in;                           // Character read from serial device
	//time_stamp a_time;                      // Holds the time so it can be displayed
	//ESCDriver esc_driver = ESCDriver();
	portTickType previousTicks;
	delay_ms(3000);

	
	


	// This is an infinite loop; it runs until the power is turned off. There is one 
	// such loop inside the code for each task
	for (;;)
	{
		// Run the finite state machine. The variable 'state' is kept by the parent class
		switch (state)
		{
			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			// In state 0, the servos reset and wait for initialization
			case (0):
			//*p_serial << PMS ("case 0 entered") << endl;
			
			previousTicks = xTaskGetTickCount();
			delay_from_to(previousTicks, 2000);
			
			if(servo_reset.get()) //If reset flag is triggered, transition to 1, triggered in case z of user task
			{
							
				//previousTicks = xTaskGetTickCount();
				//delay_from_to(previousTicks, 1000);

				transition_to (1);
			}
			
			else if (servo_start.get() && reset_complete.get()) //If run-start flag is triggered, transition to 2, triggered after reset and 
			{
			
				transition_to (2);
			}
				
			break; // End of state 0

			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			
			// In state 1, the servos are resetting
			case (1):
			
			previousTicks = xTaskGetTickCount();
			delay_from_to(previousTicks, 2000);
						
			*p_serial << PMS ("case 1 entered") << endl;
			//p_servo_driver->ServoOperate(40,80,40,80,40,80);
			p_servo_driver->ServoOperate(60,60,60,60,60,60);
			//servo1 aka cca isnt loading
			_delay_ms(1000);
			//p_servo_driver->ServoReset();
			servo_reset.put(false);
			reset_complete.put(true);						
			transition_to(0);
			
			break; // End of state 1
			
			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			
			// In state 2, the servos are running
			case(2):
			
			previousTicks = xTaskGetTickCount();
			delay_from_to(previousTicks, 200);
						
			*p_serial << PMS ("case 2 entered") << endl;
			//*p_serial << PMS ("Servo Value") << Servo1_queue.get() << endl << endl;
			
			p_servo_driver->ServoOperate(Servo1_queue.get(),Servo2_queue.get(), Servo3_queue.get(), Servo4_queue.get(), Servo5_queue.get(),Servo6_queue.get());
			//*p_serial << PMS (", TCC0CCA=") << TCC0.CCA << endl << endl;
			//_delay_ms(500);
			//p_serial << servo_stop.get() << endl;
			if (servo_stop.get())
			{			
				servo_start.put(false);
				reset_complete.put(false);
				transition_to(3);
			}
			
			break;

			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			
			// In state 3, the servos are running
			case(3):
			*p_serial << PMS ("case 3 entered") << endl;
			
			previousTicks = xTaskGetTickCount();
			delay_from_to(previousTicks, 2000);			
			
			if (servo_resume.get())
			{
				servo_stop.put(false);
				transition_to(2);
			}
			else if (servo_reset.get())
			{
				servo_stop.put(false);
				transition_to(1);
			}

			break;
					
					
			
		}

		runs++;                             // Increment counter for debugging

		// No matter the state, wait for approximately a millisecond before we 
		// run the loop again. This gives lower priority tasks a chance to run
		vTaskDelay (configMS_TO_TICKS (1));
	}
}