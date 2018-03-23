#include "dial_switch.h"

/*******************************************************************************
* 函 数 名         : key_init
* 函数功能		   : 按键端口初始化函数	   
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void Dial_switch_Init(void)	   //
{
	GPIO_InitTypeDef GPIO_InitStructure;	  //声明一个结构体变量，用来初始化GPIO

	/* 开启GPIO时钟 */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA |RCC_AHBPeriph_GPIOB, ENABLE);

	/*  配置GPIO的模式和IO口 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

u8 Get_Mac(void)
{
	u8 mac_b,mac_a,mac;
	mac_a = ~GPIO_ReadInputData(GPIOA) & 0xF0;
  mac_b = ~GPIO_ReadInputData(GPIOB) & 0x03;
	mac = (mac_b << 4) | (mac_a >> 4);
	return mac;
}







