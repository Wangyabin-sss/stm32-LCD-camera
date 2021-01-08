#ifndef _ili9488_H
#define _ili9488_H

#include "fsmc.h"
#include "gpio.h"
#include "usart.h"



#define	Mode_H		 0		//LCD水平显示
#define	Mode_V		 1		//LCD竖屏显示

#define FSMC_REG     0x60000000		// FSMC 写寄存器地址
#define FSMC_DATA    0x60020000		// FSMC 写数据地址

#define LCD_RST_L	  		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET)	// 输出低电平，复位屏幕
#define LCD_RST_H  	  	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET)		// 输出高电平
 
#define LCD_Backlight_OFF	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET)		// 输出低电平，关闭背光
#define LCD_Backlight_ON  	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET)		// 输出高电平，点亮背光


void LCD_WR_REG(uint16_t reg);
void LCD_WR_DATA(uint16_t data);
uint16_t LCD_RD_DATA(void);
void LCD_Init(void);        //LCD初始化
void LCD_SetCursor(uint16_t x, uint16_t y); //设置屏幕要显示数据的坐标
uint16_t RGB888_RGB565(uint32_t Color);
void LCD_Clear(uint32_t color);
void LCD_DisplayMode(uint8_t direction);  //lcd显示方向设置
void LCD_DrawPoint(uint16_t x,uint16_t y,uint32_t color);//画点函数
void show_photo(uint16_t x,uint16_t y,uint16_t px,uint16_t py,const uint16_t *photo);


#endif
/*lcd驱动ic为ILI9488*/
