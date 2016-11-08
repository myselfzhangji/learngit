#include "pit.h"
#include "gpio.h"
#include "uart.h"
#include "common.h"

static void PIT0_ISR(void)
{
    printf("PIT0 IT enter!\r\n");
    DelayMs(500);
    printf("PIT0 IT exit!\r\n");
}

static void PIT1_ISR(void)
{
    printf("PIT1 IT!\r\n");
}

int main(void)
{
	PIT_InitTypeDef pitConfig_t0,pitConfig_t1;
    
    GPIO_QuickInit(HW_GPIOE, 6, kGPIO_Mode_OPP);
    UART_QuickInit(UART0_RX_PD06_TX_PD07, 115200);

	/* NVIC_PriorityGroup_2来确定哪几位被定义为为主优先级，哪几位被定义为子优先级 */
	/* Application Interrupt and Reset control Register 来确定*/
	/* 第一个2是主优先级的值，第二个2是子优先级的值 */
	NVIC_SetPriority(PIT0_IRQn, NVIC_EncodePriority(NVIC_PriorityGroup_2, 1, 2));
	/* NVIC_PriorityGroup_2来确定哪几位被定义为为主优先级，哪几位被定义为子优先级 */
	/* 第一个1是主优先级的值，第二个2是子优先级的值 */
	NVIC_SetPriority(PIT1_IRQn, NVIC_EncodePriority(NVIC_PriorityGroup_2, 2, 2));

	pitConfig_t0.timeInUs=1000*1000;  //T0_time=1000*1000=1s
	pitConfig_t1.chl=HW_PIT_CH1;      //use PIT_T1
	PIT_Init(&pitConfig_t0);          //Init PIT_T0
	PIT_CallbackInstall(HW_PIT_CH0, PIT0_ISR);
    PIT_ITDMAConfig(HW_PIT_CH0, kPIT_IT_TOF, true);

	pitConfig_t0.chl=HW_PIT_CH0;      //use PIT_T0
	pitConfig_t1.timeInUs=1000*200;   //T1_time=1000*200=0.2s
	PIT_Init(&pitConfig_t1);          //Init PIT_T1
	PIT_CallbackInstall(HW_PIT_CH1, PIT1_ISR);
    PIT_ITDMAConfig(HW_PIT_CH1, kPIT_IT_TOF, true);

	while(1)
	{}
}
