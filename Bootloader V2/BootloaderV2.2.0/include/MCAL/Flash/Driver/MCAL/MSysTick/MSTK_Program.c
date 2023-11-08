/*
 * MSTK_Program.c
 *
 *  Created on: Sep 12, 2023
 *      Author: Hesham Yasser
 */

#include <LIB/STD_Types.h>
#include <LIB/BIT_MATH.h>

#include <MSysTick/MSTK_private.h>
#include <MSysTick/MSTK_Configurations.h>
#include <MSysTick/MSTK_Interface.h>

pf MSYSTICK_HANDLER=NULL_PTR;

void MSTK_voidInit(void)
{
	/*Select the clock source for systick*/
#if MSTK_CLK_SOURCE == MSTK_AHB_BY_8
	CLR_BIT (STK->CTRL , CLKSOURCE);
#elif MSTK_CLK_SOURCE == MSTK_AHB
	SET_BIT (STK->CTRL , CLKSOURCE);
#else
#error WRONG_STK_CLK
#endif
}

void MSTK_voidClearCurrentValue (void)
{
	/*Put any value in the register to reset its value to the max*/
	STK->VAL = 0;
}

void MSTK_voidSetPreloadValue (u32 A_u32PreLoadVal)
{
	/*Set the max value (Preload)*/
	STK->LOAD = A_u32PreLoadVal & STK_RES;
	/*Put any value in the register to reset its value to the max*/
	STK->VAL = 0;
}

void MSTK_voidGetFlagValue (u8 * p_Read)
{
	/*Get the reading of the count flag*/
	*p_Read = (u8)GET_BIT(STK->CTRL , COUNTFLAG);
}

void MSTK_voidEnableSTK (void)
{
	/*Set that bit to enable systick*/
	SET_BIT(STK->CTRL , ENABLE);
}

void MSTK_voiDisableSTK (void)
{
	/*Clear that bit to disable systick*/
	CLR_BIT(STK->CTRL , ENABLE);
}

void MSTK_voidGetElapsedTime (u32 * p_Read)
{
	/*Subtrace the max from the current value to calculate the elapsed time*/
	*p_Read = (STK->LOAD) - (STK->VAL);
}

void MSTK_voidGetRemainingTime (u32 * p_Read)
{
	/*return the remaining time*/
	*p_Read = STK->VAL;
}

void MSTK_voidEnableInterrupt (void)
{
	/*Set that bit to enable systick interrupt*/
	SET_BIT (STK->CTRL , TICKINT);
}

void MSTK_voidDisableInterrupt (void)
{
	/*Clear that bit to Disable systick interrupt*/
	CLR_BIT (STK->CTRL , TICKINT);
}

void MSTK_voidDelayms (u32 A_u32Delayms)
{


	/*Calculate the needed preload value*/
	u32 local_u32PreloadVal = (A_u32Delayms)*(16000);
	/*Set the preload to the corresponding register*/
	STK->LOAD = local_u32PreloadVal & STK_RES;

	/*Reset the current value register*/
	STK->VAL = 0;

	/*Enable systick*/
	SET_BIT(STK->CTRL , ENABLE);
	while ((GET_BIT(STK->CTRL , COUNTFLAG)) == 0);

}

void MSTK_voidDelayus (u32 A_u32Delayus)
{
	/*Calculate the needed preload value*/
	u32 local_u32PreloadVal = (A_u32Delayus)*(16);
	/*Set the preload to the corresponding register*/
	STK->LOAD = local_u32PreloadVal & STK_RES;
	/*Reset the current value register*/
	STK->VAL = 0;
	/*Enable systick*/
	SET_BIT(STK->CTRL , ENABLE);
	while ((GET_BIT(STK->CTRL , COUNTFLAG)) == 0);

}


void MSYSTICK_CallBack(void(*ptr)(void))
{
	MSYSTICK_HANDLER=ptr;
}

void SysTick_Handler(void)
{
	MSYSTICK_HANDLER();
	GET_BIT(STK->CTRL,COUNTFLAG);
}
