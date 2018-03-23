#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f0xx.h"

void Systick_Init(void);
void delay_ms(__IO uint32_t nTime);
void TimingDelay_Decrement(void);

typedef struct
{
	u16 cnt_1ms;
	u16 cnt_2ms;
	u16 cnt_5ms;
	u16 cnt_10ms;
	u16 cnt_20ms;
	u16 cnt_30ms;
	u16 cnt_50ms;
	u16 cnt_100ms;
	u16 cnt_200ms;
	u16 cnt_500ms;
	u16 cnt_800ms;
	u16 cnt_1s;
	u16 cnt_s;
	u16 cnt_3s;
	u16 cnt_1min;
}TimeSlice_t;
#endif /* __SYSTICK_H */
