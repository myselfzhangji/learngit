#include "fsl_gpio.h"
#include "fsl_clock.h"
#include "fsl_port.h"

void delay(uint32_t time)
{
  while(time--);
}
int main(void)
{
  gpio_pin_config_t GPIOA_init;
  gpio_pin_config_t GPIOE_init;
  
  GPIOA_init.pinDirection = kGPIO_DigitalOutput;
  GPIOA_init.outputLogic = 0; 
  CLOCK_EnableClock(kCLOCK_PortA);       //��PORTAʱ��
  PORT_SetPinMux(PORTA, 6, kPORT_MuxAsGpio);  //����PTA6ΪGPIO����
  GPIO_PinInit(GPIOA, 6, &GPIOA_init);  //PTA6����Ϊ���Ϊ1������������
 
  GPIOE_init.pinDirection = kGPIO_DigitalOutput;
  
  CLOCK_EnableClock(kCLOCK_PortE);       //��PORTEʱ��
  PORT_SetPinMux(PORTE, 6, kPORT_MuxAsGpio);  //����PTE6ΪGPIO����
  
  while(1)
  {
    GPIOE_init.outputLogic = 0;
    GPIO_PinInit(GPIOE, 6, &GPIOE_init);  //PTE6����Ϊ���Ϊ0������LED_T4
    delay(3000000);
    
    GPIOE_init.outputLogic = 1;
    GPIO_PinInit(GPIOE, 6, &GPIOE_init);  //PTE6����Ϊ���Ϊ1������LED_T4
    delay(3000000);
  }
//  return 0;
}