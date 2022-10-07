/**************************
   Button Library .h File
**************************/

#ifndef BTNLIB_H
#define BTNLIB_H

/*8 Imports **/
#include "imports.h"          // common imports
#include "inc/hw_gpio.h"      // TIVAWARE library
#include "driverlib/gpio.h"   // TIVAWARE library

/** Macros **/
#define NORTH_SOUTH_BTN 0
#define WEST_EAST_BTN 1


/** Functions **/
void init_btns(void);
  /** Initiate switch
    Desc.:
      Initiates and configures a switch

    Goal:
      1. gate clock to PORT F
      2. wait for clock to reach PORT F
      3. unlock pin 0
      3. configure switches as input
      4. configure switches as weak pull-up

    Parameters:
      - void

    Returns:
      - void
  **/

uint8_t read_btn(uint8_t btn);
  /**  Read switch value
    Desc.:
      Reads the switch value

    Goal:
      1. return the current value of the switch (0 - pressed, 1 - not pressed)

    Parameters:
      1. unsiged 4-byte integer button:
        - values: NORTH_SOUTH_BTN, WEST_EAST_BTN;

    Returns:
      - void
  **/


void assign_btn_isr(void (*isr)(void));
  /** Assign handler to switchs (switch 1 and switch 2) itnerrupt
    Desc.:
      Configures switch interrupt to occur on low_level, registers handler to switch interrupt,
        enables switch interrupts

    Goal:
      1. disable pin 0 and pin 4 interrupts
      2. configure interrupt types as low-level
      3. assigns handler
      4. enables pin_0 and pin_4 interrupt

    Parameters:
      1. function pointer isr:
        - a pointer to the function.

    Returns:
      - void
  **/
  
  
void disable_btn_int(void);
  /** Disable switchs interrupts
    Desc.:
      Disables interrupts triggered by pin_0 and Pin_4 (on port F)

    Goal:
      1. disable pin 0 and pin 4 interrupts

    Parameters:
      - void

    Returns:
      - void
  **/

void enable_btn_int(void);
  /** Enables switchs interrupts
    Desc.:
      Enables interrupts triggered by pin_0 and Pin_4 (on port F)

    Goal:
      1. Enables pin 0 and pin 4 interrupts

    Parameters:
      - void

    Returns:
      - void
  **/
  
/** END OF FILE **/
#endif