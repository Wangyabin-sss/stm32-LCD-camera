#ifndef _xpt2046_H
#define _xpt2046_H

#include "main.h"
#include "spi.h"
#include "usart.h"

#define CS_L	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET)	// 片选脚选中
#define CS_H	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET)		// 取消片选

void spi_send8(uint8_t data);
uint8_t spi_receive8(void);
void XPT2046_data(void); //读取值

#endif

