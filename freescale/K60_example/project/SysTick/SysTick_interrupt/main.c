#include "gpio.h"
#include "common.h"
#include "systick.h"

#define LED PEout(6)

void SysTick_Handler(void)
{
  GPIO_ToggleBit(HW_GPIOE, 6);
}

int main(void)
{
  PORT_PinMuxConfig(HW_GPIOE, 6, kPinAlt1);   //设置PTE6为GPIO功能
  GPIO_QuickInit(HW_GPIOE,6,kGPIO_Mode_OPP);  //设置PTE6为输出功能
  SYSTICK_Init(1000*100);         //设置SysTick初值
  SYSTICK_ITConfig(ENABLE);       //使能SysTick中断
  SYSTICK_Cmd(ENABLE);            //使能SysTick工作
  while(1);
}