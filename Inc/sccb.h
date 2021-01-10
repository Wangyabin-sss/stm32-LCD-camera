#ifndef __SCCB_H
#define __SCCB_H

#include "main.h"
#include "tim.h"

//SCCB ��������	   SDAΪGPIOA_1 SCLΪGPIOA_0
 
#define SCCB_SDA_IN()  {GPIOA->MODER&=0XFFFFFFF3;}                             //GPIOA��1�� ����  
#define SCCB_SDA_OUT() {GPIOA->MODER&=0XFFFFFFF3; GPIOA->MODER|=0X00000004;}   //GPIOA��1�� ���  

//IO��������	 
#define SCCB_SCL(set)		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, set)

#define SCCB_SDA(set)		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, set)
#define SCCB_READ_SDA   (GPIOA->IDR & 0x00000002) != 0 ? 1:0

#define SCCB_ID   		 0X60  			//OV2640��ID



///////////////////////////////////////////
void SCCB_Init(void);
void SCCB_Start(void);
void SCCB_Stop(void);
void SCCB_No_Ack(void);
uint8_t SCCB_WR_Byte(uint8_t dat);
uint8_t SCCB_RD_Byte(void);
uint8_t SCCB_WR_Reg(uint8_t reg,uint8_t data);
uint8_t SCCB_RD_Reg(uint8_t reg);



#endif







