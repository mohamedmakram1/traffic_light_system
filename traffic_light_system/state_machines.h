/**************************
   State Machine .h File
**************************/

#ifndef SM_H
#define SM_H

/** Imports **/
#include "imports.h"            // Common imports
#include "light_controller.h"   // Traffic light controller
#include "timer_lib.h"          // Tiemr library
#include "btn_lib.h"            // GPIO switchs library

/** Macros **/
#define NORTH_SOUTH_FLAG 0
#define WEST_EAST_FLAG 1

// state machine states
enum states {CAR_GREEN, CAR_YELLOW, CAR_TRANSITION, PED_GREEN, PED_RED};
extern enum states state;

// direction
extern uint8_t directions[2];
extern uint8_t direction; // direction flag used for toggling directions

// traffic light color
extern uint8_t color;

// pedestrian traffic light cooldown flag
extern uint8_t cooldown;

void SM(void);
  /** Initiate Port E
    Desc.: the state machine of the CAR_TRAFFIC_LIGHT traffic light and the pedestrian traffic
      light with 5 states.

    States:
      1. CAR_GREEN:
        - - Turns the traffic light in the current direction to a green color.
        - If the pedestrian traffic light cooldown is reset, enables GPIO switches interrupts.
        - Turns the pedestrian traffic light in the current direction to a red color.


      2. CAR_YELLOW:
        - Turns the pedestrian traffic light in the current direction to a yellow color.
        - disables GPIO switchs interrupts.

      3. CAR_TRANSITION:
        - Turns the traffic light in the current direction to a red color.
        - Disables GPIO switches interrupts.
        - Turns the pedestrian traffic light in the current direction to a green color.

    Parameters:
      - void

    Returns:
      - void
  **/

/** END OF FILE **/
#endif