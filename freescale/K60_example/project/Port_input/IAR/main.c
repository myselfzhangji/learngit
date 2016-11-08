#include"MK60D10.h"
int main(void)
{
  SIM->SCGC5 |=SIM_SCGC5_PORTE_MASK;    //��PORTE��ʱ��
  
  PORTE->PCR[26] &=~PORT_PCR_MUX_MASK;   //�������Ÿ���ΪGPIO����
  PORTE->PCR[26] |=PORT_PCR_MUX(1);
  
  PORTE->PCR[6] &=~PORT_PCR_MUX_MASK;   //�������Ÿ���ΪGPIO����
  PORTE->PCR[6] |=PORT_PCR_MUX(1);
  
  PTE->PDDR &=~(1<<26);                    //PTE26����Ϊ���뷽��
  PTE->PDDR |=(1<<6);                      //PTE6����Ϊ�������
  PTE->PDOR |=(1<<6);
   
  PORTE->PCR[26] |=PORT_PCR_PE_MASK;       //PTE26ʹ������������
  PORTE->PCR[26] |=PORT_PCR_PS_MASK;       //PTE26��������
                                         
  while(1)
  {
    if((PTE->PDIR >>26)==0)  //�������������
    {
      PTE->PDOR &=~(1<<6);
    }
    else
      PTE->PDOR |=(1<<6);
  }
}