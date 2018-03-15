//**************************************************************************************
/** \file task_user.cpp
 *    This file contains source code for a user interface task for a ME405/FreeRTOS
 *    test suite. 
 *
 *  Revisions:
 *    \li 09-30-2012 JRR Original file was a one-file demonstration with two tasks
 *    \li 10-05-2012 JRR Split into multiple files, one for each task
 *    \li 10-25-2012 JRR Changed to a more fully C++ version with class task_user
 *    \li 11-04-2012 JRR Modified from the data acquisition example to the test suite
 *
 *  License:
 *    This file is copyright 2012 by JR Ridgely and released under the Lesser GNU 
 *    Public License, version 2. It intended for educational use only, but its use
 *    is not limited thereto. */
/*    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 *    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 *    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 *    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
 *    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUEN-
 *    TIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS 
 *    OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
 *    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
 *    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */
//**************************************************************************************

#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/wdt.h>                        // Watchdog timer header

#include "shared_data_sender.h"
#include "shared_data_receiver.h"
#include "task_user.h"                      // Header for this file


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

task_user::task_user (const char* a_name, 
					  unsigned portBASE_TYPE a_priority, 
					  size_t a_stack_size,
					  emstream* p_ser_dev
					 )
	: frt_task (a_name, a_priority, a_stack_size, p_ser_dev)
{
	// Nothing is done in the body of this constructor. All the work is done in the
	// call to the frt_task constructor on the line just above this one
}


//-------------------------------------------------------------------------------------
/** This task interacts with the user for force him/her to do what he/she is told. It
 *  is just following the modern government model of "This is the land of the free...
 *  free to do exactly what you're told." 
 */

