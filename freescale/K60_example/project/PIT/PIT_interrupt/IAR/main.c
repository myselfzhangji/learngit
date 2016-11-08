#include "gpio.h"
#include "common.h"
#include "pit.h"

/* CH Kinetis�̼��� V2.50 �汾 */
/* �޸���Ƶ ���޸� CMSIS��׼�ļ� system_MKxxxx.c �е� CLOCK_SETUP �� */

/*
     ʵ�����ƣ�PIT��ʱ���ж�
     ʵ��ƽ̨����ѻ������
     ����оƬ��MK60DN512ZVQ10
 ʵ��Ч����ʹ��PITģ���0�Ŷ�ʱ������1s�������жϣ���PIT0�жϺ�����
     ���ڷ������ݺ�С������仯
     ÿ��1sС����˸һ�Σ����ڷ�������
*/

/* PIT0�жϷ����� */
//�˺����б�д�û��ж���Ҫ��������
static void PIT_ISR(void)
{
    static uint32_t i;
    //�ж�������������
//    printf("enter PIT interrupt! %d\r\n", i++); 
    /* ��˸С�� */
    GPIO_ToggleBit(HW_GPIOE, 6);
}

int main(void)
{
    DelayInit();
    
    GPIO_QuickInit(HW_GPIOE, 6, kGPIO_Mode_OPP); /* LED */
    
//    UART_QuickInit(UART0_RX_PD06_TX_PD07, 115200);
    
    /* ��ʼ��PITģ�� */
    PIT_InitTypeDef PIT_InitStruct1;  //����ṹ�����
    PIT_InitStruct1.chl = HW_PIT_CH0; /* ʹ��0�Ŷ�ʱ�� */
    PIT_InitStruct1.timeInUs = 1000*1000; /* ��ʱ����1S */
    PIT_Init(&PIT_InitStruct1); //pitģ���ʼ��
    /* ע��PIT �жϻص����� */
    PIT_CallbackInstall(HW_PIT_CH0, PIT_ISR); //0�Ŷ�ʱ�����жϴ���
    /* ����PIT0��ʱ���ж� */
    PIT_ITDMAConfig(HW_PIT_CH0, kPIT_IT_TOF, true);
    
    while(1)
    {
        /* �ȴ�ϵͳ�ж� */
    }
}


