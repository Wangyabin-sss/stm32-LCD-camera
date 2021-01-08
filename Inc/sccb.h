#ifndef __SCCB_H
#define __SCCB_H
#include "main.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ο�������guanfu_wang���롣
//ALIENTEK STM32F103������ 
//SCCB ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/4/16
//�汾��V1.0		    							    							  
//////////////////////////////////////////////////////////////////////////////////
 
 
#define SCCB_SDA_IN()  {GPIOA->CRL&=0XFFFFFF0F;GPIOA->CRL|=0X00000080;}   //GPIOA��1�� ���루1000��      ����������
#define SCCB_SDA_OUT() {GPIOA->CRL&=0XFFFFFF0F;GPIOA->CRL|=0X00000030;}   //GPIOA��1�� �����0011��50MHz �������

//IO��������	 
#define SCCB_SCL    		PDout(3)	 	//SCL
#define SCCB_SDA    		PGout(13) 		//SDA	 
#define SCCB_READ_SDA   PGin(13)  		//����SDA    

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







