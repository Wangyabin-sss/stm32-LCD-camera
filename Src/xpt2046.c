#include "xpt2046.h"


static const uint8_t count = 12; //采集次数
uint16_t x_data[count], y_data[count];

void spi_send8(uint8_t data)
{
	HAL_SPI_Transmit(&hspi1,&data,1,1000);
}

uint8_t spi_receive8(void)
{
  uint8_t data;
  HAL_SPI_Receive(&hspi1, &data, 1, 1000);
  return data;
}

void XPT2046_data(void)
{
	uint8_t i=0;
	uint16_t x=0,y=0;
	
  CS_L; //片选
	for (i = 0; i < count; i++)
  {
    spi_send8(0xd0); //发送命令
    x = spi_receive8();
    x <<= 8;
    x |= spi_receive8();
    x >>= 4;
    x_data[i] = x;
		printf("%d ",x_data[i]);
	}
	printf("\n");
	for (i = 0; i < count; i++)
	{
    spi_send8(0x90);
    y = spi_receive8();
    y <<= 8;
    y |= spi_receive8();
    y >>= 4;
    y_data[i] = y;
		printf("%d ",y_data[i]);
  }
	printf("\n");
	
	CS_H;
	
}




