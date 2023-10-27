/*
 * FLASH_Interface.h
 *
 *  Created on: Sep 27, 2023
 *      Author: mayke
 */

#ifndef FLASH_FLASH_INTERFACE_H_
#define FLASH_FLASH_INTERFACE_H_


#include "FLASH_Config.h"
#include "FLASH_Private.h"


void MFDI_voidEraseSector(u8 A_u8SectorNumber);

void MFDI_voidFlashWrite(u32 A_u32Address,u16*A_ptrData,u8 A_u8DataLength);//u16 to access half word
void MFDI_ReadBuffer(u32 A_u32Address,u16 *A_ptrDataBuff,u8 A_u8DataLength);
void MFDI_voidEraseAppArea(void);

#endif /* FLASH_FLASH_INTERFACE_H_ */
