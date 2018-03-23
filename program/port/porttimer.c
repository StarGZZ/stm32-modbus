/*
 * FreeModbus Libary: BARE Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: porttimer.c,v 1.1 2006/08/22 21:35:13 wolti Exp $
 */

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
#include "stm32_hal_legacy.h"
#include "tim.h"

/* ----------------------- static functions ---------------------------------*/
static void prvvTIMERExpiredISR( void );
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
//extern TIM_HandleTypeDef htim3;
/* ----------------------- Start implementation -----------------------------*/

BOOL
xMBPortTimersInit(USHORT usTim1Timerout50us )
{
	MX_TIM3_Init();
	return TRUE;;
}


void vMBPortTimersEnable(  )
{
    /* Enable the timer with the timeout passed to xMBPortTimersInit( ) */
	__HAL_TIM_CLEAR_IT(&htim3,TIM_IT_UPDATE);
  __HAL_TIM_SetCounter(&htim3,0);
  /* 在中断模式下启动定时器 */
  HAL_TIM_Base_Start_IT(&htim3);
}

void vMBPortTimersDisable(  )
{
  /* Disable any pending timers. */
  HAL_TIM_Base_Stop_IT(&htim3);
  
  __HAL_TIM_SetCounter(&htim3,0);
  __HAL_TIM_CLEAR_IT(&htim3,TIM_IT_UPDATE); 
}

/* Create an ISR which is called whenever the timer has expired. This function
 * must then call pxMBPortCBTimerExpired( ) to notify the protocol stack that
 * the timer has expired.
 */
static void prvvTIMERExpiredISR( void )
{
    ( void )pxMBPortCBTimerExpired(  );
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  prvvTIMERExpiredISR();
}


