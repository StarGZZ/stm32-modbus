#ifndef _key_H
#define _key_H
#include "stm32f0xx.h"
#define K1 GPIO_Pin_15 //PA15
#define K2 GPIO_Pin_3 //PB3
#define K3 GPIO_Pin_4 //PB4
#define K4 GPIO_Pin_5 //PB5
#define K_ALL GPIO_Pin_6 //PB5

#define ON  RESET
#define OFF SET


void KEY_Init(void);

#define K1_State GPIO_ReadInputDataBit(GPIOA,K1)
#define K2_State GPIO_ReadInputDataBit(GPIOB,K2)
#define K3_State GPIO_ReadInputDataBit(GPIOB,K3)
#define K4_State GPIO_ReadInputDataBit(GPIOB,K4)
#define K_ALL_State GPIO_ReadInputDataBit(GPIOB,K_ALL)

#endif
