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

#include <MCAL/FLASH/FLASH_Interface.h>



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
<<<<<<< Updated upstream:Flash Driver/FLASH_Prog.c
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
=======
		/* Wait busy flag */
		while(GET_BIT(MFDI->SR,BSY)==1);
		
		/* Check if authorized for configuration */
		if(GET_BIT(MFDI->CR,LOCK)==1)
		{
			/* Unlock sequence */
			MFDI->KEYR=MFDI_KEY1;
			MFDI->KEYR=MFDI_KEY2;
		}

		/*
		 * Selecting the sector erase
		 * Clearing selection bits[bits 3:5]
		 * Selecting sector
		 */
		MFDI->CR &= SELECT_SECTOR_MASK;
		MFDI->CR |= A_u8SectorNumber<<3;

		/* Configure as sector erase */
		SET_BIT(MFDI->CR,SER);
		
		/* Set start bit */
		SET_BIT(MFDI->CR,STRT);

		/* Wait busy flag */
		while(GET_BIT(MFDI->SR,OPERR)==1);

		/* Set end of operation flag bit */
		SET_BIT(MFDI->SR,EOP);

		/* Deactivate sector erase */
		CLR_BIT(MFDI->CR,SER);
>>>>>>> Stashed changes:Bootloader V3/Bootloader V3.0.1/src/FLASH_Prog.c
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

void MFDI_voidFlashWrite(u32 A_u32Address,u16*A_ptrData,u8 A_u8DataLength) /*u16 to access half word */
{
	u8 L_u8iterator;
<<<<<<< Updated upstream:Flash Driver/FLASH_Prog.c
	//wait busy flag
	while(GET_BIT(MFDI->SR,16)==1);
	//check if authorized for configuration
	if(GET_BIT(MFDI->CR,31)==1)
=======
	
	/* Wait busy flag */
	while(GET_BIT(MFDI->SR,BSY)==1);
	
	/* Check if authorized for configuration */
	if(GET_BIT(MFDI->CR,LOCK)==1)
>>>>>>> Stashed changes:Bootloader V3/Bootloader V3.0.1/src/FLASH_Prog.c
	{
		/* lock sequence */
		MFDI->KEYR=MFDI_KEY1;
		MFDI->KEYR=MFDI_KEY2;
	}
<<<<<<< Updated upstream:Flash Driver/FLASH_Prog.c
	MFDI->CR&= 0xFFFFFCFF;
	MFDI->CR|=WRITE_HALF_WORD<<8;

	for(L_u8iterator=0;L_u8iterator<A_u8DataLength;L_u8iterator++)
	{
		//activate programming flash
		SET_BIT(MFDI->CR,0);
=======

	MFDI->CR &= SELECT_WORD_SIZE_MASK;
	MFDI->CR |= WRITE_HALF_WORD<<8;

	for(L_u8iterator=0;L_u8iterator<A_u8DataLength;L_u8iterator++)
	{
		/* Activate programming flash */
		SET_BIT(MFDI->CR,PG);
>>>>>>> Stashed changes:Bootloader V3/Bootloader V3.0.1/src/FLASH_Prog.c

		*((volatile u16*)A_u32Address)=A_ptrData[L_u8iterator];
		A_u32Address+=2;

<<<<<<< Updated upstream:Flash Driver/FLASH_Prog.c
		//wait busy flag
		while(GET_BIT(MFDI->SR,16)==1);

		//set end of operation flag bit
		SET_BIT(MFDI->SR,0);

		//deactivate programming flash
		CLR_BIT(MFDI->CR,0);
=======
		/* Wait busy flag */
		while(GET_BIT(MFDI->SR,BSY)==1);

		/* Set end of operation flag bit */
		SET_BIT(MFDI->SR,EOP);

		/* Deactivate programming flash */
		CLR_BIT(MFDI->CR,PG);
>>>>>>> Stashed changes:Bootloader V3/Bootloader V3.0.1/src/FLASH_Prog.c

	}


}

/************************************************************************************
 * Service Name: MFDI_voidEraseAppArea
 * Parameters (in): None
 * Return value: None
 * Description: Erase application area in flash memory.
 ************************************************************************************/

void MFDI_voidEraseAppArea(void)
{
	u8 L_u8iterator;

<<<<<<< Updated upstream:Flash Driver/FLASH_Prog.c
	//sector 0 is the boot loader
	for(L_u8iterator=1;L_u8iterator<6;L_u8iterator++)
=======
	/* Skip seector 0 as it is the bootloader */
	for(L_u8iterator=_startSector ; L_u8iterator<=_endSector ; L_u8iterator++)
>>>>>>> Stashed changes:Bootloader V3/Bootloader V3.0.1/src/FLASH_Prog.c
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
