/*****************************************************************/
/* Author  : Abdelrahman                                         */
/* SWC     : MNVIC                                               */
/* Version : 1.0                                                 */
/* Date    : 11 Sep 2023                                         */
/*****************************************************************/

#include <LIB/STD_Types.h>
#include <LIB/BIT_MATH.h>

#include <MCAL/NVIC/MNVIC_config.h>
#include <MCAL/NVIC/MNVIC_interface.h>
#include <MCAL/NVIC/MNVIC_private.h>

u8 Global_u8IPR;

void MNVIC_vidEnableInt(u8 u8PostionCpy)
{
	/*
	 * REG_SIZE define as 32
	 * ISER[(u8PostionCpy/REG_SIZE)] to make Each Reg size indicate one index
	 * (u8PostionCpy%REG_SIZE) to indicate Bits position in side Register
	 * we use ISER to Enable interrupt by setting one to Interrupt index
	 */
	SET_BIT(NVIC->ISER[(u8PostionCpy/REG_SIZE)],(u8PostionCpy%REG_SIZE));
}


void MNVIC_vidDisableInt(u8 u8PostionCpy)
{
	/*
	 * REG_SIZE define as 32
	 * ICER[(u8PostionCpy/REG_SIZE)] to make Each Reg size indicate one index
	 * (u8PostionCpy%REG_SIZE) to indicate Bits position in side Register
	 * we use ICER to Disable interrupt by setting one to Interrupt index
	 */
	SET_BIT(NVIC->ICER[(u8PostionCpy/REG_SIZE)],(u8PostionCpy%REG_SIZE));
}


void MNVIC_vidEnablePendingFlag(u8 u8PostionCpy)
{
	/*
	 * REG_SIZE define as 32
	 * ISER[(u8PostionCpy/REG_SIZE)] to make Each Reg size indicate one index
	 * (u8PostionCpy%REG_SIZE) to indicate Bits position in side Register
	 * we use ISPR to Enable Pending interrupt by setting one to Interrupt index
	 */
	SET_BIT(NVIC->ISPR[(u8PostionCpy/REG_SIZE)],(u8PostionCpy%REG_SIZE));
}


void MNVIC_vidDisablePendingFlag(u8 u8PostionCpy)
{
	/*
	 * REG_SIZE define as 32
	 * ISER[(u8PostionCpy/REG_SIZE)] to make Each Reg size indicate one index
	 * (u8PostionCpy%REG_SIZE) to indicate Bits position in side Register
	 * we use ICPR to Disable Pending interrupt by setting one to Interrupt index
	 */
	SET_BIT(NVIC->ICPR[(u8PostionCpy/REG_SIZE)],(u8PostionCpy%REG_SIZE));
}


void MNVIC_vidIsIntActive(u8 u8PostionCpy, u8* pu8ReadCpy)
{
	/*
	 * REG_SIZE define as 32
	 * ISER[(u8PostionCpy/REG_SIZE)] to make Each Reg size indicate one index
	 * (u8PostionCpy%REG_SIZE) to indicate Bits position in side Register
	 * we use IABR to Check if interrupt happen or NOt
	 * if Bit = 1 then the Indicate interrupt happen
	 * if Bit = 0 no Interrupt happen
	 */
	*pu8ReadCpy=GET_BIT(NVIC->IABR[(u8PostionCpy/REG_SIZE)],(u8PostionCpy%REG_SIZE));
}


void MNVIC_vidSetIntGroupMode(NVIC_GROUP_t GroupModeCpy)
{
	/*
	 * Global_u8IPR used to hold Group Mode to check it in Set priority Function
	 * AIRCR_PreValueLoc initialized with Zero to clear all bits
	 *  MNVIC_VECT_KEY equal 0x05FA0000 this Value must be set in MSB to allow Writing on Reg
	 *  GroupModeCpy & 0x7 to get three Bits
	 *  Shift By 8 to access PRIGROUP Bits
	 *  SCB_AIRCR = AIRCR_PreValueLoc --> To access Register in one cycle
	 */
	Global_u8IPR = GroupModeCpy;
	u32 AIRCR_PreValueLoc = 0;
	AIRCR_PreValueLoc |=(MNVIC_VECT_KEY) | ((GroupModeCpy & 0x7)<<8);

	SCB_AIRCR = AIRCR_PreValueLoc;
}



void MNVIC_vidSetIntPriority(u8 u8PostionCpy, u8 u8GroupNumCpy,u8 u8SubGroupNumCpy)
{
	/*
	 * switch on Global_u8IPR which hold GroupMode
	 * this indicate how many bits for Groups and Subgroup
	 * Group16_Sub0 need 4 bits for Groups Starting from bit number 4 and no bits for Subgroup
	 * Group8_Sub2 need 3 bits for Groups Starting from bit number 5 and 1 bit for Subgroup Starting from bit number 4
	 * Group4_Sub4 need 2 bits for Groups Starting from bit number 6 and 2 bits for Subgroup Starting from bit number 4
	 * Group2_Sub8 need 1 bit for Groups Starting from bit number 7 and 3 bits for Subgroup Starting from bit number 4
	 * Group16_Sub0 need No bits for Groups and 4 bits for Subgroup Starting from bit number 4
	 */
	switch(Global_u8IPR)
	{
	case Group16_Sub0:
		NVIC->IPR[u8PostionCpy] = u8GroupNumCpy<<4;
		break;
	case Group8_Sub2:
		NVIC->IPR[u8PostionCpy] = u8GroupNumCpy<<5 | u8SubGroupNumCpy<<4;
		break;
	case Group4_Sub4:
		NVIC->IPR[u8PostionCpy] = u8GroupNumCpy<<6 | u8SubGroupNumCpy<<4;
		break;
	case Group2_Sub8:
		NVIC->IPR[u8PostionCpy] = u8GroupNumCpy<<7 | u8SubGroupNumCpy<<4;
		break;
	case Group0_Sub16:
		NVIC->IPR[u8PostionCpy] = u8SubGroupNumCpy<<4;
		break;
	}
}









