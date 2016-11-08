#include"MK60D10.h"
int main(void)
{
  SIM->SCGC5 |=SIM_SCGC5_PORTA_MASK;    //��PORTA��ʱ��
  SIM->SCGC5 |=SIM_SCGC5_PORTE_MASK;    //��PORTE��ʱ��
  
  PORTA->PCR[6] &=~PORT_PCR_MUX_MASK;   //�������Ÿ���ΪGPIO����
  PORTA->PCR[6] |=PORT_PCR_MUX(1);
  PORTE->PCR[6] &=~PORT_PCR_MUX_MASK;   //�������Ÿ���ΪGPIO����
  PORTE->PCR[6] |=PORT_PCR_MUX(1);
  
  PTA->PDDR |=(1<<6);                   //PTA6����Ϊ�������
  PTE->PDDR |=(1<<6);                   //PTE6����Ϊ�������
  
  PTA->PDOR &=~(1<<6);                  //PTA6����Ϊ���Ϊ1������������
  PTE->PDOR &=~(1<<6);                  //PTE6����Ϊ���Ϊ0������LED
  while(1);
}