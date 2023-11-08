/*
 * MSTK_Program.c
 *
 *  Created on: Sep 12, 2023
 *      Author: Elneshwy
 */

#include <LIB/STD_Types.h>
#include <LIB/BIT_MATH.h>

#include <MCAL/MSysTick/MSTK_Configurations.h>
#include <MCAL/MSysTick/MSTK_Interface.h>
#include <MCAL/MSysTick/MSTK_private.h>


pf MSYSTICK_HANDLER=NULL_PTR;


/************************************************************************************
 * Service Name: MSTK_voidInit
 * Parameters (in): None
 * Return value: None
 * Description: Initialize SystemTick.
 ************************************************************************************/

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


/************************************************************************************
 * Service Name: MSTK_voidClearCurrentValue
 * Parameters (in): None
 * Return value: None
 * Description: Clear counter value .
 ************************************************************************************/

void MSTK_voidClearCurrentValue (void)
{
	/*Put any value in the register to reset its value to the max*/
	STK->VAL = 0;
}


/************************************************************************************
 * Service Name: MSTK_voidSetPreloadValue
 * Parameters (in): uint32 (hold value of Counter)
 * Return value: None
 * Description: Set new value in counter register.
 ************************************************************************************/

void MSTK_voidSetPreloadValue (u32 A_u32PreLoadVal)
{
	/*Set the max value (Preload)*/
	STK->LOAD = A_u32PreLoadVal & STK_RES;
	/*Put any value in the register to reset its value to the max*/
	STK->VAL = 0;
}

/************************************************************************************
 * Service Name: MSTK_voidGetFlagValue
 * Parameters (in): uint8* (hold Address of Local variable that)
 * Return value: None
 * Description: Set value of Counter Flag value in Local Variable.
 ************************************************************************************/

void MSTK_voidGetFlagValue (u8 * p_Read)
{
	/*Get the reading of the count flag*/
	*p_Read = (u8)GET_BIT(STK->CTRL , COUNTFLAG);
}

/************************************************************************************
 * Service Name: MSTK_voidEnableSTK
 * Parameters (in): None
 * Return value: None
 * Description: Enable SystemTick.
 ************************************************************************************/

void MSTK_voidEnableSTK (void)
{
	/*Set that bit to enable systick*/
	SET_BIT(STK->CTRL , ENABLE);
}


/************************************************************************************
 * Service Name: MSTK_voiDisableSTK
 * Parameters (in): None
 * Return value: None
 * Description: Disable SystemTick.
 ************************************************************************************/

void MSTK_voiDisableSTK (void)
{
	/*Clear that bit to disable systick*/
	CLR_BIT(STK->CTRL , ENABLE);
}

/************************************************************************************
 * Service Name: MSTK_voidGetElapsedTime
 * Parameters (in): uint32* (Hold address of local variable)
 * Return value: None
 * Description: Set the elapsed time value in the Local variable.
 ************************************************************************************/

void MSTK_voidGetElapsedTime (u32 * p_Read)
{
	/*Subtrace the max from the current value to calculate the elapsed time*/
	*p_Read = (STK->LOAD) - (STK->VAL);
}


/************************************************************************************
 * Service Name: MSTK_voidGetRemainingTime
 * Parameters (in): uint32* (Hold address of local variable)
 * Return value: None
 * Description: Set the Remaining time value in the Local variable.
 ************************************************************************************/

void MSTK_voidGetRemainingTime (u32 * p_Read)
{
	/*return the remaining time*/
	*p_Read = STK->VAL;
}

/************************************************************************************
 * Service Name: MSTK_voidEnableInterrupt
 * Parameters (in): None
 * Return value: None
 * Description: Enable SystemTick Interrupt.
 ************************************************************************************/

void MSTK_voidEnableInterrupt (void)
{
	/*Set that bit to enable systick interrupt*/
	SET_BIT (STK->CTRL , TICKINT);
}

/************************************************************************************
 * Service Name: MSTK_voidDisableInterrupt
 * Parameters (in): None
 * Return value: None
 * Description: Disable SystemTick Interrupt.
 ************************************************************************************/

