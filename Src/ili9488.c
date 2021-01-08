#include "ili9488.h"

//LCD相关参数结构体
struct	
{
	uint16_t ID;        // 控制器ID	
	uint16_t Width;		  // 水平分辨率
	uint16_t Height;		// 垂直分辨率
	uint16_t PenColor;  //	LCD当前画笔颜色
	uint16_t BackColor;		//背景色
	uint8_t  Direction;		//显示方向
	uint8_t  ShowNum_Mode;	// 数字填充模式
}TFT_LCD;


/*****************************************************************************************
*	函 数 名: LCD_WR_REG
*	入口参数: reg - 要操作的寄存器
*	返 回 值: 无
*	函数功能: 选择要操作的寄存器
*	说    明: 
******************************************************************************************/

void LCD_WR_REG(uint16_t reg)
{   
	*(__IO uint16_t*) FSMC_REG = reg;	 
}

/*****************************************************************************************
*	函 数 名: LCD_WR_DATA
*	入口参数: data - 要写入的数据
*	返 回 值: 无
*	函数功能: 往相应的寄存器写入数据
*	说    明: 
******************************************************************************************/

void LCD_WR_DATA(uint16_t data)
{	 
	*(__IO uint16_t*) FSMC_DATA = data;	
}

/*****************************************************************************************
*	函 数 名: LCD_RD_DATA
*	入口参数: reg - 要读取的寄存器
*	返 回 值: 从该寄存器获取到的数值
*	函数功能: 从相应的寄存器读出数据
*	说    明: 无
******************************************************************************************/
uint16_t LCD_RD_DATA(void)
{
   uint16_t data;	
	data = *(__IO uint16_t*) FSMC_DATA;	
	return data;	 
}

/*****************************************************************************************
*	函 数 名: LCD_Init
*	入口参数: 无
*	返 回 值: 无
*	函数功能: 初始化LCD的配置
*	说    明: 主要是操作ILI9488的相关寄存器，进行必要的设置，默认竖屏显示
******************************************************************************************/

void LCD_Init(void)
{
  // 复位ILI9488
	LCD_RST_L;	HAL_Delay(10); 	//延时不能太小
	LCD_RST_H;	HAL_Delay(10); 

	//读取LCD控制器的ID号
	LCD_WR_REG(0XD3);	
  TFT_LCD.ID=LCD_RD_DATA();     //假读
	TFT_LCD.ID=LCD_RD_DATA();     //读0x00
	TFT_LCD.ID=LCD_RD_DATA();     //读0x94
	TFT_LCD.ID<<=8;               //0x94移入高8位
	TFT_LCD.ID|=LCD_RD_DATA();    //读0x88并获取完整ID号
	printf(" LCD ID:ILI%x\r\n",TFT_LCD.ID);
	if(TFT_LCD.ID!=0x9488)while(1);	
	
   // 初始化ILI9488
	LCD_WR_REG(0xE0); //P-Gamma
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0x0C);
	LCD_WR_DATA(0x09);
	LCD_WR_DATA(0x17);
	LCD_WR_DATA(0x09);
	LCD_WR_DATA(0x3E);
	LCD_WR_DATA(0x89);
	LCD_WR_DATA(0x49);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x0D);
	LCD_WR_DATA(0x0A);
	LCD_WR_DATA(0x13);
	LCD_WR_DATA(0x15);
	LCD_WR_DATA(0x0F);
	LCD_WR_REG(0XE1); //N-Gamma
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x11);
	LCD_WR_DATA(0x15);
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x05);
	LCD_WR_DATA(0x2D);
	LCD_WR_DATA(0x34);
	LCD_WR_DATA(0x41);
	LCD_WR_DATA(0x02);
	LCD_WR_DATA(0x0B);
	LCD_WR_DATA(0x0A);
	LCD_WR_DATA(0x33);
	LCD_WR_DATA(0x37);
	LCD_WR_DATA(0x0F);

	LCD_WR_REG(0XC0); //Power Control 1
	LCD_WR_DATA(0x17); //Vreg1out
	LCD_WR_DATA(0x15); //Verg2out
	LCD_WR_REG(0xC1); //Power Control 2
	LCD_WR_DATA(0x41); //VGH,VGL
	LCD_WR_REG(0xC5); //Power Control 3
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x12); //Vcom
	LCD_WR_DATA(0x80);

	LCD_WR_REG(0x36); //Memory Access
	LCD_WR_DATA(0x48);
	LCD_WR_REG(0x3A); // Interface Pixel Format
	LCD_WR_DATA(0x55);
	LCD_WR_REG(0XB0); // Interface Mode Control
	LCD_WR_DATA(0x00);
	LCD_WR_REG(0xB1); //Frame rate
	LCD_WR_DATA(0xA0); //60Hz
	LCD_WR_REG(0xB4); //Display Inversion Control
	LCD_WR_DATA(0x02); //2-dot
	LCD_WR_REG(0XB6); //RGB/MCU Interface Control
	LCD_WR_DATA(0x02); //MCU
	LCD_WR_DATA(0x02); //Source,Gate scan dieection
	LCD_WR_REG(0XE9); // Set Image Function
	LCD_WR_DATA(0x00); // Disable 24 bit data input
	LCD_WR_REG(0xF7);// Adjust Control
	LCD_WR_DATA(0xA9);
	LCD_WR_DATA(0x51);
	LCD_WR_DATA(0x2C);
	LCD_WR_DATA(0x82);
	// D7 stream, loose
	LCD_WR_REG(0x11); //Sleep out
	HAL_Delay(10); 
	LCD_WR_REG(0x29); //Display on
	
