/**************************
    Light Controlelr .h File
**************************/
#ifndef LIGHT_H
#define LIGHT_H

/** Imports **/
#include "imports.h"

// GPIO
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"

/** Macros **/
  // Used for initializing ports
#define PORT_E_PINS (GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5)
#define PORT_B_PINS (GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_5)

  // Colors
#define GREEN_COLOR     GPIO_PIN_0      // 1
#define YELLOW_COLOR    GPIO_PIN_1      // 2
#define RED_COLOR       GPIO_PIN_2      // 4

  // Traffic light flags
#define PED_TRAFFIC_LIGHT 0
#define CAR_TRAFFIC_LIGHT 1

  // Direction MASKS
#define NORTH_SOUTH_MASK 1
#define WEST_EAST_MASK 8


/** Functions **/
void init_port_E(void);
  /** Initiate Port E
    Desc.:
      Configures port E ports that connects to the external LEDs representing the cars traffic light.
      Pins (0-2) are used with the north-south traffic lights
      Pins (3-5) are used with the west-east traffic lights

    Goal:
      1. gate clock to port E
      2. wait for clock to reach port E
      3. configure ports 0-5 as output ports

    Parameters:
      - void

    Returns:
      - void
  **/


void init_port_B(void);
  /** Initiate Port B
    Desc.:
      Configures port B ports that connects to the external LEDs representing the pedstrian traffic light.
      Pins (0,2) are used with the north-south pedstrian traffic lights
      Pins (3,5 ) are used with the west-east pedstrian traffic lights

    Goal:
      1. gate clock to port B
      2. wait for clock to reach port B
      3. configure ports 0,2 and 3,5 as output ports (see documantion for explanation)

    Parameters:
      - void

    Returns:
      - void
  **/


void set_TL_color(uint8_t color, uint8_t traffic_light, uint8_t direction);
  /** Change Color of Traffic Light
    Desc.:
      Given the color, traffic light type, and direction; this function changes its
        color to passed color. While simultaneously turning of other colors.

    Goal:
      1. set the current traffic light color to only a single color

    Parameters (3):
      1. unsiged 1-byte integer color:
        - the new color of the traffic light

      2. unsiged 1-byte integer traffic_light:
        - traffic light flag
        - values: NORTH_SOUTH_MASK or WEST_EAST_MASK

      3. unsiged 1-byte integer direction:
        - direction mast
        - values: NORTH_SOUTH_MASK or WEST_EAST_MASK

    Returns:
      - void
  **/
/**************/
#endif