/**************************
      Main program
**************************/

    /** Imports **/
#include "state_machines.h"     // State machine
#include "timer_lib.h"          // Timers library
#include "driverlib/sysctl.h"   //for sleeping
#include "btn_lib.h"            // Button library



/*** Function Prototype ***/
void timer0_isr(void);

void timer1_isr(void);

void btn_isr(void);



    /*** Main Progaram ***/
int main(){

  __asm("CPSID i"); // disable system itnterrupts

  {
    // Initiating ports
    init_port_E();
    init_port_B();

    // Initiating timers
    init_timer(TIMER0);
    assign_isr(timer0_isr, TIMER0);

    init_timer(TIMER1);
    assign_isr(timer1_isr, TIMER1);

    // Initiating GPIO Switches
    init_btns();
    assign_btn_isr(btn_isr);

    // Initiating State Machine
    state = CAR_TRANSITION;
    color = RED_COLOR;
    direction = WEST_EAST_FLAG; //West-East

    set_TL_color(RED_COLOR, CAR_TRAFFIC_LIGHT, WEST_EAST_MASK);
    set_TL_color(GREEN_COLOR, PED_TRAFFIC_LIGHT, WEST_EAST_MASK);
    set_TL_color(RED_COLOR, CAR_TRAFFIC_LIGHT, NORTH_SOUTH_MASK);
    set_TL_color(RED_COLOR, PED_TRAFFIC_LIGHT, NORTH_SOUTH_MASK);

    // Start State Machine
    begin_delay(1, TIMER0);
  }

  __asm("CPSIE i"); // enable system itnterrupts

  /** main loop **/
  while(1){
    SM();
  }

  /** end main **/
  return 0;
}

// Timer 0 interrupt service routine
void timer0_isr(void){
  TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

  state = (state+1) % 3; // Loop over states 0, 1, 2

  uint8_t delay_sec = 5 / ((color*2) % 7); // see documentation explanation
  begin_delay( delay_sec, TIMER0);

  if(color == RED_COLOR){
    direction = !direction;
  }
}

// Timer 1 interrupt service routine
void timer1_isr(void){
  TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

  if(state == PED_GREEN){
    state = PED_RED;
    resume_timer(TIMER0);
  }

  cooldown = 0;
}

// GPIO switches interrupt service routine
void btn_isr(void){
  disable_btn_int();
  GPIOIntClear(GPIO_PORTF_BASE, GPIO_INT_PIN_0|GPIO_INT_PIN_4);

  uint8_t ns_btn_val = read_btn(NORTH_SOUTH_BTN);
  uint8_t we_btn_val = read_btn(WEST_EAST_BTN) >> 4;

  if((!we_btn_val && direction) || (!ns_btn_val && !direction)){
      pause_timer(TIMER0);
      state = PED_GREEN;
      begin_delay(2, TIMER1);
  }
}