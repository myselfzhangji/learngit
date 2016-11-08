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
  CLOCK_EnableClock(kCLOCK_PortA);       //打开PORTA时钟
  PORT_SetPinMux(PORTA, 6, kPORT_MuxAsGpio);  //设置PTA6为GPIO功能
  GPIO_PinInit(GPIOA, 6, &GPIOA_init);  //PTA6设置为输出为1，驱动蜂鸣器
 
  GPIOE_init.pinDirection = kGPIO_DigitalOutput;
  
  CLOCK_EnableClock(kCLOCK_PortE);       //打开PORTE时钟
  PORT_SetPinMux(PORTE, 6, kPORT_MuxAsGpio);  //设置PTE6为GPIO功能
  
  while(1)
  {
    GPIOE_init.outputLogic = 0;
    GPIO_PinInit(GPIOE, 6, &GPIOE_init);  //PTE6设置为输出为0，驱动LED_T4
    delay(3000000);
    
    GPIOE_init.outputLogic = 1;
    GPIO_PinInit(GPIOE, 6, &GPIOE_init);  //PTE6设置为输出为1，驱动LED_T4
    delay(3000000);
  }
//  return 0;
}