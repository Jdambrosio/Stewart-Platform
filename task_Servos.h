/*
 * task_Servos.h
 *
 * Created: 3/1/2018 9:44:32 AM
 *  Author: John
 */ 


#ifndef TASK_SERVOS_H_
#define TASK_SERVOS_H_

#include <stdlib.h>                         // Prototype declarations for I/O functions

#include "FreeRTOS.h"                       // Primary header for FreeRTOS
#include "task.h"                           // Header for FreeRTOS task functions
#include "queue.h"                          // FreeRTOS inter-task communication queues

#include "rs232int.h"                       // ME405/507 library for serial comm.
#include "time_stamp.h"                     // Class to implement a microsecond timer
#include "frt_task.h"                       // Header for ME405/507 base task class
#include "frt_queue.h"                      // Header of wrapper for FreeRTOS queues
#include "frt_text_queue.h"                 // Header for a "<<" queue class
#include "frt_shared_data.h"                // Header for thread-safe shared data

#include "shares.h"                         // Global ('extern') queue declarations

#include "math.h"
#include "ServoDriver.h"

//-------------------------------------------------------------------------------------
/** This task interacts with the user for force him/her to do what he/she is told. What
 *  a rude task this is. Then again, computers tend to be that way; if they're polite
 *  with you, they're probably spying on you. 
 */


class task_Servos : public frt_task
{
private:
	// No private variables or methods for this class

protected:
	
	ServoDriver* p_servo_driver;

public:
	// This constructor creates a user interface task object
	task_Servos (const char*, unsigned portBASE_TYPE, size_t, emstream*, ServoDriver*);

	/** This method is called by the RTOS once to run the task loop for ever and ever.
	 */
	void run (void);
};





#endif /* TASK_SERVOS_H_ */