#include "sccb.h"

 
//��ʼ��SCCB�ӿ�
//CHECK OK
void SCCB_Init(void)
{						
 	GPIO_InitTypeDef GPIO_InitStruct = {0};
	//ʱ������gpio.c�п���
	
	GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	SCCB_SCL(GPIO_PIN_SET);
	SCCB_SDA(GPIO_PIN_SET);
	
	SCCB_SDA_OUT();	
}			 

//void SCCB_SDA_OUT(void)
//{
//	GPIOA->MODER&=0XFFFFFFFC;   GPIOA->MODER|=0X00000001;  //����Ϊ���
////	GPIOA->OTYPER&=0XFFFFFF0F;  GPIOA->OTYPER|=0X00000080;
////	GPIOA->OSPEEDR&=0XFFFFFF0F; GPIOA->OSPEEDR|=0X00000080;
////	GPIOA->PUPDR&=0XFFFFFF0F;   GPIOA->PUPDR|=0X00000080;
//}
//void SCCB_SDA_IN(void)
//{
//	GPIOA->MODER&=0XFFFFFFFC;                              //����Ϊ����
////	GPIOA->OTYPER&=0XFFFFFF0F;  GPIOA->OTYPER|=0X00000001;
////	GPIOA->PUPDR&=0XFFFFFF0F;   GPIOA->PUPDR|=0X00000080;
//}

//SCCB��ʼ�ź�
//��ʱ��Ϊ�ߵ�ʱ��,�����ߵĸߵ���,ΪSCCB��ʼ�ź�
//�ڼ���״̬��,SDA��SCL��Ϊ�͵�ƽ
void SCCB_Start(void)
{
    SCCB_SDA(GPIO_PIN_SET);     //�����߸ߵ�ƽ	   
    SCCB_SCL(GPIO_PIN_SET);	    //��ʱ���߸ߵ�ʱ���������ɸ�����
    delay_us(50);  
    SCCB_SDA(GPIO_PIN_RESET);
    delay_us(50);	 
    SCCB_SCL(GPIO_PIN_RESET);	    //�����߻ָ��͵�ƽ��������������Ҫ	  
}

//SCCBֹͣ�ź�
//��ʱ��Ϊ�ߵ�ʱ��,�����ߵĵ͵���,ΪSCCBֹͣ�ź�
//����״����,SDA,SCL��Ϊ�ߵ�ƽ
void SCCB_Stop(void)
{
    SCCB_SDA(GPIO_PIN_RESET);
    delay_us(50);	 
    SCCB_SCL(GPIO_PIN_SET);	
    delay_us(50); 
    SCCB_SDA(GPIO_PIN_SET);	
    delay_us(50);
}  
//����NA�ź�
void SCCB_No_Ack(void)
{
	delay_us(50);
	SCCB_SDA(GPIO_PIN_SET);	
	SCCB_SCL(GPIO_PIN_SET);	
	delay_us(50);
	SCCB_SCL(GPIO_PIN_RESET);	
	delay_us(50);
	SCCB_SDA(GPIO_PIN_RESET);	
	delay_us(50);
}
//SCCB,д��һ���ֽ�
//����ֵ:0,�ɹ�;1,ʧ��. 
uint8_t SCCB_WR_Byte(uint8_t dat)
{
	uint8_t j,res;	 
	for(j=0;j<8;j++) //ѭ��8�η�������
	{
		if(dat&0x80) SCCB_SDA(GPIO_PIN_SET);	
		else SCCB_SDA(GPIO_PIN_RESET);
		dat<<=1;
		delay_us(50);
		SCCB_SCL(GPIO_PIN_SET);	
		delay_us(50);
		SCCB_SCL(GPIO_PIN_RESET);		   
	}			 
	SCCB_SDA_IN();		//����SDAΪ���� 
	delay_us(50);
	SCCB_SCL(GPIO_PIN_SET);			//���յھ�λ,���ж��Ƿ��ͳɹ�
	delay_us(50);
	if(SCCB_READ_SDA) res=1;  //SDA=1����ʧ�ܣ�����1
	else res=0;         //SDA=0���ͳɹ�������0
	SCCB_SCL(GPIO_PIN_RESET);		 
	SCCB_SDA_OUT();		//����SDAΪ���    
	return res;  
}	 
//SCCB ��ȡһ���ֽ�
//��SCL��������,��������
//����ֵ:����������
uint8_t SCCB_RD_Byte(void)
{
	uint8_t temp=0,j;    
	SCCB_SDA_IN();		//����SDAΪ����  
	for(j=8;j>0;j--) 	//ѭ��8�ν�������
	{		     	  
		delay_us(50);
		SCCB_SCL(GPIO_PIN_SET);
		temp=temp<<1;
		if(SCCB_READ_SDA)temp++;   
		delay_us(50);
		SCCB_SCL(GPIO_PIN_RESET);
	}	
	SCCB_SDA_OUT();		//����SDAΪ���    
	return temp;
} 							    
//д�Ĵ���
//����ֵ:0,�ɹ�;1,ʧ��.
uint8_t SCCB_WR_Reg(uint8_t reg,uint8_t data)
{
	uint8_t res=0;
	SCCB_Start(); 					//����SCCB����
	if(SCCB_WR_Byte(SCCB_ID))res=1;	//д����ID	  
	delay_us(100);
  if(SCCB_WR_Byte(reg))res=1;		//д�Ĵ�����ַ	  
	delay_us(100);
  if(SCCB_WR_Byte(data))res=1; 	//д����	 
  SCCB_Stop();	  
  return	res;
}		  					    
//���Ĵ���
//����ֵ:�����ļĴ���ֵ
uint8_t SCCB_RD_Reg(uint8_t reg)
{
	uint8_t val=0;
	SCCB_Start(); 				//����SCCB����
	SCCB_WR_Byte(SCCB_ID);		//д����ID	  
	delay_us(100);	 
  SCCB_WR_Byte(reg);			//д�Ĵ�����ַ	  
	delay_us(100);	  
	SCCB_Stop();   
	delay_us(100);	   
	//���üĴ�����ַ�󣬲��Ƕ�
	SCCB_Start();
	SCCB_WR_Byte(SCCB_ID|0X01);	//���Ͷ�����	  
	delay_us(100);
  val=SCCB_RD_Byte();		 	//��ȡ����
  SCCB_No_Ack();
  SCCB_Stop();
  return val;
}















