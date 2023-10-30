 /*************************************************************************************************************************************************************
 *
 * File Name: Flash_Prog.c
 *
 * Description: Source file for the Flash memory.
 *
 * Author: Abdulrahman El-Neshwy, Abdulrahman Khalaf, Aya Samir, Seba Ammar, Ziad Gomaa, John Emile
 *
 * Date : Sept 28, 2023
 *
 *************************************************************************************************************************************************************/



#include "../include/LIB/Bit_Math.h"
#include "../include/LIB/STD_TYPES.h"

#include <MCAL/Flash/FLASH_Interface.h>



/************************************************************************************
 * Service Name: MFDI_voidEraseSector
 * Parameters (in): uint8 (Holds the sector number to be erased)
 * Return value: None
 * Description: Erase a specific sector in flash memory.
 ************************************************************************************/

void MFDI_voidEraseSector(u8 A_u8SectorNumber)
{
	if(A_u8SectorNumber==0 || A_u8SectorNumber > FLASH_MAX_NUMBER_OF_SECTORS )
	{
		/* sector0 is boot loader sector */
		/* report sector number error */
	}
	else
	{
		//wait busy flag
		while(GET_BIT(MFDI->SR,16)==1);
		//check if authorized for configuration
		if(GET_BIT(MFDI->CR,31)==1)
		{
			//lock sequence
			MFDI->KEYR=MFDI_KEY1;
			MFDI->KEYR=MFDI_KEY2;
		}
		//selecting the sector erase
		MFDI->CR&=0xFFFFFF87;//clearing selection bits[bits 3:5]
		MFDI->CR|=A_u8SectorNumber<<3; //select sector

		//configure as sector erase
		SET_BIT(MFDI->CR,1);
		//set start bit
		SET_BIT(MFDI->CR,16);

		//wait busy flag
		while(GET_BIT(MFDI->SR,16)==1);

		//set end of operation flag bit
		SET_BIT(MFDI->SR,0);

		//Deactivate sector erase
		CLR_BIT(MFDI->CR,1);
	}
}

/************************************************************************************
 * Service Name: MFDI_voidFlashWrite
 * Parameters (in): uint32 (Holds the address)
 * 					uint16* (Pointer to half-word data)
 * 					uint8 (holds data length)
 * Return value: None
 * Description: Write in specific address in flash memory.
 ************************************************************************************/

void MFDI_voidFlashWrite(u32 A_u32Address,u16*A_ptrData,u8 A_u8DataLength)//u16 to access half word
{
	u8 L_u8iterator;
	//wait busy flag
	while(GET_BIT(MFDI->SR,16)==1);
	//check if authorized for configuration
	if(GET_BIT(MFDI->CR,31)==1)
	{
		//lock sequence
		MFDI->KEYR=MFDI_KEY1;
		MFDI->KEYR=MFDI_KEY2;
	}
	MFDI->CR&= 0xFFFFFCFF;
	MFDI->CR|=WRITE_HALF_WORD<<8;

	for(L_u8iterator=0;L_u8iterator<A_u8DataLength;L_u8iterator++)
	{
		//activate programming flash
		SET_BIT(MFDI->CR,0);

		*((volatile u16*)A_u32Address)=A_ptrData[L_u8iterator];
		A_u32Address+=2;

		//wait busy flag
		while(GET_BIT(MFDI->SR,16)==1);

		//set end of operation flag bit
		SET_BIT(MFDI->SR,0);

		//deactivate programming flash
		CLR_BIT(MFDI->CR,0);

	}


}

/************************************************************************************
 * Service Name: MFDI_voidEraseAppArea
 * Parameters (in): FLASH_Sectors (Holds the start sector number to be erased)
 * 					FLASH_Sectors (Holds the end sector number to be erased)
 * Return value: None
 * Description: Erase application area in flash memory.
 ************************************************************************************/

void MFDI_voidEraseAppArea(FLASH_Sectors _startSector,FLASH_Sectors _endSector)
{
	u8 L_u8iterator;

	//sector 0 is the boot loader
	for(L_u8iterator=_startSector ; L_u8iterator<=_endSector ; L_u8iterator++)
	{
		MFDI_voidEraseSector(L_u8iterator);
	}
}


/************************************************************************************
 * Service Name: MFDI_ReadBuffer
 * Parameters (in): uint32 (Holds the address)
 * 					uint16* (Pointer to half-word data)
 * 					uint8 (holds data length)
 * Return value: None
 * Description: Read from flash memory and write to a buffer.
 ************************************************************************************/

void MFDI_ReadBuffer(u32 A_u32Address,u16 *A_ptrDataBuff,u8 A_u8DataLength)
{
	u8 L_u8iterator=0;
	for(L_u8iterator=0;L_u8iterator<A_u8DataLength;L_u8iterator++)
	{
		/*Read data from flash and store it in Buffer */
		A_ptrDataBuff[L_u8iterator] = *((volatile u16*)A_u32Address);
		A_u32Address+=2;
	}
}



/****************************************************************************************
 * Service Name: MFDI_voidMoveData
 * Parameters (in): FLASH_SectorsOffset (Holds the source address)
 * 					FLASH_SectorsOffset (Holds the destination address)
 * 					uint16 (Holds the data length)
 * Return value: None
 * Description: Move data from a sector in flash memory to another sector in flash memory
 ****************************************************************************************/

void MFDI_voidMoveData(FLASH_Sectors_Address a_sourceAddress,FLASH_Sectors_Address a_DestinationAddress, u16 a_dataLength)
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
