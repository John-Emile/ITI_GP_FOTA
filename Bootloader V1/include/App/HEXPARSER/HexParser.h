/*
 * HexParser.h
 *
 *  Created on: Sep 11, 2023
 *      Author: adham
 */

#ifndef APP_HEXPARSER_HEXPARSER_H_
#define APP_HEXPARSER_HEXPARSER_H_
#include	<LIB/STD_Types.h>


/***************************************************************/
void HexParser_vParseData(u8 A_pu8Data[]);
void HexParser_vEraseAppArea(void);

/***************************************************************/
#define FLASH_APP_START_ADDRESS			0x08000000
#endif /* APP_HEXPARSER_HEXPARSER_H_ */