void task_user::run (void)
{
	char char_in;                           // Character read from serial device
	time_stamp a_time;                      // Holds the time so it can be displayed
	uint8_t s1buf[4];						// Small buffers to combine numbers from data transfer
	uint8_t s2buf[4];	
	uint8_t s3buf[4];
	uint8_t s4buf[4];
	uint8_t s5buf[4];		
	uint8_t s6buf[4];
	uint8_t s1n;							// Keeps track of how many numbers need to be combined
	uint8_t s2n;
	uint8_t s3n;
	uint8_t s4n;			
	uint8_t s5n;
	uint8_t s6n;
	uint8_t s1val;							// Value of data after conversion, put into the queue
	uint8_t s2val;				
	uint8_t s3val;
	uint8_t s4val;		
	uint8_t s5val;		
	uint8_t s6val;
	uint8_t s2displaybuffer[31];
	uint8_t n;		
	
			
	// Tell the user how to get into command mode (state 1), where the user interface
	// task does interesting things such as diagnostic printouts
	*p_serial << PMS ("Press Ctrl-A for command mode") << endl;

	// This is an infinite loop; it runs until the power is turned off. There is one 
	// such loop inside the code for each task
	for (;;)
	{
		// Run the finite state machine. The variable 'state' is kept by the parent class
		switch (state)
		{
			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			// In state 0, we transparently relay characters from the radio to the USB 
			// serial port and vice versa but watch for certain control characters
			case (0):
				if (p_serial->check_for_char ())        // If the user typed a
				{                                       // character, read
					char_in = p_serial->getchar ();     // the character

					// In this switch statement, we respond to different characters
					switch (char_in)
					{
						// Control-C means reset the AVR computer
						case ('x'):
							*p_serial << PMS ("Resetting AVR") << endl;
							wdt_enable (WDTO_120MS);
							for (;;);
							break;

						// Control-A puts this task in command mode
						case ('a'):
							print_help_message ();
							transition_to (1);
							break;

						// Any other character will be ignored
						default:
							break;
					};
				}

				// Check the print queue to see if another task has sent this task 
				// something to be printed
				else if (print_ser_queue.check_for_char ())
				{
					p_serial->putchar (print_ser_queue.getchar ());
				}

				break; // End of state 0

			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			// In state 1, we're in command mode, so when the user types characters, the
			// characters are interpreted as commands to do something
			case (1):
				
				if (p_serial->check_for_char ())			// If the user typed a
				{											// character, read
					char_in = p_serial->getchar ();	
					*p_serial << PMS ("Command Mode") << endl;		// the character

					// In this switch statement, we respond to different characters as
					// commands typed in by the user
					switch (char_in)
					{
						
						 //Diagnostic
						//case('d'):
							//*p_serial << task_Servos.get_state() << endl;
							//break;
						
						// The 'x' command begins data transfer
						case ('x'):
							transition_to(2);
							break;

						// The 's' stops the current run 
						case ('s'):
							//raise a flag to stop the run
							if (!(servo_stop.get()))
							{
								transition_to(10);
							}
							break;

						// The escape key or 'e' key go back to non-command mode
						case (27):
						case ('e'):
							*p_serial << PMS ("Exit command mode") << endl;
							//transition_to (0);
							break;
						
						// The 'g' key begins a run from the beginning
						//raise a flag to start a run
						case('g'):
							if (!(servo_start.get()))
							{
								transition_to(11);
							}
							break;
							
						// The 'r' key begins a run from the stopped position
						case('r'):
							//raise a flag to resume a run
							if (!(servo_resume.get()))
							{
								transition_to(12);
							}
							break;							

						// The 'z' key sets the position to the zero position
						//raise a flag to start the zero process
						case('z'):
							if (!(servo_reset.get()))
							{
								transition_to(13);
							}
							break;


						// If the character isn't recognized, ask: What's That Function?
						default:
							p_serial->putchar (char_in);
							*p_serial << PMS (":WTF?") << endl;
							break;
					}; // End switch for characters
				} // End if a character was received

				// In this state, characters from the radio are ignored; hopefully we'll
				// get out of this state before the radio buffer overflows and characters
				// are missed
				
				break; // End of state 1
			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			// In state 2, we're in data transfer mode, the user can wait for data transfer
			// to complete, or stop mid transfer and return to state 0
			case (2):
				if (p_serial->check_for_char ())			// If the user typed a
				{											// character, read
					char_in = p_serial->getchar ();			// the character

					// In this switch statement, we respond to different characters as
					// commands typed in by the user
					switch (char_in)
					{
						
						// The '1' command transitions to Servo1 State
						case ('1'):
						s1n = 0;						
						transition_to(3);
						break;
						
						// The '2' command transitions to Servo2 State
						case ('2'):
						s2n = 0;
						transition_to(4);
						break;	

						// The '3' command transitions to Servo3 State
						case ('3'):
						s3n = 0;
						transition_to(5);
						break;	
											
						// The '4' command transitions to Servo4 State
						case ('4'):
						s4n = 0;
						transition_to(6);
						break;
						
						// The '5' command transitions to Servo5 State
						case ('5'):
						s5n = 0;
						transition_to(7);
						break;						
						
						// The '6' command transitions to Servo6 State
						case ('6'):
						s6n = 0;
						transition_to(8);
						break;	
						
						// The 'e' command transitions back to command mode
						case ('e'):
						transition_to(1);
						break;						
					}
				}
				break;
			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			// In state 3, we're in servo1 data send mode
			// 
			case (3):
			if (p_serial->check_for_char ())			// If the user typed a
			{											// character, read
				char_in = p_serial->getchar ();			// the character

				// In this switch statement, we respond to different characters as
				// commands typed in by the user
				switch (char_in)
				{
					
					// The ',' indicates that one complete number has been read and needs to be converted
					case (','):
					s1val = conversion(s1buf, s1n);
					Servo1_queue.put(s1val);
					s1n = 0;
					break;

					/* The '0' indicates that an integer 0 must be added to the buffer*/
					case ('0'):
					s1buf[s1n] = 0;
					s1n++;
					break;


					// The '1' indicates that an integer 1 must be added to the buffer
					case ('1'):
					s1buf[s1n] = 1;
					s1n++;
					break;
					
					// The '2' indicates that an integer 2 must be added to the buffer
					case ('2'):
					s1buf[s1n] = 2;
					s1n++;
					break;									

					// The '3' indicates that an integer 3 must be added to the buffer
					case ('3'):
					s1buf[s1n] = 3;
					s1n++;
					break;						

					// The '4' indicates that an integer 4 must be added to the buffer
					case ('4'):
					s1buf[s1n] = 4;
					s1n++;
					break;

					// The '5' indicates that an integer 5 must be added to the buffer
					case ('5'):
					s1buf[s1n] = 5;
					s1n++;
					break;
						
					// The '6' indicates that an integer 6 must be added to the buffer
					case ('6'):
					s1buf[s1n] = 6;
					s1n++;
					break;
					
					// The '7' indicates that an integer 7 must be added to the buffer
					case ('7'):
					s1buf[s1n] = 7;
					s1n++;
					break;			
							
					// The '8' indicates that an integer 8 must be added to the buffer
					case ('8'):
					s1buf[s1n] = 8;
					s1n++;
					break;


					// The '9' indicates that a numerical 9 must be added to the buffer
					case ('9'):
					s1buf[s1n] = 9;
					s1n++;
					break;

					// The 'e' command begins data transfer
					case ('e'):
					*p_serial << PMS ("Servo 1 Transfer Complete") << endl;
					n = 0;
					transition_to(9);
					break;
				}
			}
			break;


			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			// In state 4, we're in servo2 data send mode
			//
			case (4):
			if (p_serial->check_for_char ())			// If the user typed a
			{											// character, read
				char_in = p_serial->getchar ();			// the character
				//*p_serial << char_in << endl;

				// In this switch statement, we respond to different characters as
				// commands typed in by the user
				switch (char_in)
				{
					
					// The ',' indicates that one complete number has been read and needs to be converted
					case (','):
					s2val = conversion(s2buf, s2n);
					Servo2_queue.put(s2val);
					s2n = 0;
					break;

					// The '0' indicates that an integer 0 must be added to the buffer
					case ('0'):
					s2buf[s2n] = 0;
					s2n++;
					break;


					// The '1' indicates that an integer 1 must be added to the buffer
					case ('1'):
					s2buf[s2n] = 1;
					s2n++;
					break;
					
					// The '2' indicates that an integer 2 must be added to the buffer
					case ('2'):
					s2buf[s2n] = 2;
					s2n++;
					break;

					// The '3' indicates that an integer 3 must be added to the buffer
					case ('3'):
					s2buf[s2n] = 3;
					s2n++;
					break;

					// The '4' indicates that an integer 4 must be added to the buffer
					case ('4'):
					s2buf[s2n] = 4;
					s2n++;
					break;

					// The '5' indicates that an integer 5 must be added to the buffer
					case ('5'):
					s2buf[s2n] = 5;
					s2n++;
					break;
					
					// The '6' indicates that an integer 6 must be added to the buffer
					case ('6'):
					s2buf[s2n] = 6;
					s2n++;
					break;
					
					// The '7' indicates that an integer 7 must be added to the buffer
					case ('7'):
					s2buf[s2n] = 7;
					s2n++;
					break;
					
					// The '8' indicates that an integer 8 must be added to the buffer
					case ('8'):
					s2buf[s2n] = 8;
					s2n++;
					break;


					// The '9' indicates that a numerical 9 must be added to the buffer
					case ('9'):
					s2buf[s2n] = 9;
					s2n++;
					break;
					
					// The 'e' command begins data transfer
					case ('e'):
					*p_serial << PMS ("Servo 2 Transfer Complete") << endl;
					n = 0;
					transition_to(9);
					break;					
				}
			} break;

			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			// In state 5, we're in servo3 data send mode
			//
			case (5):
			if (p_serial->check_for_char ())			// If the user typed a
			{											// character, read
				char_in = p_serial->getchar ();			// the character

				// In this switch statement, we respond to different characters as
				// commands typed in by the user
				switch (char_in)
				{
					
					// The ',' indicates that one complete number has been read and needs to be converted
					case (','):
					s3val = conversion(s3buf, s3n);
					Servo3_queue.put(s3val);
					s3n = 0;
					break;

					// The '0' indicates that an integer 0 must be added to the buffer
					case ('0'):
					s3buf[s3n] = 0;
					s3n++;
					break;

					// The '1' indicates that an integer 1 must be added to the buffer
					case ('1'):
					s3buf[s3n] = 1;
					s3n++;
					break;
					
					// The '2' indicates that an integer 2 must be added to the buffer
					case ('2'):
					s3buf[s3n] = 2;
					s3n++;
					break;

					// The '3' indicates that an integer 3 must be added to the buffer
					case ('3'):
					s3buf[s3n] = 3;
					s3n++;
					break;

					// The '4' indicates that an integer 4 must be added to the buffer
					case ('4'):
					s3buf[s3n] = 4;
					s3n++;
					break;

					// The '5' indicates that an integer 5 must be added to the buffer
					case ('5'):
					s3buf[s3n] = 5;
					s3n++;
					break;
					
					// The '6' indicates that an integer 6 must be added to the buffer
					case ('6'):
					s3buf[s3n] = 6;
					s3n++;
					break;
					
					// The '7' indicates that an integer 7 must be added to the buffer
					case ('7'):
					s3buf[s3n] = 7;
					s3n++;
					break;
					
					// The '8' indicates that an integer 8 must be added to the buffer
					case ('8'):
					s3buf[s3n] = 8;
					s3n++;
					break;

					// The '9' indicates that a numerical 9 must be added to the buffer
					case ('9'):
					s3buf[s3n] = 9;
					s3n++;
					break;

					// The 'e' command begins data transfer
					case ('e'):
					*p_serial << PMS ("Servo 3 Transfer Complete") << endl;
					n = 0;
					transition_to(9);
					break;					
				}
			} break;


			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			// In state 6, we're in servo4 data send mode
			//
			case (6):
			if (p_serial->check_for_char ())			// If the user typed a
			{											// character, read
				char_in = p_serial->getchar ();			// the character

				// In this switch statement, we respond to different characters as
				// commands typed in by the user
				switch (char_in)
				{
					
					// The ',' indicates that one complete number has been read and needs to be converted
					case (','):
					s4val = conversion(s4buf, s4n);
					Servo4_queue.put(s4val);
					s4n = 0;
					break;

					// The '0' indicates that an integer 0 must be added to the buffer
					case ('0'):
					s4buf[s4n] = 0;
					s4n++;
					break;

					// The '1' indicates that an integer 1 must be added to the buffer
					case ('1'):
					s4buf[s4n] = 1;
					s4n++;
					break;
					
					// The '2' indicates that an integer 2 must be added to the buffer
					case ('2'):
					s4buf[s4n] = 2;
					s4n++;
					break;

					// The '3' indicates that an integer 3 must be added to the buffer
					case ('3'):
					s4buf[s4n] = 3;
					s4n++;
					break;

					// The '4' indicates that an integer 4 must be added to the buffer
					case ('4'):
					s4buf[s4n] = 4;
					s4n++;
					break;

					// The '5' indicates that an integer 5 must be added to the buffer
					case ('5'):
					s4buf[s4n] = 5;
					s4n++;
					break;
					
					// The '6' indicates that an integer 6 must be added to the buffer
					case ('6'):
					s4buf[s4n] = 6;
					s4n++;
					break;
					
					// The '7' indicates that an integer 7 must be added to the buffer
					case ('7'):
					s4buf[s4n] = 7;
					s4n++;
					break;
					
					// The '8' indicates that an integer 8 must be added to the buffer
					case ('8'):
					s4buf[s4n] = 8;
					s4n++;
					break;


					// The '9' indicates that a numerical 9 must be added to the buffer
					case ('9'):
					s4buf[s4n] = 9;
					s4n++;
					break;

					// The 'e' command begins data transfer
					case ('e'):
					*p_serial << PMS ("Servo 4 Transfer Complete") << endl;
					n = 0;
					transition_to(9);
					break;					
				}
			} break;


			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			// In state 7, we're in servo5 data send mode
			//
			case (7):
			if (p_serial->check_for_char ())			// If the user typed a
			{											// character, read
				char_in = p_serial->getchar ();			// the character

				// In this switch statement, we respond to different characters as
				// commands typed in by the user
				switch (char_in)
				{
					
					// The ',' indicates that one complete number has been read and needs to be converted
					case (','):
					s5val = conversion(s5buf, s5n);
					Servo5_queue.put(s5val);
					s5n = 0;
					break;

					// The '0' indicates that an integer 0 must be added to the buffer
					case ('0'):
					s5buf[s5n] = 0;
					s5n++;
					break;

					// The '1' indicates that an integer 1 must be added to the buffer
					case ('1'):
					s5buf[s5n] = 1;
					s5n++;
					break;
					
					// The '2' indicates that an integer 2 must be added to the buffer
					case ('2'):
					s5buf[s5n] = 2;
					s5n++;
					break;

					// The '3' indicates that an integer 3 must be added to the buffer
					case ('3'):
					s5buf[s5n] = 3;
					s5n++;
					break;

					// The '4' indicates that an integer 4 must be added to the buffer
					case ('4'):
					s5buf[s5n] = 4;
					s5n++;
					break;

					// The '5' indicates that an integer 5 must be added to the buffer
					case ('5'):
					s5buf[s5n] = 5;
					s5n++;
					break;
					
					// The '6' indicates that an integer 6 must be added to the buffer
					case ('6'):
					s5buf[s5n] = 6;
					s5n++;
					break;
					
					// The '7' indicates that an integer 7 must be added to the buffer
					case ('7'):
					s5buf[s5n] = 7;
					s5n++;
					break;
					
					// The '8' indicates that an integer 8 must be added to the buffer
					case ('8'):
					s5buf[s5n] = 8;
					s5n++;
					break;


					// The '9' indicates that a numerical 9 must be added to the buffer
					case ('9'):
					s5buf[s5n] = 9;
					s5n++;
					break;

					// The 'e' command begins data transfer
					case ('e'):
					*p_serial << PMS ("Servo 5 Transfer Complete") << endl;
					n = 0;
					transition_to(9);
					break;					
				}
			} break;


			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			// In state 8, we're in servo6 data send mode
			//
			case (8):
			if (p_serial->check_for_char ())			// If the user typed a
			{											// character, read
				char_in = p_serial->getchar ();			// the character

				// In this switch statement, we respond to different characters as
				// commands typed in by the user
				switch (char_in)
				{
					
					// The ',' indicates that one complete number has been read and needs to be converted
					case (','):
					s6val = conversion(s6buf, s6n);
					Servo6_queue.put(s6val);
					s6n = 0;
					break;

					// The '0' indicates that an integer 0 must be added to the buffer
					case ('0'):
					s6buf[s6n] = 0;
					s6n++;
					break;

					// The '1' indicates that an integer 1 must be added to the buffer
					case ('1'):
					s6buf[s6n] = 1;
					s6n++;
					break;
					
					// The '2' indicates that an integer 2 must be added to the buffer
					case ('2'):
					s6buf[s6n] = 2;
					s6n++;
					break;

					// The '3' indicates that an integer 3 must be added to the buffer
					case ('3'):
					s6buf[s6n] = 3;
					s6n++;
					break;

					// The '4' indicates that an integer 4 must be added to the buffer
					case ('4'):
					s6buf[s6n] = 4;
					s6n++;
					break;

					// The '5' indicates that an integer 5 must be added to the buffer
					case ('5'):
					s6buf[s6n] = 5;
					s6n++;
					break;
					
					// The '6' indicates that an integer 6 must be added to the buffer
					case ('6'):
					s6buf[s6n] = 6;
					s6n++;
					break;
					
					// The '7' indicates that an integer 7 must be added to the buffer
					case ('7'):
					s6buf[s6n] = 7;
					s6n++;
					break;
					
					// The '8' indicates that an integer 8 must be added to the buffer
					case ('8'):
					s6buf[s6n] = 8;
					s6n++;
					break;


					// The '9' indicates that a numerical 9 must be added to the buffer
					case ('9'):
					s6buf[s6n] = 9;
					s6n++;
					break;

					// The 'e' command begins data transfer
					case ('e'):
					*p_serial << PMS ("Servo 6 Transfer Complete") << endl;
					n = 0;
					transition_to(9);
					break;					
				}
			} break;


					
			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			// In state 9 we want to display an array of the servo1queue
			//
			case (9):
			
			transition_to(2);

			/*if (n < 20)
			{
				s1displaybuffer[n] = Servo1_queue.get();
				*p_serial << s1displaybuffer[n] << endl;
				n++;
			}
			else
			{			
				transition_to(2);
			}*/
			break;
			
			
			
			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			// In state 10 we will be stopping the servos
			//
			case (10):
			*p_serial << PMS ("Case 10 entered") << endl;
			servo_stop.put(true);
			*p_serial << servo_stop.get() << endl;
			transition_to(1);
			break;
			
			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			// In state 11 we will be running the servos
			//
			case (11):
			*p_serial << PMS ("Case 11 entered") << endl;
			servo_start.put(true);
			transition_to(1);
			break;
			
			
			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			// In state 12 we will resume running the servos
			//
			case (12):
			servo_resume.put(true);
			transition_to(1);
			break;			

			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			// In state 13 we will reset the servos
			//
			case (13):
			servo_reset.put(true);
			transition_to(1);
			break;

			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			// In state 9 we want to display an array of the servo1queue
			//
			case (14):

			if (n < 31)
			{
				s2displaybuffer[n] = Servo2_queue.get();
				*p_serial << s2displaybuffer[n] << endl;
				n++;
			}
			else
			{			
				transition_to(2);
			}
			break;


											
			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			// We should never get to the default state. If we do, complain and restart
			default:
				*p_serial << PMS ("Illegal state! Resetting AVR") << endl;
				wdt_enable (WDTO_120MS);
				for (;;);
				break;

		} // End switch state

		runs++;                             // Increment counter for debugging

		// No matter the state, wait for approximately a millisecond before we 
		// run the loop again. This gives lower priority tasks a chance to run
		vTaskDelay (configMS_TO_TICKS (1));
	}
}
				


