/*************************************************************************************************************************************************************
 *
 * File Name: Hex_Parse.h
 *
 * Description: Header file for the hex file parser.
 *
 * Author: Abdulrahman El-Neshwy, Abdulrahman Khalaf, Aya Samir, Seba Ammar, Ziad Gomaa, John Emile
 *
 * Date : Sept 28, 2023
 *
 *************************************************************************************************************************************************************/

#ifndef HEX_PARSER_HEX_PARSE_H_
#define HEX_PARSER_HEX_PARSE_H_


#define ASCII_VALUE_OF_ZERO	48

/* Definition of possible records type in hex file */
#define HEX_RECORD_TYPE_IS_DATA	'0'
#define HEX_RECORD_TYPE_IS_HIGH_ADDRESS_RECORD	'4'
#define HEX_RECORD_TYPE_IS_END_OF_FILE	'1'


/* Enumeration that holds the frame of the hex record */
typedef enum
{
	HEX_FRAME_START_ASCII_COLON = 0,
	HEX_FRAME_HIGH_BYTE_CHARACTER_COUNT,
	HEX_FRAME_LOW_BYTE_CHARACTER_COUNT,
	HEX_FRAME_FIRST_ADDRESS_BYTE,
	HEX_FRAME_SECOND_ADDRESS_BYTE,
	HEX_FRAME_THIRD_ADDRESS_BYTE,
	HEX_FRAME_FOURTH_ADDRESS_BYTE,
	HEX_FRAME_RECORD_HIGH_BYTE,
	HEX_FRAME_RECORD_LOW_BYTE,
	HEX_FRAME_DATA_FIRST_BYTE_UPPER_HALF,
	HEX_FRAME_DATA_FIRST_BYTE_LOWER_HALF,
	HEX_FRAME_DATA_SECOND_BYTE_UPPER_HALF,
	HEX_FRAME_DATA_SECOND_BYTE_LOWER_HALF,

}HEX_recordFrame;


/************************************************************************************
 * Service Name: APARSER_ParseAscii2Hex
 * Parameters (in): uint8 (Holds the Ascii value)
 * Return value: uint8 (Holds the Hex value)
 * Description: Transform Ascii value to its corresponding Hex number.
 ************************************************************************************/
u8 APARSER_ParseAscii2Hex(u8 Copy_u8Ascii);

/************************************************************************************
 * Service Name: APARSER_voidParseRecord
 * Parameters (in): uint8* (Holds pointer to buffer record)
 * Return value: None
 * Description: Parse the record.
 ************************************************************************************/

void APARSER_voidParseRecord(u8*Copy_BufRecord);

/************************************************************************************
 * Service Name: APARSER_voidParseData
 * Parameters (in): uint8* (Holds pointer to buffer record)
 * Return value: None
 * Description: Parse the hex file.
 ************************************************************************************/

void APAESER_voidParseData(u8 *Copy_u8BufData);


<<<<<<<< Updated upstream:Bootloader V2/BootloaderV2.1.1/include/App/Hex Parser/HEX_PARSE.h
========
void APAESER_voidMoveData(u32 _sourceAddress,u32 _DestinationAddress, u16 _dataLength);
>>>>>>>> Stashed changes:Hex Parser/HEX_PARSE.h

#endif /* HEX_PARSER_HEX_PARSE_H_ */
