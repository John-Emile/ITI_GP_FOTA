/*
 * HEX_PARSE.c
 *
 *  Created on: Sep 28, 2023
 *      Author: mayke
 */

#include "../include/LIB/Bit_Math.h"
#include "../include/LIB/STD_TYPES.h"


#include <App/HEX_Parser/HEX_PARSE.h>
#include <MCAL/FLASH/FLASH_Interface.h>

u32 FLASH_ADDRESS = 0x08000000;

u16 DataBUF[100];
u8 APARSER_ParseAscii2Hex(u8 Copy_u8Ascii)
{
	u8 HEX_Value=0;
	if(Copy_u8Ascii>=48 &&Copy_u8Ascii<=57)
	{
		HEX_Value=Copy_u8Ascii-48;
	}
	else if(Copy_u8Ascii>='A'&&Copy_u8Ascii<='F')
	{
		HEX_Value=Copy_u8Ascii-55;
	}
	return HEX_Value;
}

void APARSER_voidParseRecord(u8*Copy_BufRecord)
{
	switch(Copy_BufRecord[8])
	{
	case'0' : APAESER_voidParseData(Copy_BufRecord);
	break;
	case '4':/*set high address part*/break;
	case '1'://end of file
		break;
	}
}

void APAESER_voidParseData(u8 *Copy_u8BufData)
{
	u8 CC_High,CC_Low,CC;
	u8 digit0,digit1,digit2,digit3;

	//convert count character
	CC_High=APARSER_ParseAscii2Hex(Copy_u8BufData[1]);
	CC_Low=APARSER_ParseAscii2Hex(Copy_u8BufData[2]);
	CC=(CC_High<<4)|CC_Low;
	//convert address
	digit0=APARSER_ParseAscii2Hex(Copy_u8BufData[3]);
	digit1=APARSER_ParseAscii2Hex(Copy_u8BufData[4]);
	digit2=APARSER_ParseAscii2Hex(Copy_u8BufData[5]);
	digit3=APARSER_ParseAscii2Hex(Copy_u8BufData[6]);
	FLASH_ADDRESS&=0xFFFF0000;
	FLASH_ADDRESS|=(digit0<<12)|(digit1<<8)|(digit2<<4)|(digit3<<0);
	//data
	for(u8 i=0;i<(CC/2);i++)
	{
		digit0=APARSER_ParseAscii2Hex(Copy_u8BufData[(4*i)+9] );
		digit1=APARSER_ParseAscii2Hex(Copy_u8BufData[(4*i)+10]);
		digit2=APARSER_ParseAscii2Hex(Copy_u8BufData[(4*i)+11]);
		digit3=APARSER_ParseAscii2Hex(Copy_u8BufData[(4*i)+12]);
		DataBUF[i]=(digit2<<12)|(digit3<<8)|(digit0<<4)|(digit1<<0);

	}
	MFDI_voidFlashWrite((FLASH_ADDRESS+0x00004000),DataBUF,(CC/2));
}

void APAESER_voidMoveData(u32 _sourceAddress,u32 _DestinationAddress, u16 _dataLength)
{
	u16 ReadBuff;
	u16 L_u8iterator=0;

	for(L_u8iterator=0 ; L_u8iterator< _dataLength ; L_u8iterator++)
	{
		MFDI_ReadBuffer(_sourceAddress,&ReadBuff,1);
		MFDI_voidFlashWrite(_DestinationAddress,&ReadBuff,1);

		_sourceAddress+=2;
		_DestinationAddress+=2;
	}
}
