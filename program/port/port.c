/***************************************************************
*
*
*
*
FreeModbus 通过 
eMBRegInputCB eMBRegHoldingCB 
eMBRegCoilsCB	eMBRegDiscreteCB 四个接口函数完成数据的读写操作 
**************************************************************/
#include "stm32f1xx.h"
#include "mb.h" 
#include "mbutils.h" 

//uint16_t usRegInputBuf[10]={0x0000,0xfe02,0x1203,0x1304,0x1405,0x1506,0x1607,0x1708,0x1809};
uint8_t ucRegCoilsBuf[10]={0xff,0,1,1,1,1,1,1,1,1};
uint16_t usRegInputBuf[10]={0,1,2,3,4,5,6,7,8,9};
uint16_t usRegHoldingBuf[7]={3,1,0,0,0,0,0};
//Rx:285-01 03 0E 00 03 00 01 00 00 00 00 00 00 00 00 00 05 2E 29



uint8_t REG_INPUT_START=0,REG_HOLDING_START=0,REG_COILS_START=0;
uint8_t REG_INPUT_NREGS=10,REG_HOLDING_NREGS=10,REG_COILS_NREGS=10;
uint8_t usRegInputStart=0,usRegHoldingStart=0,usRegCoilsStart=0;

//读数字寄存器 功能码0x04

eMBErrorCode
eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
	eMBErrorCode    eStatus = MB_ENOERR;
	int             iRegIndex;

    if( ( usAddress-1 >= REG_INPUT_START )&& ( usAddress-1 + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
    {
        iRegIndex = ( int )( usAddress-1 - usRegInputStart );
        while( usNRegs > 0 )
        {
            *pucRegBuffer++ =
                ( unsigned char )( usRegInputBuf[iRegIndex] >> 8 );
            *pucRegBuffer++ =
                ( unsigned char )( usRegInputBuf[iRegIndex] & 0xFF );
            iRegIndex++;
            usNRegs--;
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }

    return eStatus;
}

// 寄存器的读写函数 支持的命令为读 0x03 和写0x06

eMBErrorCode
eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    int             iRegIndex;
    if( ( usAddress-1 >= REG_HOLDING_START ) && ( usAddress-1 + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS ) )
    {
        iRegIndex = ( int )( usAddress-1 - usRegHoldingStart );
        switch ( eMode )
        {
        case MB_REG_READ:
            while( usNRegs > 0 )
            {
 				      *pucRegBuffer++ = ( unsigned char )( usRegHoldingBuf[iRegIndex] >> 8 );
              *pucRegBuffer++ = ( unsigned char )( usRegHoldingBuf[iRegIndex] & 0xFF );
			        	iRegIndex++;
                usNRegs--;
            }
            break;

        case MB_REG_WRITE:
            while( usNRegs > 0 )
            {
				      usRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;
              usRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;
              iRegIndex++;
              usNRegs--;
            }
        }
    }
    else
    {
        eStatus = MB_ENOREG;
    }
    return eStatus;
}

//读开关寄存器 0x02
eMBErrorCode
eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
    ( void )pucRegBuffer;
    ( void )usAddress;
    ( void )usNDiscrete;
    return MB_ENOREG;
}


////读/写开关寄存器  0x01  x05
eMBErrorCode
eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils,
eMBRegisterMode eMode )
{
	eMBErrorCode eStatus = MB_ENOERR;
	int16_t iNCoils = ( int16_t )usNCoils;
	int16_t usBitOffset;

	if( ( (int16_t)usAddress-1 >= REG_COILS_START ) &&
	( usAddress-1 + usNCoils <= REG_COILS_START + REG_COILS_NREGS ) )
	{
		usBitOffset = ( int16_t )( usAddress-1 - REG_COILS_START );
		switch ( eMode )
		{
			case MB_REG_READ:
			while( iNCoils > 0 )
			{
				*pucRegBuffer++ = xMBUtilGetBits( ucRegCoilsBuf, usBitOffset,
				( uint8_t )( iNCoils > 8 ? 8 : iNCoils ) );
				iNCoils -= 8;
				usBitOffset += 8;
			}
				break;
				case MB_REG_WRITE:
			while( iNCoils > 0 )
			{
				xMBUtilSetBits( ucRegCoilsBuf, usBitOffset,
				( uint8_t )( iNCoils > 8 ? 8 : iNCoils ),
				*pucRegBuffer++ );
				iNCoils -= 8;
			}
			break;
		}
  }
	else
	{
	eStatus = MB_ENOREG;
	}
	return eStatus;
}


eMBErrorCode eMBRegFastHoldingCB(UCHAR ucLoop16_13, UCHAR ucLoop12_9,UCHAR ucLoop8_5,UCHAR ucLoop4_1)
{
	/***************************不同回路数的继电器修改这里即可************************/
	UCHAR i;
	for(i = 0;i < 4;i++)
	{
		if((ucLoop4_1 >> (i*2))&(1 << 0))/* 01B = 开 */
		{
			usRegHoldingBuf[i + 3] = 1;
		}
		else if((ucLoop4_1 >> (i*2))&(1 << 1))/* 10B = 关 */
		{
			usRegHoldingBuf[i + 3] = 0;
		}
		else/* 00B = 保持*/
		{
			/*不用处理*/
		}
	}
	return MB_ENOERR;
}



