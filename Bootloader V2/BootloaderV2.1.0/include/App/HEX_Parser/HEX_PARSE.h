/*
 * HEX_PARSE.h
 *
 *  Created on: Sep 28, 2023
 *      Author: mayke
 */

#ifndef HEX_PARSER_HEX_PARSE_H_
#define HEX_PARSER_HEX_PARSE_H_


u8 APARSER_ParseAscii2Hex(u8 Copy_u8Ascii);

void APARSER_voidParseRecord(u8*Copy_BufRecord);

void APAESER_voidParseData(u8 *Copy_u8BufData);

void APAESER_voidMoveData(u32 _sourceAddress,u32 _DestinationAddress, u16 _dataLength);

#endif /* HEX_PARSER_HEX_PARSE_H_ */
