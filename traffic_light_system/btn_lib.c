/**************************
   Button Library .c File
**************************/

#include "btn_lib.h"


void init_btns(void){
  // Initializing PORT F
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // gate clock to port F
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)){}; // wait for clock to reach port F

  HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
  HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= GPIO_PIN_0;

  GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);
  GPIOPadConfigSet(GPIO_PORTF_BASE,(GPIO_PIN_0 | GPIO_PIN_4),GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
};

uint8_t read_btn(uint8_t btn){
  if(btn){
    return GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);
  }

  return GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0);
};

void assign_btn_isr(void (*isr)(void)){
   GPIOIntDisable(GPIO_PORTF_BASE, (GPIO_PIN_0 | GPIO_PIN_4));
   GPIOIntTypeSet(GPIO_PORTF_BASE, (GPIO_PIN_0 | GPIO_PIN_4), GPIO_LOW_LEVEL);
   GPIOIntRegister(GPIO_PORTF_BASE, isr);
   GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_0|GPIO_INT_PIN_4);
};

void disable_btn_int(void){
     GPIOIntDisable(GPIO_PORTF_BASE, (GPIO_PIN_0 | GPIO_PIN_4));
}

void enable_btn_int(void){
     GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_0|GPIO_INT_PIN_4);
}