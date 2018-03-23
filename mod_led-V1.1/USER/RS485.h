#ifndef __RS485_H
#define	__RS485_H

#include "stm32f0xx.h"

#define GPIO_Pin_RS485 GPIO_Pin_8

#define RS485_DE()  GPIO_SetBits(GPIOA,GPIO_Pin_RS485)
#define RS485_RE()  GPIO_ResetBits(GPIOA,GPIO_Pin_RS485)


void	RS485_Init(void);


#endif /* __LED_H */

