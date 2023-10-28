 /*************************************************************************************************************************************************************
 *
 * File Name: Flash_Interface.h
 *
 * Description: Header file for the Flash memory.
 *
 * Author: Abdulrahman El-Neshwy, Abdulrahman Khalaf, Aya Samir, Seba Ammar, Ziad Gomaa, John Emile
 *
 * Date : Sept 28, 2023
 *
 *************************************************************************************************************************************************************/

#ifndef FLASH_FLASH_INTERFACE_H_
#define FLASH_FLASH_INTERFACE_H_


#include "FLASH_Private.h"

/* Rom is 256kb in STM32F4xx thus it is only 5 sectors */
#define FLASH_MAX_NUMBER_OF_SECTORS	5

typedef enum
{
	FLASH_SECTOR_ZERO_OFFSET = 0,
	FLASH_SECTOR_ONE_OFFSET = 0x00004000,
	FLASH_SECTOR_TWO_OFFSET = 0x00008000,
	FLASH_SECTOR_THREE_OFFSET = 0x0000C000,
	FLASH_SECTOR_FOUR_OFFSET = 0x00010000,
	FLASH_SECTOR_FIVE_OFFSET = 0x00020000,
	FLASH_SECTOR_SIX_OFFSET = 0x00040000,
	FLASH_SECTOR_SEVEN_OFFSET = 0x00060000,


}FLASH_SectorsOffset;

/************************************************************************************
 * Service Name: MFDI_voidEraseSector
 * Parameters (in): uint8 (Holds the sector number to be erased)
 * Return value: None
 * Description: Erase a specific sector in flash memory.
 ************************************************************************************/

void MFDI_voidEraseSector(u8 A_u8SectorNumber);

/************************************************************************************
 * Service Name: MFDI_voidFlashWrite
 * Parameters (in): uint32 (Holds the address)
 * 					uint16* (Pointer to half-word data)
 * 					uint8 (holds data length)
 * Return value: None
 * Description: Write in specific address in flash memory.
 ************************************************************************************/

void MFDI_voidFlashWrite(u32 A_u32Address,u16*A_ptrData,u8 A_u8DataLength);//u16 to access half word

/************************************************************************************
 * Service Name: MFDI_ReadBuffer
 * Parameters (in): uint32 (Holds the address)
 * 					uint16* (Pointer to half-word data)
 * 					uint8 (holds data length)
 * Return value: None
 * Description: Read from flash memory and write to a buffer.
 ************************************************************************************/

void MFDI_ReadBuffer(u32 A_u32Address,u16 *A_ptrDataBuff,u8 A_u8DataLength);

/************************************************************************************
 * Service Name: MFDI_voidEraseAppArea
 * Parameters (in): None
 * Return value: None
 * Description: Erase application area in flash memory.
 ************************************************************************************/

void MFDI_voidEraseAppArea(void);

#endif /* FLASH_FLASH_INTERFACE_H_ */
