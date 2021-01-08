#include "ili9488.h"

//LCD��ز����ṹ��
struct	
{
	uint16_t ID;        // ������ID	
	uint16_t Width;		  // ˮƽ�ֱ���
	uint16_t Height;		// ��ֱ�ֱ���
	uint16_t PenColor;  //	LCD��ǰ������ɫ
	uint16_t BackColor;		//����ɫ
	uint8_t  Direction;		//��ʾ����
	uint8_t  ShowNum_Mode;	// �������ģʽ
}TFT_LCD;


/*****************************************************************************************
*	�� �� ��: LCD_WR_REG
*	��ڲ���: reg - Ҫ�����ļĴ���
*	�� �� ֵ: ��
*	��������: ѡ��Ҫ�����ļĴ���
*	˵    ��: 
******************************************************************************************/

void LCD_WR_REG(uint16_t reg)
{   
	*(__IO uint16_t*) FSMC_REG = reg;	 
}

/*****************************************************************************************
*	�� �� ��: LCD_WR_DATA
*	��ڲ���: data - Ҫд�������
*	�� �� ֵ: ��
*	��������: ����Ӧ�ļĴ���д������
*	˵    ��: 
******************************************************************************************/

void LCD_WR_DATA(uint16_t data)
{	 
	*(__IO uint16_t*) FSMC_DATA = data;	
}

/*****************************************************************************************
*	�� �� ��: LCD_RD_DATA
*	��ڲ���: reg - Ҫ��ȡ�ļĴ���
*	�� �� ֵ: �ӸüĴ�����ȡ������ֵ
*	��������: ����Ӧ�ļĴ�����������
*	˵    ��: ��
******************************************************************************************/
uint16_t LCD_RD_DATA(void)
{
   uint16_t data;	
	data = *(__IO uint16_t*) FSMC_DATA;	
	return data;	 
}

/*****************************************************************************************
*	�� �� ��: LCD_Init
*	��ڲ���: ��
*	�� �� ֵ: ��
*	��������: ��ʼ��LCD������
*	˵    ��: ��Ҫ�ǲ���ILI9488����ؼĴ��������б�Ҫ�����ã�Ĭ��������ʾ
******************************************************************************************/

void LCD_Init(void)
{
  // ��λILI9488
	LCD_RST_L;	HAL_Delay(10); 	//��ʱ����̫С
	LCD_RST_H;	HAL_Delay(10); 

	//��ȡLCD��������ID��
	LCD_WR_REG(0XD3);	
  TFT_LCD.ID=LCD_RD_DATA();     //�ٶ�
	TFT_LCD.ID=LCD_RD_DATA();     //��0x00
	TFT_LCD.ID=LCD_RD_DATA();     //��0x94
	TFT_LCD.ID<<=8;               //0x94�����8λ
	TFT_LCD.ID|=LCD_RD_DATA();    //��0x88����ȡ����ID��
	printf(" LCD ID:ILI%x\r\n",TFT_LCD.ID);
	if(TFT_LCD.ID!=0x9488)while(1);	
	
   // ��ʼ��ILI9488
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
	
//	LCD_SetBackColor(LCD_BLACK); // ���ñ���ɫ
//	LCD_SetColor(LCD_WHITE);		// ���û�����ɫ
//	LCD_SetFont(&Font24);  			// ����Ĭ������
//	LCD_ShowNumMode(Fill_Space);	// �����������ģʽ
	LCD_DisplayMode(Mode_V);		// ������ʾ��������
	LCD_Clear(0xffffff);		// ����
	
	LCD_Backlight_ON;
}

/*****************************************************************************************
*	�� �� ��:	 LCD_SetCursor
*	��ڲ���:	 x - ˮƽ����
*			  	   y - ��ֱ����
*	�� �� ֵ: ��
*	��������: ������ĻҪ��ʾ���ݵ�����
*	˵    ��: 0x2A Ϊˮƽ����Ĵ�����ַ��0x2BΪ��ֱ����Ĵ�����ַ
******************************************************************************************/

