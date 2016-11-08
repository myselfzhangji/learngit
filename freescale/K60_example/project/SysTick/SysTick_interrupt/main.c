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
  PORT_PinMuxConfig(HW_GPIOE, 6, kPinAlt1);   //����PTE6ΪGPIO����
  GPIO_QuickInit(HW_GPIOE,6,kGPIO_Mode_OPP);  //����PTE6Ϊ�������
  SYSTICK_Init(1000*100);         //����SysTick��ֵ
  SYSTICK_ITConfig(ENABLE);       //ʹ��SysTick�ж�
  SYSTICK_Cmd(ENABLE);            //ʹ��SysTick����
  while(1);
}