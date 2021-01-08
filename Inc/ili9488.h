#ifndef _ili9488_H
#define _ili9488_H

#include "fsmc.h"
#include "gpio.h"
#include "usart.h"



#define	Mode_H		 0		//LCDˮƽ��ʾ
#define	Mode_V		 1		//LCD������ʾ

#define FSMC_REG     0x60000000		// FSMC д�Ĵ�����ַ
#define FSMC_DATA    0x60020000		// FSMC д���ݵ�ַ

#define LCD_RST_L	  		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET)	// ����͵�ƽ����λ��Ļ
#define LCD_RST_H  	  	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET)		// ����ߵ�ƽ
 
#define LCD_Backlight_OFF	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET)		// ����͵�ƽ���رձ���
#define LCD_Backlight_ON  	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET)		// ����ߵ�ƽ����������


void LCD_WR_REG(uint16_t reg);
void LCD_WR_DATA(uint16_t data);
uint16_t LCD_RD_DATA(void);
void LCD_Init(void);        //LCD��ʼ��
void LCD_SetCursor(uint16_t x, uint16_t y); //������ĻҪ��ʾ���ݵ�����
uint16_t RGB888_RGB565(uint32_t Color);
void LCD_Clear(uint32_t color);
void LCD_DisplayMode(uint8_t direction);  //lcd��ʾ��������
void LCD_DrawPoint(uint16_t x,uint16_t y,uint32_t color);//���㺯��
void show_photo(uint16_t x,uint16_t y,uint16_t px,uint16_t py,const uint16_t *photo);


#endif
/*lcd����icΪILI9488*/
