/*==============================
**
*
*
**
===============================*/
/* Includes -------------------*/
#include "stm32f0xx.h"
#include "mb.h"
#include "systick.h"
#include "stdbool.h"
#include "led.h"
#include "key.h"
#include "rs485.h"
#include "dial_switch.h"

volatile u32 Timer1;	
extern u16 usRegHoldingBuf[7];

//extern BOOL Send_over(void);

TimeSlice_t timeslice;

u8 Modbus_Mac;
u16 Channel_1 = 0, 
    Channel_2 = 0, 
		Channel_3 = 0, 
		Channel_4 = 0;

bool IS_K1_ON = false;
bool IS_K2_ON = false;
bool IS_K3_ON = false;
bool IS_K4_ON = false;
bool IS_K_ALL_ON = false;
bool IS_K1_Rele = true;
bool IS_K2_Rele = true;
bool IS_K3_Rele = true;
bool IS_K4_Rele = true;
bool IS_K_ALL_Rele = true;
bool IS_LED1_ON = false;
bool IS_LED2_ON = false;
bool IS_LED3_ON = false;
bool IS_LED4_ON = false;
bool IS_LED_ALL_ON = false;
bool IS_MAC_Change = false;

void Buf_Data_Mange(void);
void KEY_Mange(void);  

int main(void)
{
	SystemInit();
	Systick_Init();
	LED_Init();
	KEY_Init();
	RS485_Init();
	Dial_switch_Init();
	
	Modbus_Mac = Get_Mac();
	usRegHoldingBuf[0] = Modbus_Mac;
	eMBInit(MB_RTU, Modbus_Mac, 0, 9600, MB_PAR_NONE);//初始化 FreeModbus 为RTU模式 从机地址为Modbus_Mac Uart1 9600 无校验
	eMBEnable();								//启动   FreeModbus 

	while(1)
	{
	 KEY_Mange();	           // 不断判断按键    
	 eMBPoll();							   //不断的解析协议栈
	 Modbus_Mac = Get_Mac();	
	 Buf_Data_Mange();	
	}
} 

void Buf_Data_Mange(void)           //对HOLDING寄存器的数据进行处理
{
		if(timeslice.cnt_10ms == 0 && IS_MAC_Change)
	{
		eMBInit(MB_RTU, Modbus_Mac, 0, 9600, MB_PAR_NONE);
		eMBEnable();	
		IS_MAC_Change = false;
	}
	if(Modbus_Mac != usRegHoldingBuf[0])
	{ 
		IS_MAC_Change = true;
		timeslice.cnt_10ms = 10;
    usRegHoldingBuf[0] = Modbus_Mac;		 
	}
  else if(usRegHoldingBuf[1] == 0)
	{
		usRegHoldingBuf[1] = 1;
		usRegHoldingBuf[3] = 0;
		usRegHoldingBuf[4] = 0;
		usRegHoldingBuf[5] = 0;
		usRegHoldingBuf[6] = 0;
	  LED1_OFF;
		LED2_OFF;
		LED3_OFF;
		LED4_OFF;
	}
	else if(usRegHoldingBuf[2] == 1)
	{
    usRegHoldingBuf[2] = 0;
		usRegHoldingBuf[3] = 1;
		usRegHoldingBuf[4] = 1;
		usRegHoldingBuf[5] = 1;
		usRegHoldingBuf[6] = 1;
		LED1_ON;
		LED2_ON;
		LED3_ON;
		LED4_ON;
	}
	else if(Channel_1 != usRegHoldingBuf[3])
	{
		Channel_1 = usRegHoldingBuf[3];
	  if(usRegHoldingBuf[3] == 0)
	  {
			usRegHoldingBuf[1] = 1;
			usRegHoldingBuf[2] = 0;
			LED1_OFF;
	  }
		else if(usRegHoldingBuf[3] == 1)
		{
			usRegHoldingBuf[1] = 1;
			usRegHoldingBuf[2] = 0;
			LED1_ON;
	  }
	}
	else if(Channel_2 != usRegHoldingBuf[4])
	{
		Channel_2 = usRegHoldingBuf[4];
		if(usRegHoldingBuf[4] == 0)
		{
			usRegHoldingBuf[1] = 1;
			usRegHoldingBuf[2] = 0;
			LED2_OFF;
		}
		else if(usRegHoldingBuf[4] == 1)
		{
			usRegHoldingBuf[1] = 1;
			usRegHoldingBuf[2] = 0;
			LED2_ON;
		}	
	}
	else if(Channel_3 != usRegHoldingBuf[5])
	{
		Channel_3 = usRegHoldingBuf[5];
		if(usRegHoldingBuf[5] == 0)
		{
			usRegHoldingBuf[1] = 1;
			usRegHoldingBuf[2] = 0;
			LED3_OFF;
		}
		else if(usRegHoldingBuf[5] == 1)
		{
			usRegHoldingBuf[1] = 1;
			usRegHoldingBuf[2] = 0;
			LED3_ON;
		}
	}
	else if(Channel_4 != usRegHoldingBuf[6])
	{		
		Channel_4 = usRegHoldingBuf[6];
		if(usRegHoldingBuf[6] == 0)
		{
			usRegHoldingBuf[1] = 1;
			usRegHoldingBuf[2] = 0;
			LED4_OFF;		
		}
		else if(usRegHoldingBuf[6] == 1)
		{
			usRegHoldingBuf[1] = 1;
			usRegHoldingBuf[2] = 0;
			LED4_ON;
		}	
	}
}

