#ifndef __LED_H
#define	__LED_H

#include "stm32f0xx.h"

#define GPIO_Pin_LED_1 GPIO_Pin_0 
#define GPIO_Pin_LED_2 GPIO_Pin_1 
#define GPIO_Pin_LED_3 GPIO_Pin_2 
#define GPIO_Pin_LED_4 GPIO_Pin_3 

#define LED1_ON  GPIO_SetBits(GPIOA,GPIO_Pin_LED_1)
#define LED1_OFF GPIO_ResetBits(GPIOA,GPIO_Pin_LED_1)
#define LED2_ON  GPIO_SetBits(GPIOA,GPIO_Pin_LED_2)
#define LED2_OFF GPIO_ResetBits(GPIOA,GPIO_Pin_LED_2)
#define LED3_ON  GPIO_SetBits(GPIOA,GPIO_Pin_LED_3)
#define LED3_OFF GPIO_ResetBits(GPIOA,GPIO_Pin_LED_3)
#define LED4_ON  GPIO_SetBits(GPIOA,GPIO_Pin_LED_4)
#define LED4_OFF GPIO_ResetBits(GPIOA,GPIO_Pin_LED_4)

//#define LED1_State GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_LED_1)
//#define LED2_State GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_LED_2)
//#define LED3_State GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_LED_3)
//#define LED4_State GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_LED_4)

void	LED_Init(void);


#endif /* __LED_H */

