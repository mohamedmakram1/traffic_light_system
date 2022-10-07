/**************************
   Timer Library .h File
**************************/

#ifndef TIMERLIB_H
#define TIMERLIB_H

/** Imports **/
#include "imports.h" // coomon imports
#include "driverlib/timer.h" // TIVAWARE timer API

/** Macros **/
#define TIMER0 0
#define TIMER1 1
#define FREQUENCY 16E+6

/** Functions **/
void init_timer(uint32_t timer);
  /** Initiate timer
    Desc.:
      Initiates and configures a timer

    Goal:
      1. gate clock to timer
      2. wait for clock to reach timer
      3. configure timer as full-width(32), one-Shot, down-counting timer
      4. stalls timer during debugging

    Parameters:
      1. unsiged 4-byte integer timer:
        - values: TIMER0, TIMER1;

    Returns:
      - void
  **/


void begin_delay(uint32_t seconds, uint32_t timer);
  /** Load and start timer
    Desc.:
      Loads the timer load register and enables (starts) the timer

    Goal:
      1. calculate ticks froms seconds
      2. load the timer with calcualted ticks
      3. start timer

    Parameters:
      1. unsiged 4-byte integer seconds:
        - the delay in seconds
      
      2. unsiged 4-byte integer timer:
        - values: TIMER0, TIMER1     

    Returns:
      - void
  **/


void assign_isr(void (*isr)(void), uint32_t timer);
  /** Assign handler to timer interrupt
    Desc.:
      Enables timer interrupts and assigns an interrupt handler

    Goal:
      1. assign interrupt handler
      2. enable timer-out interrupts

    Parameters:
      1. function pointer isr:
        - a pointer to the function.
      
      2. unsiged 4-byte integer timer:
        - values: TIMER0, TIMER1;        

    Returns:
      - void
  **/
  
  
void pause_timer(uint8_t timer);
  /** Stop timer
    Desc.:
    Stops timer at the current value without chaning its current value.
    
    Goal:
      1. disable timer

    Parameters:
      1. unsiged 4-byte integer timer:
        - values: TIMER0, TIMER1;        

    Returns:
      - void
  **/
  
void resume_timer(uint32_t timer);
  /** Continue timer
    Desc.:
    Resumes timer from its current value without chaning its current value
    
    Goal:
      1. enable timer

    Parameters:
      1. unsiged 4-byte integer timer:
        - values: TIMER0, TIMER1;        

    Returns:
      - void
  **/

/** END OF FILE **/
#endif