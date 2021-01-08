#ifndef __SCCB_H
#define __SCCB_H
#include "main.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序参考自网友guanfu_wang代码。
//ALIENTEK STM32F103开发板 
//SCCB 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/4/16
//版本：V1.0		    							    							  
//////////////////////////////////////////////////////////////////////////////////
 
 
#define SCCB_SDA_IN()  {GPIOA->CRL&=0XFFFFFF0F;GPIOA->CRL|=0X00000080;}   //GPIOA的1口 输入（1000）      上下拉输入
#define SCCB_SDA_OUT() {GPIOA->CRL&=0XFFFFFF0F;GPIOA->CRL|=0X00000030;}   //GPIOA的1口 输出（0011）50MHz 推挽输出

//IO操作函数	 
#define SCCB_SCL    		PDout(3)	 	//SCL
#define SCCB_SDA    		PGout(13) 		//SDA	 
#define SCCB_READ_SDA   PGin(13)  		//输入SDA    

#define SCCB_ID   		 0X60  			//OV2640的ID

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