//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
/** This method prints a simple help message.
 */

void task_user::print_help_message (void)
{
	*p_serial << ATERM_BKG_CYAN << ATERM_TXT_BLACK << clrscr;
	*p_serial << PROGRAM_VERSION << PMS (" help") << endl;
	*p_serial << PMS ("  Ctl-C: Reset the AVR") << endl;
	*p_serial << PMS ("  Ctl-A: Enter command mode") << endl;
	*p_serial << PMS ("  In command mode only:") << endl;
	*p_serial << PMS ("    n:   Show the time right now") << endl;
	*p_serial << PMS ("    v:   Version and setup information") << endl;
	*p_serial << PMS ("    s:   Stack dump for tasks") << endl;
	*p_serial << PMS ("    e:   Exit command mode") << endl;
	*p_serial << PMS ("    h:   HALP!") << endl;
}


//-------------------------------------------------------------------------------------
/** This method displays information about the status of the system, including the
 *  following: 
 *    \li The name and version of the program
 *    \li The name, status, priority, and free stack space of each task
 *    \li Processor cycles used by each task
 *    \li Amount of heap space free and setting of RTOS tick timer
 */

void task_user::show_status (void)
{
	time_stamp the_time;					// Holds current time for printing

	// Show program version, time, and free heap space
	*p_serial << endl << PROGRAM_VERSION << PMS (__DATE__) << endl 
			  << PMS ("Time: ") << the_time.set_to_now ()
			  << PMS (", Heap free: ") << heap_left() << PMS ("/") 
			  << configTOTAL_HEAP_SIZE;

	// Show how the timer/counter is set up to cause RTOS timer ticks
	*p_serial << PMS (", TCC0CCA=") << TCC0.CCA << endl << endl;

	// Have the tasks print their status
	print_task_list (p_serial);
}

uint8_t task_user::conversion(uint8_t* p_buffer, uint8_t count)
{
	uint8_t result;
	
	if (count == 1)
	{
		result = p_buffer[count-1];
		return result;
	}
	
	else if (count == 2)
	{
		result = (p_buffer[count-2] * 10) + p_buffer[count-1];
		return result;
	}
	
	else if (count == 3)
	{
		result = (p_buffer[count-3] * 100) + (p_buffer[count-2] * 10) + p_buffer[count-1];
		return result;
	}
}


