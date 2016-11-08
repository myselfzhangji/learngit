#include"MK60D10.h"
int main(void)
{
  SIM->SCGC5 |=SIM_SCGC5_PORTA_MASK;    //打开PORTA的时钟
  SIM->SCGC5 |=SIM_SCGC5_PORTE_MASK;    //打开PORTE的时钟
  
  PORTA->PCR[6] &=~PORT_PCR_MUX_MASK;   //设置引脚复用为GPIO功能
  PORTA->PCR[6] |=PORT_PCR_MUX(1);
  PORTE->PCR[6] &=~PORT_PCR_MUX_MASK;   //设置引脚复用为GPIO功能
  PORTE->PCR[6] |=PORT_PCR_MUX(1);
  
  PTA->PDDR |=(1<<6);                   //PTA6设置为输出方向
  PTE->PDDR |=(1<<6);                   //PTE6设置为输出方向
  
  PTA->PDOR &=~(1<<6);                  //PTA6设置为输出为1，驱动蜂鸣器
  PTE->PDOR &=~(1<<6);                  //PTE6设置为输出为0，点亮LED
  while(1);
}