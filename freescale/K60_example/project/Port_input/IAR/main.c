#include"MK60D10.h"
int main(void)
{
  SIM->SCGC5 |=SIM_SCGC5_PORTE_MASK;    //打开PORTE的时钟
  
  PORTE->PCR[26] &=~PORT_PCR_MUX_MASK;   //设置引脚复用为GPIO功能
  PORTE->PCR[26] |=PORT_PCR_MUX(1);
  
  PORTE->PCR[6] &=~PORT_PCR_MUX_MASK;   //设置引脚复用为GPIO功能
  PORTE->PCR[6] |=PORT_PCR_MUX(1);
  
  PTE->PDDR &=~(1<<26);                    //PTE26设置为输入方向
  PTE->PDDR |=(1<<6);                      //PTE6设置为输出方向
  PTE->PDOR |=(1<<6);
   
  PORTE->PCR[26] |=PORT_PCR_PE_MASK;       //PTE26使能上下拉功能
  PORTE->PCR[26] |=PORT_PCR_PS_MASK;       //PTE26启动上拉
                                         
  while(1)
  {
    if((PTE->PDIR >>26)==0)  //如果按键被按下
    {
      PTE->PDOR &=~(1<<6);
    }
    else
      PTE->PDOR |=(1<<6);
  }
}