void KEY_Mange(void)
{
  if(K1_State == ON)
	{ 
		if(IS_K1_ON)
		{
	    if(K1_State == ON && timeslice.cnt_5ms == 0 && IS_K1_Rele)
			{
			  IS_LED1_ON =! IS_LED1_ON;
				if(IS_LED1_ON)
				  usRegHoldingBuf[3] = 1;
				else
					usRegHoldingBuf[3] = 0;
				IS_K1_Rele = false;
			}
		}
		else
		{
			IS_K1_ON = true;
		  timeslice.cnt_5ms = 5;
		}
	}
	else 
	{
		IS_K1_ON = false;
		IS_K1_Rele = true;
	}

  if(K2_State == ON)
	{ 
		if(IS_K2_ON)
		{
	    if(K2_State == ON && timeslice.cnt_5ms == 0 && IS_K2_Rele)
			{
			  IS_LED2_ON =! IS_LED2_ON;
				if(IS_LED2_ON)
				  usRegHoldingBuf[4] = 1;
				else
					usRegHoldingBuf[4] = 0;
				IS_K2_Rele = false;
			}
		}
		else
		{
			IS_K2_ON = true;
		  timeslice.cnt_5ms = 5;
		}
	}
	else 
	{
	  IS_K2_ON = false;
		IS_K2_Rele = true;
	}	
	
  if(K3_State == ON)
	{ 
		if(IS_K3_ON)
		{
	    if(K3_State == ON && timeslice.cnt_5ms == 0 && IS_K3_Rele)
			{
			  IS_LED3_ON =! IS_LED3_ON;
				if(IS_LED3_ON)
				  usRegHoldingBuf[5] = 1;
				else
					usRegHoldingBuf[5] = 0;
				IS_K3_Rele = false;
			}
		}
		else
		{
			IS_K3_ON = true;
		  timeslice.cnt_5ms = 5;
		}
	}
	else 
	{
	  IS_K3_ON = false;
		IS_K3_Rele = true;
	}	

  if(K4_State == ON)
	{ 
		if(IS_K4_ON)
		{
	    if(K4_State == ON && timeslice.cnt_5ms == 0 && IS_K4_Rele)
			{
			  IS_LED4_ON =! IS_LED4_ON;
				if(IS_LED4_ON)
				  usRegHoldingBuf[6] = 1;
				else
					usRegHoldingBuf[6] = 0;
				IS_K4_Rele = false;
			}
		}
		else
		{
			IS_K4_ON = true;
		  timeslice.cnt_5ms = 5;
		}
	}
	else 
	{
	  IS_K4_ON = false;
		IS_K4_Rele = true;
	}		
	
  if(K_ALL_State == ON)
	{ 
		if(IS_K_ALL_ON)
		{
	    if(K_ALL_State == ON && timeslice.cnt_5ms == 0 && IS_K_ALL_Rele)
			{
			  IS_LED_ALL_ON =! IS_LED_ALL_ON;
				if(IS_LED_ALL_ON)
				  usRegHoldingBuf[2] = 1;
				else
					usRegHoldingBuf[1] = 0;
				IS_K_ALL_Rele = false;
			}
		}
		else
		{
			IS_K_ALL_ON = true;
		  timeslice.cnt_5ms = 5;
		}
	}
	else 
	{
	  IS_K_ALL_ON = false;
		IS_K_ALL_Rele = true;
	}			
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
