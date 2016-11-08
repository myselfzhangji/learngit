#include "fsl_gpio.h"
#include "fsl_clock.h"
#include "fsl_port.h"

int main(void)
{
  gpio_pin_config_t GPIOE_init;
  port_pin_config_t PORTE_init;
  
  CLOCK_EnableClock(kCLOCK_PortE);       //打开PORTE时钟
  
  PORT_SetPinMux(PORTE, 26, kPORT_MuxAsGpio);  //设置PTE26为GPIO功能
  GPIOE_init.pinDirection = kGPIO_DigitalInput; //PTE26设置为输入
  GPIO_PinInit(GPIOE, 26, &GPIOE_init);
  PORTE_init.pullSelect =(PORT_PCR_PE(1)) | (PORT_PCR_PS(1));      //使能上下拉,选择上拉
  PORT_SetPinConfig(PORTE, 26, &PORTE_init);

  PORT_SetPinMux(PORTE, 6, kPORT_MuxAsGpio);  //设置PTE6为GPIO功能
  GPIOE_init.pinDirection = kGPIO_DigitalOutput;
  
  
  while(1)
  {
    if((PTE->PDIR >>26)==1)
    {
      GPIOE_init.outputLogic = 0;
      GPIO_PinInit(GPIOE, 6, &GPIOE_init);
    }
    else
    {
      GPIOE_init.outputLogic = 1;
      GPIO_PinInit(GPIOE, 6, &GPIOE_init);
    }
  }
  
}