void LCD_SetCursor(uint16_t x, uint16_t y)
{	   
   //ILI9488��������ʱ�����END����Ҳд��ȥ����ΪEND����ͨ����ȷ��������ֱ��д�������
	LCD_WR_REG(0x2A); 							
	LCD_WR_DATA(x>>8);LCD_WR_DATA(x&0XFF); 	//����ˮƽ���꣬��λ��ǰ	
	LCD_WR_DATA(0x01);   // �������X����Ϊ480
	LCD_WR_DATA(0xDF); 	
	LCD_WR_REG(0x2B); 						
	LCD_WR_DATA(y>>8);LCD_WR_DATA(y&0XFF); 	//���ô�ֱ���꣬��λ��ǰ	
	LCD_WR_DATA(0x01);   // �������Y����Ϊ480
	LCD_WR_DATA(0xDF); 
} 

/*****************************************************************************************
*	�� �� ��:	 RGB888_RGB565
*	��ڲ���:	 Color - Ҫ���õ���ɫ
*	�� �� ֵ: ��
*	��������: ���û��ʵ���ɫ��������ʾ�ַ�������ͼ�ε�
*	˵    ��: 3.5�����Ļʹ�õ���ɫ��ʽ��16λ��BGR565��Ϊ�˷���ʹ�ã�
*				    ��ڲ���ʹ�õ���24λ��RGB888��ɫ��Ȼ����ͨ������ת����16λɫ
						24λRGB888��Ӧ��ϵΪ 0x00(R 0~255)00(G 0~255)00(B 0~255)
******************************************************************************************/

uint16_t RGB888_RGB565(uint32_t Color)
{
	uint16_t Red_Value = 0, Green_Value = 0, Blue_Value = 0; //������ɫͨ����ֵ
	
	Red_Value   = (uint16_t)((Color&0xF80000)>>8);		// ��ȡ��ɫ��ֵ
	Green_Value = (uint16_t)((Color&0x00FC00)>>5);		// ��ȡ��ɫ��ֵ
	Blue_Value  = (uint16_t)((Color&0x0000F8)>>3);		// ��ȡ��ɫ��ֵ
	
	return (uint16_t)(Red_Value | Green_Value | Blue_Value);		// �ϳ�16λɫ����ɫ��ʽBGR565
}

/*****************************************************************************************
*	�� �� ��:	LCD_Clear
*	��ڲ���: color
*	�� �� ֵ: ��
*	��������: ���������Ļ����ʾ
*	˵    ��: ��������ɫΪcolor��RGB565��
******************************************************************************************/

void LCD_Clear(uint32_t color)
{
	uint32_t i = 0;
	
	TFT_LCD.BackColor=RGB888_RGB565(color);
	LCD_SetCursor(0,0);	// ������ʼ����
	LCD_WR_REG(0X2C);		// ��ʼд��GRAM

	for(i=0;i<480*320;i++)	// �ܹ���Ҫд��320*480���㣬ILI9341�������Ļ�ķֱ����Զ�������ʾ
	{
		*(__IO uint16_t*) FSMC_DATA = TFT_LCD.BackColor;	// д�뱳��ɫ
	}
}

/*****************************************************************************************
*	�� �� ��:	LCD_DisplayMode
*	��ڲ���: direction
*	�� �� ֵ: ��
*	��������: �ı���ʾ����
*	˵    ��: ����궨��ֵMode_H(����) Mode_V��������
******************************************************************************************/

