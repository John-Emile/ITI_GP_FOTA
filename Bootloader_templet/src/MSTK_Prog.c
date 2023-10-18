/*
 * MSTK_Prog.c
 *
 *  Created on: Sep 12, 2023
 *      Author: mayke
 */


#include "../include/LIB/Bit_Math.h"
#include "../include/LIB/STD_TYPES.h"

#include "../include/STK/MSTK_Interface.h"


static void (*SYSTIC_INT)(void)=0;// Global pointer to function
static volatile u8 Flag=0;
void MSTK_voidInit(void)
{
	CLR_BIT(MSTK->STK_CTRL,1);
	//SET_BIT(MSTK->STK_CTRL,2);//AHB
	CLR_BIT(MSTK->STK_CTRL,2);//AHB/8
	//CLR_BIT(MSTK->STK_CTRL,16);

}
void MSTK_voidSetBusyWait(u32 Copy_u32Ticks)
{

	MSTK->STK_VAL=0;//write any value to clear
	MSTK->STK_LOAD=Copy_u32Ticks;

	SET_BIT(MSTK->STK_CTRL,0);//enable timer
	while((GET_BIT(MSTK->STK_CTRL,16))==0);
	MSTK->STK_LOAD=0;
	MSTK->STK_VAL=0;//write any value to clear
	CLR_BIT(MSTK->STK_CTRL,0);//Disable Timer

}

void MSTK_SetIntervalSingle(u32 Copy_u32Ticks,void(*Copy_ptr)(void))
{

	MSTK->STK_LOAD=Copy_u32Ticks;
	MSTK->STK_VAL=0;//write any value to clear
	SET_BIT(MSTK->STK_CTRL,0);//enable timer
	SET_BIT(MSTK->STK_CTRL,1);//enable timer interrupt
	SYSTIC_INT=Copy_ptr;
	Flag=1;
	// global pointer to function = copy_ptr
	//CLR_BIT(MSTK->STK_CTRL,0);

}
void MSTK_SetIntervalPeriodic(u32 Copy_u32Ticks,void(*Copy_ptr)(void))
{

	MSTK->STK_LOAD=Copy_u32Ticks;
	MSTK->STK_VAL=0;//write any value to clear
	SET_BIT(MSTK->STK_CTRL,1);//enable timer interrupt
	SET_BIT(MSTK->STK_CTRL,0);//enable timer
	SYSTIC_INT=Copy_ptr;
	Flag=2;

}

void MSTK_StopInterval(void)
{
	CLR_BIT(MSTK->STK_CTRL,0);//Disable Timer
	CLR_BIT(MSTK->STK_CTRL,1);//Disable timer interrupt
	MSTK->STK_LOAD=0;
	MSTK->STK_VAL=0;
	Flag=0;
}
u32 MSTK_u32GetElapsedTime(void)
{
	u32 L_ELapsedTime=0;
	L_ELapsedTime=(MSTK->STK_LOAD)-(MSTK->STK_VAL);

	return L_ELapsedTime;
}
u32 MSTK_u32GetRemainingTime(void)
{
	u32 L_RemainingTime=0;

	L_RemainingTime=(MSTK->STK_VAL);

	return L_RemainingTime;
}

void SysTick_Handler(void)
{
	if(Flag==2)
	{
		if(SYSTIC_INT!=NULL)
		{
			SYSTIC_INT();
		}
		(CLR_BIT(MSTK->STK_CTRL,16));

	}
	else if(Flag==1)
	{
		if(SYSTIC_INT!=NULL)
		{
			SYSTIC_INT();
			CLR_BIT(MSTK->STK_CTRL,0);
			Flag=0;
		}
		(CLR_BIT(MSTK->STK_CTRL,16));
	}
	else{
	}

}

/*
 * void SysTick_Handler(void
 *
 * {
 *
 *
 *
 *
 * }
 *
 *
 *
 *
 * */