//	LCD_SetBackColor(LCD_BLACK); // 设置背景色
//	LCD_SetColor(LCD_WHITE);		// 设置画笔颜色
//	LCD_SetFont(&Font24);  			// 设置默认字体
//	LCD_ShowNumMode(Fill_Space);	// 设置数字填充模式
	LCD_DisplayMode(Mode_V);		// 设置显示方向，竖屏
	LCD_Clear(0xffffff);		// 清屏
	
	LCD_Backlight_ON;
}

/*****************************************************************************************
*	函 数 名:	 LCD_SetCursor
*	入口参数:	 x - 水平坐标
*			  	   y - 垂直坐标
*	返 回 值: 无
*	函数功能: 设置屏幕要显示数据的坐标
*	说    明: 0x2A 为水平坐标寄存器地址，0x2B为垂直坐标寄存器地址
******************************************************************************************/

void LCD_SetCursor(uint16_t x, uint16_t y)
{	   
   //ILI9488设置坐标时必须把END坐标也写进去。因为END坐标通常不确定，这里直接写最大坐标
	LCD_WR_REG(0x2A); 							
	LCD_WR_DATA(x>>8);LCD_WR_DATA(x&0XFF); 	//设置水平坐标，高位在前	
	LCD_WR_DATA(0x01);   // 设置最大X坐标为480
	LCD_WR_DATA(0xDF); 	
	LCD_WR_REG(0x2B); 						
	LCD_WR_DATA(y>>8);LCD_WR_DATA(y&0XFF); 	//设置垂直坐标，高位在前	
	LCD_WR_DATA(0x01);   // 设置最大Y坐标为480
	LCD_WR_DATA(0xDF); 
} 

/*****************************************************************************************
*	函 数 名:	 RGB888_RGB565
*	入口参数:	 Color - 要设置的颜色
*	返 回 值: 无
*	函数功能: 设置画笔的颜色，用于显示字符、绘制图形等
*	说    明: 3.5寸的屏幕使用的颜色格式是16位的BGR565，为了方便使用，
*				    入口参数使用的是24位的RGB888颜色，然后再通过代码转换成16位色
						24位RGB888对应关系为 0x00(R 0~255)00(G 0~255)00(B 0~255)
******************************************************************************************/

uint16_t RGB888_RGB565(uint32_t Color)
{
	uint16_t Red_Value = 0, Green_Value = 0, Blue_Value = 0; //各个颜色通道的值
	
	Red_Value   = (uint16_t)((Color&0xF80000)>>8);		// 提取红色的值
	Green_Value = (uint16_t)((Color&0x00FC00)>>5);		// 提取绿色的值
	Blue_Value  = (uint16_t)((Color&0x0000F8)>>3);		// 提取蓝色的值
	
	return (uint16_t)(Red_Value | Green_Value | Blue_Value);		// 合成16位色，颜色格式BGR565
}

/*****************************************************************************************
*	函 数 名:	LCD_Clear
*	入口参数: color
*	返 回 值: 无
*	函数功能: 清除整个屏幕的显示
*	说    明: 清除后的颜色为color（RGB565）
******************************************************************************************/

void LCD_Clear(uint32_t color)
{
	uint32_t i = 0;
	
	TFT_LCD.BackColor=RGB888_RGB565(color);
	LCD_SetCursor(0,0);	// 设置起始坐标
	LCD_WR_REG(0X2C);		// 开始写入GRAM

	for(i=0;i<480*320;i++)	// 总共需要写入320*480个点，ILI9341会根据屏幕的分辨率自动换行显示
	{
		*(__IO uint16_t*) FSMC_DATA = TFT_LCD.BackColor;	// 写入背景色
	}
}

