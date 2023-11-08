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
	FLASH_SECTOR_ZERO_OFFSET  =	0x00000000,
	FLASH_SECTOR_ONE_OFFSET   =	0x00004000,
	FLASH_SECTOR_TWO_OFFSET   = 0x00008000,
	FLASH_SECTOR_THREE_OFFSET = 0x0000C000,
	FLASH_SECTOR_FOUR_OFFSET  = 0x00010000,
	FLASH_SECTOR_FIVE_OFFSET  = 0x00020000,
	FLASH_SECTOR_SIX_OFFSET   = 0x00040000,
	FLASH_SECTOR_SEVEN_OFFSET = 0x00060000,


}FLASH_SectorsOffset;

typedef enum
{
	FLASH_SECTOR_ZERO_ADDRESS  = 0x08000000,
	FLASH_SECTOR_ONE_ADDRESS   = 0x08004000,
	FLASH_SECTOR_TWO_ADDRESS   = 0x08008000,
	FLASH_SECTOR_THREE_ADDRESS = 0x0800C000,
	FLASH_SECTOR_FOUR_ADDRESS  = 0x08010000,
	FLASH_SECTOR_FIVE_ADDRESS  = 0x08020000,
	FLASH_SECTOR_SIX_ADDRESS   = 0x08040000,
	FLASH_SECTOR_SEVEN_ADDRESS = 0x08060000,

}FLASH_SectorsOffset;

typedef enum
{
	FLASH_SECTOR_ZERO = 0,
	FLASH_SECTOR_ONE,
	FLASH_SECTOR_TWO,
	FLASH_SECTOR_THREE,
	FLASH_SECTOR_FOUR,
	FLASH_SECTOR_FIVE,
}FLASH_Sectors;

/************************************************************************************
 * Service Name: MFDI_voidEraseSector
 * Parameters (in): FLASH_Sectors (Holds the sector number to be erased)
 * Return value: None
 * Description: Erase a specific sector in flash memory.
 ************************************************************************************/

void MFDI_voidEraseSector(FLASH_Sectors A_u8SectorNumber);

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
 * Parameters (in): FLASH_Sectors (Holds the start sector number to be erased)
 * 					FLASH_Sectors (Holds the end sector number to be erased)
 * Return value: None
 * Description: Erase application area in flash memory.
 ************************************************************************************/

void MFDI_voidEraseAppArea(FLASH_Sectors _startSector,FLASH_Sectors _endSector);


/****************************************************************************************
 * Service Name: APARSER_voidMoveData
 * Parameters (in): FLASH_SectorsOffset (Holds the source address)
 * 					FLASH_SectorsOffset (Holds the destination address)
 * 					uint16 (Holds the data length)
 * Return value: None
 * Description: Move data from a sector in flash memory to another sector in flash memory
 ****************************************************************************************/

void MFDI_voidMoveData(FLASH_SectorsOffset _sourceAddress,FLASH_SectorsOffset _DestinationAddress, u16 _dataLength);


#endif /* FLASH_FLASH_INTERFACE_H_ */
