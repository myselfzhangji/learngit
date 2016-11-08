#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_clock.h"
#include "fsl_wdog.h"
#include "fsl_common.h"

#define GPIO_OUT       GPIOE
#define PORT           PORTE
#define GPIO_OUT_PIN   6
#define GPIO_IN_PIN    26
#define GPIO_IN        GPIOE
#define outputlevel     0
#define watcgdog_timeoutValue  2000   //timeoutvalue=2000,2s


void delay_ms(uint32_t time)
{
  while(time--);
}
void Init_gpio_out(PORT_Type *port, GPIO_Type *gpio, uint32_t pin, uint32_t output)
{
  gpio_pin_config_t GPIO_config;
  GPIO_config.pinDirection = kGPIO_DigitalOutput;
  GPIO_config.outputLogic = output;
  CLOCK_EnableClock(kCLOCK_PortE);
  PORT_SetPinMux(port, pin, kPORT_MuxAsGpio);
  GPIO_PinInit(gpio, pin, &GPIO_config);
}
void Init_gpio_in(PORT_Type *port, GPIO_Type *gpio, uint32_t pin)
{
  gpio_pin_config_t GPIO_config;
  port_pin_config_t PORT_config;
  GPIO_config.pinDirection = kGPIO_DigitalInput;
  PORT_config.pullSelect =(PORT_PCR_PE(1)) | (PORT_PCR_PS(1)); //使能上下拉,选择上拉
  CLOCK_EnableClock(kCLOCK_PortE);
  PORT_SetPinConfig(port, pin, &PORT_config);
  PORT_SetPinMux(port, pin, kPORT_MuxAsGpio);
  GPIO_PinInit(gpio, pin, &GPIO_config);
}
void Watcgdog_init()
{
  wdog_config_t watchgdog_config;
  uint32_t WDOG_clockSource_Frequency;
  WDOG_GetDefaultConfig(&watchgdog_config);
//  watchgdog_config.clockSource = kWDOG_AlternateClockSource;
//  WDOG_clockSource_Frequency = CLOCK_GetFreq(kCLOCK_BusClk);
  watchgdog_config.clockSource = kWDOG_LpoClockSource;
  WDOG_clockSource_Frequency = CLOCK_GetFreq(kCLOCK_LpoClk);  
  watchgdog_config.timeoutValue = (WDOG_clockSource_Frequency/1000) * watcgdog_timeoutValue;     
  WDOG_Init(WDOG, &watchgdog_config);
}
int main(void)
{
  Init_gpio_in(PORT, GPIO_IN, GPIO_IN_PIN);
  Init_gpio_out(PORT, GPIO_OUT, GPIO_OUT_PIN, 1);
  Watcgdog_init();
  Init_gpio_out(PORT, GPIO_OUT, GPIO_OUT_PIN, 0);
  delay_ms(3000000); 
  Init_gpio_out(PORT, GPIO_OUT, GPIO_OUT_PIN, 1);
  while(1)
  {
    if((PTE->PDIR >>26)==0)
    {
      WDOG_Refresh(WDOG);
      delay_ms(3000);
    }
    delay_ms(300);
  }
}