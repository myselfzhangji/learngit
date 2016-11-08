#include "MK60D10.h"
#include "gpio.h"
#include "i2c.h"
#include "adxl345.h"

int main(void)
{
  PORT_PinMuxConfig(HW_GPIOB, 2, kPinAlt2);  //����PTB2Ϊi2c_scl
  PORT_PinMuxConfig(HW_GPIOB, 3, kPinAlt2);  //����PTB3Ϊi2c_sda
  return 0;
}