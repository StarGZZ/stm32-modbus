#include "key.h"

/*******************************************************************************
* 函 数 名         : key_init
* 函数功能		   : 按键端口初始化函数	   
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void KEY_Init(void)	   //
{
	GPIO_InitTypeDef GPIO_InitStructure;	  //声明一个结构体变量，用来初始化GPIO

	/* 开启GPIO时钟 */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA |RCC_AHBPeriph_GPIOB, ENABLE);

	/*  配置GPIO的模式和IO口 */
  GPIO_InitStructure.GPIO_Pin = K1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = K2|K3|K4|K_ALL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}
