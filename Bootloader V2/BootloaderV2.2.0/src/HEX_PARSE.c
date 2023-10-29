/*************************************************************************************************************************************************************
 *
 * File Name: Hex_Parse.c
 *
 * Description: Program file for the hex file parser.
 *
 * Author: Abdulrahman El-Neshwy, Abdulrahman Khalaf, Aya Samir, Seba Ammar, Ziad Gomaa, John Emile
 *
 * Date : Sept 28, 2023
 *
 *************************************************************************************************************************************************************/

#include "../include/LIB/Bit_Math.h"
#include "../include/LIB/STD_TYPES.h"


#include <App/Hex Parser/HEX_PARSE.h>
#include <MCAL/Flash/FLASH_Interface.h>

/* Global unsigned integer variable that holds that start of flash address */
u32 FLASH_ADDRESS = 0x08020000;

/* Global unsigned array of character variable that holds that data parsed */
u16 DataBUF[100];


/************************************************************************************
 * Service Name: APARSER_ParseAscii2Hex
 * Parameters (in): uint8 (Holds the Ascii value)
 * Return value: uint8 (Holds the Hex value)
 * Description: Transform Ascii value to its corresponding Hex number.
 ************************************************************************************/

u8 APARSER_ParseAscii2Hex(u8 a_asciiValue)
{
	/* local variable that holds the returned value */
	u8 l_hexValue =0;

	/* Check if this Ascii value is equivalent to number from 0 to 9 */
	if((a_asciiValue>=48) && (a_asciiValue<=57))
	{
		/* ASCII value of zero to transform char number to actual like  '3' to 3 */
		l_hexValue = a_asciiValue - ASCII_VALUE_OF_ZERO;
	}

	/* Check if this Ascii value is char A to F */
	else if((a_asciiValue>='A') && (a_asciiValue<='F'))
	{
		/* 55 to transform A to 10, B to 11 and etc.. */
		l_hexValue = a_asciiValue - 55;
	}
	return l_hexValue;
}

/************************************************************************************
 * Service Name: APARSER_voidParseRecord
 * Parameters (in): uint8* (Holds pointer to buffer record)
 * Return value: None
 * Description: Parse the record.
 ************************************************************************************/

void APARSER_voidParseRecord(u8*Copy_BufRecord)
{
	/* Check on record type */
	switch(Copy_BufRecord[HEX_FRAME_RECORD_LOW_BYTE])
	{
	case HEX_RECORD_TYPE_IS_DATA :

		/* Start parsing the record */
		APAESER_voidParseData(Copy_BufRecord);
		break;

	case HEX_RECORD_TYPE_IS_HIGH_ADDRESS_RECORD:
		/*set high address part*/
		break;

	case HEX_RECORD_TYPE_IS_END_OF_FILE:
		/* End of file - Do nothing */
		break;

	default:
		/* Do nothing - defensive programming */
		break;
	}
}

/************************************************************************************
 * Service Name: APARSER_voidParseData
 * Parameters (in): uint8* (Holds pointer to buffer record)
 * Return value: None
 * Description: Parse the hex file.
 ************************************************************************************/

void APAESER_voidParseData(u8 *Copy_u8BufData)
{
	/* local variable to hold the character count high byte */
	u8 l_charCountHighByte = 0;

	/* local variable to hold the character count low byte */
	u8 l_charCountLowByte = 0;

	/* local variable to hold the character count */
	u8 l_charCount = 0;

	/* To hold the address value */
	u8 digit[4] = {};

	/*** Getting the character count ***/
	/* Get the high byte */
	l_charCountHighByte = APARSER_ParseAscii2Hex(Copy_u8BufData[HEX_FRAME_HIGH_BYTE_CHARACTER_COUNT]);

	/* Get the low byte */
	l_charCountLowByte = APARSER_ParseAscii2Hex(Copy_u8BufData[HEX_FRAME_LOW_BYTE_CHARACTER_COUNT]);

	/* Get the character count */
	l_charCount = (l_charCountHighByte << 4)| l_charCountLowByte;


	/*** Extracting the address ***/
	digit[0]=APARSER_ParseAscii2Hex(Copy_u8BufData[HEX_FRAME_FIRST_ADDRESS_BYTE]);
	digit[1]=APARSER_ParseAscii2Hex(Copy_u8BufData[HEX_FRAME_SECOND_ADDRESS_BYTE]);
	digit[2]=APARSER_ParseAscii2Hex(Copy_u8BufData[HEX_FRAME_THIRD_ADDRESS_BYTE]);
	digit[3]=APARSER_ParseAscii2Hex(Copy_u8BufData[HEX_FRAME_FOURTH_ADDRESS_BYTE]);

	/* Clear bits 15 down to 0 to insert low address */
	FLASH_ADDRESS &= 0xFFFF0000;

	/* Insert the low address into the least significant 4 bytes */
	FLASH_ADDRESS |= (digit[0]<<12) | (digit[1]<<8) | (digit[2]<<4) | (digit[3]<<0);


	/*** Extracting the data ***/

	/* Writes 2 bytes per time */
	for(u8 i=0;i<(l_charCount/2);i++)
	{
		/* Get the Most significant part of the first byte */
		digit[0]=APARSER_ParseAscii2Hex(Copy_u8BufData[(4*i)+ HEX_FRAME_DATA_FIRST_BYTE_UPPER_HALF] );

		/* Get the Least significant part of the first byte */
		digit[1]=APARSER_ParseAscii2Hex(Copy_u8BufData[(4*i)+ HEX_FRAME_DATA_FIRST_BYTE_LOWER_HALF]);

		/* Get the Most significant part of the second byte */
		digit[2]=APARSER_ParseAscii2Hex(Copy_u8BufData[(4*i)+ HEX_FRAME_DATA_SECOND_BYTE_UPPER_HALF]);

		/* Get the Least significant part of the second byte */
		digit[3]=APARSER_ParseAscii2Hex(Copy_u8BufData[(4*i)+ HEX_FRAME_DATA_SECOND_BYTE_LOWER_HALF]);

		/*
		 * Load the second byte then first byte using MSB first
		 * Example: FE BA should be loaded as BA FE
		 */
		DataBUF[i]=(digit[2]<<12)|(digit[3]<<8)|(digit[0]<<4)|(digit[1]<<0);

	}

	/* Write the data in the flash memory sector 1 */
	MFDI_voidFlashWrite((FLASH_ADDRESS-FLASH_SECTOR_ONE_OFFSET),DataBUF,(l_charCount/2));
}



