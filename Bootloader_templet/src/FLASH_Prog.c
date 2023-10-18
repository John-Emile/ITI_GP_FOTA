/*
 * FLASH_Prog.c
 *
 *  Created on: Sep 27, 2023
 *      Author: mayke
 */



#include "../include/LIB/Bit_Math.h"
#include "../include/LIB/STD_TYPES.h"

#include "../include/FLASH/FLASH_Interface.h"




void MFDI_voidEraseSector(u8 A_u8SectorNumber)
{
	if(A_u8SectorNumber==0 || A_u8SectorNumber>5)//sector 6&7 in other controllers
	{
		//sector0 is boot loader sector
		//report sector number error
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
		MFDI->CR|=A_u8SectorNumber<<3;//select sector

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


void MFDI_voidEraseAppArea(void)
{
	u8 L_u8iterator;
	//sector 0 is the boot loader
	for(L_u8iterator=1;L_u8iterator<6;L_u8iterator++)
	{
		MFDI_voidEraseSector(L_u8iterator);
	}
}