void MSTK_voidDisableInterrupt (void)
{
	/*Clear that bit to Disable systick interrupt*/
	CLR_BIT (STK->CTRL , TICKINT);
}


/************************************************************************************
 * Service Name: MSTK_voidDelayms
 * Parameters (in): uint32 (Hold value of Delay Time in msec)
 * Return value: None
 * Description: Delay system with the required time in msec by polling.
 ************************************************************************************/

void MSTK_voidDelayms (u32 A_u32Delayms)
{


	/*Calculate the needed preload value*/
	u32 local_u32PreloadVal = (A_u32Delayms)*(2000);
	/*Set the preload to the corresponding register*/
	STK->LOAD = local_u32PreloadVal & STK_RES;

	/*Reset the current value register*/
	STK->VAL = 0;

	/*Enable systick*/
	SET_BIT(STK->CTRL , ENABLE);
	while ((GET_BIT(STK->CTRL , COUNTFLAG)) == 0);
	/*Clear that bit to disable systick*/
	CLR_BIT(STK->CTRL , ENABLE);

}

/************************************************************************************
 * Service Name: MSTK_voidDelayus
 * Parameters (in): uint32 (Hold value of Delay Time in usec)
 * Return value: None
 * Description: Delay system with the required time in usec by polling.
 ************************************************************************************/

void MSTK_voidDelayus (u32 A_u32Delayus)
{
	/*Calculate the needed preload value*/
	u32 local_u32PreloadVal = (A_u32Delayus)*(2);
	/*Set the preload to the corresponding register*/
	STK->LOAD = local_u32PreloadVal & STK_RES;
	/*Reset the current value register*/
	STK->VAL = 0;
	/*Enable systick*/
	SET_BIT(STK->CTRL , ENABLE);
	while ((GET_BIT(STK->CTRL , COUNTFLAG)) == 0);
	/*Clear that bit to disable systick*/
	CLR_BIT(STK->CTRL , ENABLE);

}

/************************************************************************************
 * Service Name: MSTK_StopInterval
 * Parameters (in): None
 * Return value: None
 * Description: Stop systemTick.
 ************************************************************************************/

void MSTK_StopInterval(void)
{
	/*Disable Timer*/
	CLR_BIT(STK->CTRL,0);
	/*Disable timer interrupt*/
	CLR_BIT(STK->CTRL,1);
	STK->LOAD=0;
	STK->VAL=0;
}


/************************************************************************************
 * Service Name: MSTK_asyncDelayms
 * Parameters (in): uint32 (Hold value of Delay Time in msec)
 * 					pf (hold Address of Function)
 * Return value: None
 * Description: Delay Function with the required time in msec by interrupt handler.
 ************************************************************************************/

void MSTK_asyncDelayms (u32 A_u32Delayms,pf ptr)
{

	/*Calculate the needed preload value*/
	u32 local_u32PreloadVal = (A_u32Delayms)*(2000);
	/*Set the preload to the corresponding register*/
	STK->LOAD = local_u32PreloadVal & STK_RES;

	/*Reset the current value register*/
	STK->VAL = 0;

	/*Enable systick*/
	SET_BIT(STK->CTRL , ENABLE);
	/*Set that bit to enable systick interrupt*/
	SET_BIT (STK->CTRL , TICKINT);

	MSYSTICK_HANDLER=ptr;
}


/************************************************************************************
 * Service Name: MSYSTICK_CallBack
 * Parameters (in): pf (hold Address of Function)
 * Return value: None
 * Description: Set address of Function of Global pointer to Function.
 ************************************************************************************/

void MSYSTICK_CallBack(void(*ptr)(void))
{
	if(MSYSTICK_HANDLER == NULL_PTR)
	{
		MSYSTICK_HANDLER=ptr;
	}
}

/************************************************************************************
 * Service Name: SysTick_Handler
 * Parameters (in): None
 * Return value: None
 * Description: ISR called when System tick call an interrupt.
 ************************************************************************************/

void SysTick_Handler(void)
{
	if(MSYSTICK_HANDLER!=NULL_PTR)
	{
		MSYSTICK_HANDLER();
		CLR_BIT(STK->CTRL,ENABLE);
	}
	(GET_BIT(STK->CTRL,COUNTFLAG));
}
