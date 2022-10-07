/**************************
    Light Controlelr .c File
**************************/
#include "light_controller.h"

/** Functions **/
void init_port_E(void){
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE); // gate clock to port E
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)){}; // wait for clock to reach port E

  GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, PORT_E_PINS); // configure port E's pins as output pins
};


void init_port_B(void){
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); // gate clock to port B
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)){}; // wait for clock to reach port B

  GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, PORT_B_PINS); // configure port B's pins as output pins
}


void set_TL_color(uint8_t color, uint8_t traffic_light, uint8_t direction){
  switch(traffic_light){
    
    case(CAR_TRAFFIC_LIGHT):
      GPIOPinWrite(GPIO_PORTE_BASE, direction * (GREEN_COLOR+YELLOW_COLOR+RED_COLOR), direction * color); // see documentation for explanation
      break;
      
    case(PED_TRAFFIC_LIGHT):
      GPIOPinWrite(GPIO_PORTB_BASE, direction * (GREEN_COLOR+YELLOW_COLOR+RED_COLOR), direction * color);
      break;
  }
}










