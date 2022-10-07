/**************************
   Timer Library .c File
**************************/

#include "timer_lib.h"

void init_timer(uint32_t timer){
  switch (timer){
    /** Timer 0 **/
    case(TIMER0):
      SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0); // gate clock to TIMER 0
      while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)){} // wait for clock to reach TIMER 0

      // Configuring Timer
      TimerDisable(TIMER0_BASE, TIMER_A); // disable TIMER A
      TimerControlStall(TIMER0_BASE, TIMER_A, true); // stop with debugger
      TimerConfigure(TIMER0_BASE, TIMER_CFG_ONE_SHOT); // Configure TIMER 0 as a full width ONE Shot timer
      break;

    /** Timer 1 **/
    case(TIMER1):
      SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1); // gate clock to TIMER 0
      while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER1)){} // wait for clock to reach TIMER 0

      // Configuring Timer
      TimerDisable(TIMER1_BASE, TIMER_A); // disable TIMER A
      TimerControlStall(TIMER1_BASE, TIMER_A, true); // stop with debugger
      TimerConfigure(TIMER1_BASE,TIMER_CFG_ONE_SHOT); // Configure TIMER 0 as a full width periodic timer
      break;
  }
}

void begin_delay(uint32_t seconds, uint32_t timer){
  uint32_t ticks = (seconds*FREQUENCY) - 1;
  switch(timer){
    /** Timer 0 **/
    case(TIMER0):
      TimerDisable(TIMER0_BASE, TIMER_A); // disable TIMER A
      TimerLoadSet(TIMER0_BASE, TIMER_A, ticks); // load TIMER A
      TimerEnable(TIMER0_BASE, TIMER_A); // Enable TIMER A
      break;

    /** Timer 1 **/
    case(TIMER1):
      TimerDisable(TIMER1_BASE, TIMER_A); // disable TIMER A
      TimerLoadSet(TIMER1_BASE, TIMER_A, ticks); // load TIMER A
      TimerEnable(TIMER1_BASE, TIMER_A); // Enable TIMER A
      break;
  }
}

void assign_isr(void (*isr)(void), uint32_t timer){
  switch(timer){
    /** Timer 0 **/
    case(TIMER0):
      TimerIntDisable(TIMER0_BASE, TIMER_TIMA_TIMEOUT); // disable TIMER 0 A timeput interrupts
      TimerIntRegister(TIMER0_BASE, TIMER_A, isr);
      TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT); // Enable TIMER A timout interrupts
      break;

    /** Timer 1 **/
    case(TIMER1):
      TimerIntDisable(TIMER1_BASE, TIMER_TIMA_TIMEOUT); // disable TIMER 1 A timeput interrupts
      TimerIntRegister(TIMER1_BASE, TIMER_A, isr);
      TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT); // Enable TIMER A timout interrupts
      break;
  }
}

void pause_timer(uint8_t timer){
  switch(timer){
    /** Timer 0 **/
    case(TIMER0):
      TimerDisable(TIMER0_BASE, TIMER_A);
      break;

    /** Timer 1 **/
    case(TIMER1):
      TimerDisable(TIMER1_BASE, TIMER_A);
      break;
  }
}

void resume_timer(uint32_t timer){
  switch(timer){
    /** Timer 0 **/
    case(TIMER0):
      TimerEnable(TIMER0_BASE, TIMER_A);
      break;

    /** Timer 1 **/
    case(TIMER1):
      TimerEnable(TIMER1_BASE, TIMER_A);
      break;
  }
}