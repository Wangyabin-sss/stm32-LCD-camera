#include "sccb.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ο�������guanfu_wang���롣
//ALIENTEK STM32F103������ 
//SCCB ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/4/16
//�汾��V1.0		    							    							  
//////////////////////////////////////////////////////////////////////////////////
 
//��ʼ��SCCB�ӿ�
//CHECK OK
void SCCB_Init(void)
{						
 	
}			 

//SCCB��ʼ�ź�
//��ʱ��Ϊ�ߵ�ʱ��,�����ߵĸߵ���,ΪSCCB��ʼ�ź�
//�ڼ���״̬��,SDA��SCL��Ϊ�͵�ƽ
void SCCB_Start(void)
{
    
}

//SCCBֹͣ�ź�
//��ʱ��Ϊ�ߵ�ʱ��,�����ߵĵ͵���,ΪSCCBֹͣ�ź�
//����״����,SDA,SCL��Ϊ�ߵ�ƽ
void SCCB_Stop(void)
{
    
}  
//����NA�ź�
void SCCB_No_Ack(void)
{
	
}
//SCCB,д��һ���ֽ�
//����ֵ:0,�ɹ�;1,ʧ��. 
uint8_t SCCB_WR_Byte(uint8_t dat)
{
	
}	 
//SCCB ��ȡһ���ֽ�
//��SCL��������,��������
//����ֵ:����������
uint8_t SCCB_RD_Byte(void)
{
	
} 							    
//д�Ĵ���
//����ֵ:0,�ɹ�;1,ʧ��.
uint8_t SCCB_WR_Reg(uint8_t reg,uint8_t data)
{
	
}		  					    
//���Ĵ���
//����ֵ:�����ļĴ���ֵ
uint8_t SCCB_RD_Reg(uint8_t reg)
{
	
}















