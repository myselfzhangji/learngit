#include "gpio.h"
#include "common.h"
#include "systick.h"

static void GPIO_ISR(uint32_t pinxArray)
{
    if(pinxArray == (1<<26))
    {
        GPIO_ToggleBit(HW_GPIOE, 6);
    }
}
int main(void)
{
    /* 配置LED1，GPIO，输出功能                   */
    PORT_PinMuxConfig(HW_GPIOE, 6, kPinAlt1);
    GPIO_QuickInit(HW_GPIOE, 6, kGPIO_Mode_OPP);

    PORT_PinMuxConfig(HW_GPIOE, 26, kPinAlt1);   //设置PTE26为GPIO功能
    GPIO_QuickInit(HW_GPIOE, 26, kGPIO_Mode_IPU);//设置PTE26为输入功能
    PORT_PinOpenDrainConfig(HW_GPIOE, 26, ENABLE);
    GPIO_ITDMAConfig(HW_GPIOE, 26, kGPIO_IT_FallingEdge, true);
    GPIO_CallbackInstall(HW_GPIOE, GPIO_ISR);
    while(1);
}