void LCD_DisplayMode(uint8_t direction)
{
	TFT_LCD.Direction = direction;		// �޸�ȫ�ֱ����������־λ
	
	if (TFT_LCD.Direction == Mode_H) 		// ������ʾ
	{
		LCD_WR_REG(0X36);		// ɨ�跽�����üĴ���
		LCD_WR_DATA(0X28); 	//	ɨ�跽�򣬴��ϵ���	�����ҵ���
		
		LCD_WR_REG(0x2A); 	
		LCD_WR_DATA(0x00);	// ����x���꣨������û�����ã�ֻ����Ҫ��д����ѣ�
		LCD_WR_DATA(0x00); 			
		LCD_WR_DATA(0x01);	// �������x����Ϊ320
		LCD_WR_DATA(0XDF); 
			
		LCD_WR_REG(0x2B); 
		LCD_WR_DATA(0x00);	// ����y���꣨������û�����ã�ֻ����Ҫ��д����ѣ�
		LCD_WR_DATA(0x00); 		
		LCD_WR_DATA(0x01);	// �������y����Ϊ240
		LCD_WR_DATA(0x3F); 		
		
		TFT_LCD.Width  = 480;		// ˮƽ���320
		TFT_LCD.Height = 320;		// ��ֱ���240
	}
	else if(TFT_LCD.Direction == Mode_V)	// ������ʾ
	{
		LCD_WR_REG(0X36);		// ɨ�跽�����üĴ���
		LCD_WR_DATA(0X48); 	//	ɨ�跽�򣬴����ң����ϵ���	
		
		LCD_WR_REG(0x2A); 	
		LCD_WR_DATA(0x00);	// ����x���꣨������û�����ã�ֻ����Ҫ��д����ѣ�
		LCD_WR_DATA(0x00); 			
		LCD_WR_DATA(0x01);   // �������x����Ϊ240
		LCD_WR_DATA(0x3F); 				
                           
		LCD_WR_REG(0x2B);    
		LCD_WR_DATA(0x00);   // ����y���꣨������û�����ã�ֻ����Ҫ��д����ѣ�
		LCD_WR_DATA(0x00); 			
		LCD_WR_DATA(0x01);   // �������y����Ϊ320
		LCD_WR_DATA(0XDF); 			
		                     
		TFT_LCD.Width  = 320;    // ˮƽ���240
		TFT_LCD.Height = 480;		// ��ֱ���320
	}
}

/*****************************************************************************************
*	�� �� ��:	 LCD_DrawPoint
*	��ڲ���:	 x - ˮƽ����
*			  	   y - ��ֱ����
*				     color - Ҫ��ʾ����ɫ
*	�� �� ֵ: ��
*	��������: ���ƶ����괦����ָ����ɫ�ĵ�
*	˵    ��: ��
******************************************************************************************/

void LCD_DrawPoint(uint16_t x,uint16_t y,uint32_t color)
{
	TFT_LCD.PenColor=RGB888_RGB565(color);
	LCD_SetCursor(x,y);	// ��������
	LCD_WR_REG(0X2C);		// д��GRAM
	*(__IO uint16_t*) FSMC_DATA = TFT_LCD.PenColor; 	// д����ɫ
}

/*****************************************************************************************
*	�� �� ��:	 show_photo
*	��ڲ���:	 x,y-----��ʾ��ʼ����
*				     px,py---ͼƬ���ش�С
						 *photo--ͼƬ����ָ��(BGR565��ʽ)
*	�� �� ֵ: ��
*	��������: ��ָ��λ����ʾָ����СͼƬ
*	˵    ��: ��
******************************************************************************************/

void show_photo(uint16_t x,uint16_t y,uint16_t px,uint16_t py,const uint16_t *photo)
{
	uint16_t i=0,j=0,m=0;
	LCD_SetCursor(x,y);	// ����д��ʼ����
	LCD_WR_REG(0X2C);		// д��GRAM
	for(i=0;i<py;i++)
	{
		if(i>=480-y) break;  //��ֹд�������곬��480
		for(j=0;j<px;j++)
		{
			if(j>=320-x) break;  //��ֹд�������곬��320
			*(__IO uint16_t*) FSMC_DATA = photo[i*px+j]; 	// д����ɫ
		}
		if(j<320)
		{
			for(m=0;m<320-j-x;m++)
			{
				*(__IO uint16_t*) FSMC_DATA = TFT_LCD.BackColor; 	// д����ɫ
			}
		}
	}
	
}










