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


#include <App/HEX_Parser/HEX_PARSE.h>
#include <MCAL/FLASH/FLASH_Interface.h>

/* Global unsigned integer variable that holds that start of flash address */
u32 FLASH_ADDRESS = 0x08000000;

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
	MFDI_voidFlashWrite((FLASH_ADDRESS+FLASH_SECTOR_ONE_OFFSET),DataBUF,(l_charCount/2));
}


/****************************************************************************************
 * Service Name: APARSER_voidMoveData
 * Parameters (in): uint32 (Holds the source address)
 * 					uint32 (Holds the destination address)
 * 					uint16 (Holds the data length)
 * Return value: None
 * Description: Move data from a sector in flash memory to another sector in flash memory
 ****************************************************************************************/

void APAESER_voidMoveData(u32 a_sourceAddress,u32 a_DestinationAddress, u16 a_dataLength)
{

	/* local variable to hold the value of the buffer to read from memory */
	u16 l_readBuff;

	/* local variable used in for loop */
	u16 l_iterator=0;

	/* Loop until you finish given data length */
	for(l_iterator=0 ; l_iterator< a_dataLength ; l_iterator++)
	{
		/* Read from source address in flash memory and right the output in a buffer */
		MFDI_ReadBuffer(a_sourceAddress,&l_readBuff,1);

		/* Write from the buffer to the destination address in flash memory */
		MFDI_voidFlashWrite(a_DestinationAddress,&l_readBuff,1);

		/* Increase source address and destination address by 2 as we read 2 bytes each time */
		a_sourceAddress+=2;
		a_DestinationAddress+=2;
	}

}


u8 APARSER_checkSum(u8 *Copy_u8BufData)
{
	/* To return the status of the check sum operation */
	u8 l_status = 0;

	/* local variable to hold the character count high byte */
	u8 l_charCountHighByte = 0;

	/* local variable to hold the character count low byte */
	u8 l_charCountLowByte = 0;

	/* local variable to hold the character count */
	u8 l_charCount = 0;

	/* To get the iteration size needed to get check sum byte as data is not constant */
	u8 l_iteratorSize = 0;

	/* To hold the sum of the record to be compared with checksum byte */
	u16 l_sum = 0;

	/*** Getting the character count ***/

	/* Get the high byte */
	l_charCountHighByte = APARSER_ParseAscii2Hex(Copy_u8BufData[1]);

	/* Get the low byte */
	l_charCountLowByte = APARSER_ParseAscii2Hex(Copy_u8BufData[2]);

	/* Get the character count */
	l_charCount = (l_charCountHighByte << 4) | l_charCountLowByte;
    //printf("l_charCount = %d\n",l_charCount);

	/*** Get iterator size by half bytes ***/

	/*
	 * Get number of data bytes in decimal then multiplying by 2 as we work by half bytes (1 hex number)
	 * Add the byte that holds the char count
	 * Add the address bytes
	 * Add the type of record
	 * Now this variable hold the length of the record until the check sum byte
	 */
	l_iteratorSize = (l_charCount * 2) + 2 + 4 + 2;

	/*
	 * Start from the second halfword as we want to neglect the ':'
	 * Iterate until the end of the data bytes
	 * Increment by 1 bytes (2 Halfwords)
	 */

	for (int l_iterator = 1; l_iterator < l_iteratorSize; l_iterator+=2)
	{
		/* Accumulate the sum byte by byte */
		l_sum += (APARSER_ParseAscii2Hex(Copy_u8BufData[l_iterator]) << 4) | APARSER_ParseAscii2Hex((Copy_u8BufData[l_iterator+1]));;
		//printf("l_iterator %d is %x\n",l_iterator,l_sum);
	}

	/*
	 * Checksum is the 2s-complement of the sum of the number of bytes, plus the address plus the data
	 * Add up the number of bytes, the address and all the data and discard any carry to give 8-bit total
	 * Then invert each digit to give 1s-complement by XOR with 0xFF then add 1 to get the 2s-complement
	 */
	l_sum = (((l_sum & 0xFF) ^ 0xFF) + 1);
    //printf("sum = %d\n",l_sum);

	/* Get the checkSum byte */
	int checkSumUpper = APARSER_ParseAscii2Hex(Copy_u8BufData[l_iteratorSize+1]);
	int checkSumLower = APARSER_ParseAscii2Hex(Copy_u8BufData[l_iteratorSize+2]);
	int checkSum = 0;
	checkSum = ( checkSumUpper << 4) | checkSumLower ;

    //printf("checkSum = %d\n",l_sum);


	/* Compare it with the sum calculated */
	if (checkSum == l_sum)
	{
		l_status = 1;
	}
	else
	{
		l_status = 0;
	}

	return l_status;
}
