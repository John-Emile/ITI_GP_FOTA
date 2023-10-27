/*
 * HexParser.c
 *
 *  Created on: Sep 11, 2023
 *      Author: adham
 */
/*************************************Includes*********************************/
#include <LIB/STD_Types.h>
#include <LIB/BIT_MATH.h>
#include <App/HEXPARSER/HexParser.h>
#include <MCAL/Fls/Fls_interface.h>
/******************************************************************************/

u32 FLASH_BASE_ADDR= 0x08004000 ;
u32 address = 0x08000000 ;
u16 DataBuffer[100] ;

void HexParser_vEraseAppArea(void)
{
	Fls_earseAppArea();
}

static u8 HexParser_u8Ascii2Hex(u8 A_u8Ascii)
{

	u8 L_u8HexValue = 0;

	if(A_u8Ascii >= '0' && A_u8Ascii <= '9')
	{
		L_u8HexValue = A_u8Ascii - '0' ;
	}
	else if(A_u8Ascii >= 'A' && A_u8Ascii <='F')
	{
		L_u8HexValue = A_u8Ascii - 55 ; // 55='A'-10
	}
	return L_u8HexValue;
}


void HexParser_vParseData(u8 A_pu8Data[])
{
		u8 CC_High,CC_Low,CC;
		u8 digit0,digit1,digit2,digit3;

		//convert count character
		CC_High=HexParser_u8Ascii2Hex(A_pu8Data[1]);
		CC_Low=HexParser_u8Ascii2Hex(A_pu8Data[2]);
		CC=(CC_High<<4)|CC_Low;
		//convert address
		digit0=HexParser_u8Ascii2Hex(A_pu8Data[3]);
		digit1=HexParser_u8Ascii2Hex(A_pu8Data[4]);
		digit2=HexParser_u8Ascii2Hex(A_pu8Data[5]);
		digit3=HexParser_u8Ascii2Hex(A_pu8Data[6]);
		FLASH_BASE_ADDR&=0xFFFF0000;
		FLASH_BASE_ADDR|=(digit0<<12)|(digit1<<8)|(digit2<<4)|(digit3<<0);
		//data
		for(u8 i=0;i<(CC/2);i++)
		{
			digit0=HexParser_u8Ascii2Hex(A_pu8Data[(4*i)+9] );
			digit1=HexParser_u8Ascii2Hex(A_pu8Data[(4*i)+10]);
			digit2=HexParser_u8Ascii2Hex(A_pu8Data[(4*i)+11]);
			digit3=HexParser_u8Ascii2Hex(A_pu8Data[(4*i)+12]);
			DataBuffer[i]=(digit2<<12)|(digit3<<8)|(digit0<<4)|(digit1<<0);

		}
		Fls_write(FLASH_BASE_ADDR,DataBuffer,(CC/2));
}



