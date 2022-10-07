/**************************
    State Machine .c File
**************************/
#include "state_machines.h"


enum states state;
extern uint8_t cooldown = 0;

uint8_t directions[2] = {NORTH_SOUTH_MASK, WEST_EAST_MASK};
uint8_t direction;
uint8_t color;

void SM(void){
  switch(state){
    /** Cars moving **/
    case (CAR_GREEN):
      color = GREEN_COLOR;
      set_TL_color(color, CAR_TRAFFIC_LIGHT, directions[direction]);
      set_TL_color(RED_COLOR, PED_TRAFFIC_LIGHT, directions[direction]);

      if(!cooldown){
        enable_btn_int();
      }
      break;

    /** Cars slowing down**/
    case (CAR_YELLOW):
      disable_btn_int();
      color = YELLOW_COLOR;
      set_TL_color(color, CAR_TRAFFIC_LIGHT, directions[direction]);
      break;

    /** Cars stopping **/
    case(CAR_TRANSITION):
      color = RED_COLOR;
      disable_btn_int();
      set_TL_color(color, CAR_TRAFFIC_LIGHT, directions[direction]);
      set_TL_color(GREEN_COLOR, PED_TRAFFIC_LIGHT, directions[direction]);
      break;

    /** Pedestrian walking **/
    case (PED_GREEN):
      set_TL_color(RED_COLOR, CAR_TRAFFIC_LIGHT, directions[direction]);
      set_TL_color(GREEN_COLOR, PED_TRAFFIC_LIGHT, directions[direction]);
      break;

    /** Pedestrian stopping **/
    case(PED_RED):
      begin_delay(1, TIMER1);
      set_TL_color(RED_COLOR, PED_TRAFFIC_LIGHT, directions[direction]);
      cooldown = 1;
      state = CAR_GREEN;
      break;
  }
}