/*****************************************************************************************
*	函 数 名:	LCD_DisplayMode
*	入口参数: direction
*	返 回 值: 无
*	函数功能: 改变显示方向
*	说    明: 传入宏定义值Mode_H(横屏) Mode_V（竖屏）
******************************************************************************************/

void LCD_DisplayMode(uint8_t direction)
{
	TFT_LCD.Direction = direction;		// 修改全局变量，方向标志位
	
	if (TFT_LCD.Direction == Mode_H) 		// 横屏显示
	{
		LCD_WR_REG(0X36);		// 扫描方向设置寄存器
		LCD_WR_DATA(0X28); 	//	扫描方向，从上到下	，从右到左
		
		LCD_WR_REG(0x2A); 	
		LCD_WR_DATA(0x00);	// 设置x坐标（在这里没有作用，只是需要先写入而已）
		LCD_WR_DATA(0x00); 			
		LCD_WR_DATA(0x01);	// 设置最大x坐标为320
		LCD_WR_DATA(0XDF); 
			
		LCD_WR_REG(0x2B); 
		LCD_WR_DATA(0x00);	// 设置y坐标（在这里没有作用，只是需要先写入而已）
		LCD_WR_DATA(0x00); 		
		LCD_WR_DATA(0x01);	// 设置最大y坐标为240
		LCD_WR_DATA(0x3F); 		
		
		TFT_LCD.Width  = 480;		// 水平宽度320
		TFT_LCD.Height = 320;		// 垂直宽度240
	}
	else if(TFT_LCD.Direction == Mode_V)	// 竖屏显示
	{
		LCD_WR_REG(0X36);		// 扫描方向设置寄存器
		LCD_WR_DATA(0X48); 	//	扫描方向，从左到右，从上到下	
		
		LCD_WR_REG(0x2A); 	
		LCD_WR_DATA(0x00);	// 设置x坐标（在这里没有作用，只是需要先写入而已）
		LCD_WR_DATA(0x00); 			
		LCD_WR_DATA(0x01);   // 设置最大x坐标为240
		LCD_WR_DATA(0x3F); 				
                           
		LCD_WR_REG(0x2B);    
		LCD_WR_DATA(0x00);   // 设置y坐标（在这里没有作用，只是需要先写入而已）
		LCD_WR_DATA(0x00); 			
		LCD_WR_DATA(0x01);   // 设置最大y坐标为320
		LCD_WR_DATA(0XDF); 			
		                     
		TFT_LCD.Width  = 320;    // 水平宽度240
		TFT_LCD.Height = 480;		// 垂直宽度320
	}
}

/*****************************************************************************************
*	函 数 名:	 LCD_DrawPoint
*	入口参数:	 x - 水平坐标
*			  	   y - 垂直坐标
*				     color - 要显示的颜色
*	返 回 值: 无
*	函数功能: 在制定坐标处绘制指定颜色的点
*	说    明: 无
******************************************************************************************/

void LCD_DrawPoint(uint16_t x,uint16_t y,uint32_t color)
{
	TFT_LCD.PenColor=RGB888_RGB565(color);
	LCD_SetCursor(x,y);	// 设置坐标
	LCD_WR_REG(0X2C);		// 写入GRAM
	*(__IO uint16_t*) FSMC_DATA = TFT_LCD.PenColor; 	// 写入颜色
}

/*****************************************************************************************
*	函 数 名:	 show_photo
*	入口参数:	 x,y-----显示起始坐标
*				     px,py---图片像素大小
						 *photo--图片数组指针(BGR565格式)
*	返 回 值: 无
*	函数功能: 在指定位置显示指定大小图片
*	说    明: 无
******************************************************************************************/

void show_photo(uint16_t x,uint16_t y,uint16_t px,uint16_t py,const uint16_t *photo)
{
	uint16_t i=0,j=0,m=0;
	LCD_SetCursor(x,y);	// 设置写起始坐标
	LCD_WR_REG(0X2C);		// 写入GRAM
	for(i=0;i<py;i++)
	{
		if(i>=480-y) break;  //防止写数据坐标超过480
		for(j=0;j<px;j++)
		{
			if(j>=320-x) break;  //防止写数据坐标超过320
			*(__IO uint16_t*) FSMC_DATA = photo[i*px+j]; 	// 写入颜色
		}
		if(j<320)
		{
			for(m=0;m<320-j-x;m++)
			{
				*(__IO uint16_t*) FSMC_DATA = TFT_LCD.BackColor; 	// 写入颜色
			}
		}
	}
	
}










