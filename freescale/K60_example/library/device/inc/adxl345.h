/**
  ******************************************************************************
  * @file    adxl345.h
  * @author  YANDLD
  * @version V2.5
  * @date    2013.12.25
  * @brief   蓝宙电子官网：www.landzo.com  蓝宙官方淘宝商城：http://landzo.taobao.com
  ******************************************************************************
  */
  
#ifndef __ADXL345_H__
#define __ADXL345_H__

#include <stdint.h>

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x)	(sizeof(x) / sizeof((x)[0]))
#endif


//!< API functions 
int adxl345_init(uint32_t instance);
int adxl345_readXYZ(short *x, short *y, short *z);
int adxl345_calibration(void);
short adxl345_convert_angle(short x, short y, short z, short *ax, short *ay, short *az);


#endif



