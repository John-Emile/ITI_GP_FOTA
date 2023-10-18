/*
 * GPIO_Prog.c
 *
 *  Created on: Sep 7, 2023
 *      Author: maykel
 *
 * Description: MGPIO_Prog.c -> Implementation
 *
 * Module Feature :01-MGPIO_voidSetPinMode
 *                 02-MGPIO_voidSetPortMode
 *                 03-MGPIO_voidSetOutputMode
 *                 04-
 *                 05-
 *                 06-
 *                 07-
 *                 08-
 *
 */


/*
 **************************************************************************************
 *									Standard Types
 *************************************************************************************
 */
#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/Bit_Math.h"

/*
 **************************************************************************************
 *										Macro
 *************************************************************************************
 */

#include "../include/GPIO/GPIO_Private.h"
#include "../include/GPIO/GPIO_Config.h"
#include "../include/GPIO/GPIO_Interface.h"


/*
 **************************************************************************************
 *								Function implementation
 *************************************************************************************
 */
void MGPIO_voidSetPinMode (u8 Copy_u8PortName , u8 Copy_u8PinNum ,u8 Copy_u8Mode)
{
	/*
	 * MGPIO_MODE_INPUT
	 * MGPIO_MODE_OUTPUT
	 * MGPIO_MODE_ALTFUN
	 * MGPIO_MODE_ANALOG
	 */
	if(Copy_u8PinNum<16)
	{
		switch (Copy_u8PortName)
		{
		case MGPIO_PORTA:MGPIOA->MODER|= (u32)(Copy_u8Mode<<2U *Copy_u8PinNum);break;
		case MGPIO_PORTB:MGPIOB->MODER|= (u32)(Copy_u8Mode<<2U *Copy_u8PinNum);break;
#if STMmodel==STM32F401cc
		case MGPIO_PORTC:
			if(12<Copy_u8PinNum)
			{
				MGPIOC->MODER|= (u32)(Copy_u8Mode<<2U *Copy_u8PinNum);
			}
			else{
				// report error portc pin number out of boundary
			}
			break;
#elif STMmodel
			/*	case MGPIO_PORTC:MGPIOC->MODER|= (u32)(Copy_u8Mode<<2U *Copy_u8PinNum);break;
			 * case MGPIO_PORTD:MGPIOD->MODER|= (u32)(Copy_u8Mode<<2U *Copy_u8PinNum);break;
			 *case MGPIO_PORTE:MGPIOE->MODER|= (u32)(Copy_u8Mode<<2U *Copy_u8PinNum);break;
			 *case MGPIO_PORTH:MGPIOH->MODER|= (u32)(Copy_u8Mode<<2U *Copy_u8PinNum);break;
			 */
#endif
		default ://error
			break;
		}
	}
	else {
		//report error
	}
}

//void MGPIO_voidSetPortMode (u8 Copy_u8PortName ,u8 Copy_u8Mode){}//assignment

void MGPIO_voidSetOutputMode (u8 Copy_u8PortName , u8 Copy_u8PinNum ,u8 Copy_u8OutputMode)
{
	switch (Copy_u8PortName)
	{
	case MGPIO_PORTA:MGPIOA->OTYPER |= (u32) (Copy_u8OutputMode<<Copy_u8PinNum);break;
	case MGPIO_PORTB:MGPIOB->OTYPER |= (u32) (Copy_u8OutputMode<<Copy_u8PinNum);break;
	case MGPIO_PORTC:MGPIOC->OTYPER |= (u32) (Copy_u8OutputMode<<Copy_u8PinNum);break;
	default ://error
		break;
	}
}

void MGPIO_voidSetOutputSpeed (u8 Copy_u8PortName , u8 Copy_u8PinNum ,u8 Copy_u8OutputSpeed)
{
	switch (Copy_u8PortName)
	{
	case MGPIO_PORTA:MGPIOA->OSPEEDR|= (u32)(Copy_u8OutputSpeed<< 2U *Copy_u8PinNum);break;
	case MGPIO_PORTB:MGPIOB->OSPEEDR|= (u32)(Copy_u8OutputSpeed<< 2U *Copy_u8PinNum);break;
	case MGPIO_PORTC:MGPIOC->OSPEEDR|= (u32)(Copy_u8OutputSpeed<< 2U *Copy_u8PinNum);break;
	default ://error
		break;
	}
}
void MGPIO_voidSetPullState (u8 Copy_u8PortName , u8 Copy_u8PinNum ,u8 Copy_u8PullState)
{
	switch (Copy_u8PortName)
	{
	case MGPIO_PORTA:MGPIOA->PUPDR|= (u32)( Copy_u8PullState<<2U *Copy_u8PinNum);break;
	case MGPIO_PORTB:MGPIOB->PUPDR|= (u32)( Copy_u8PullState<<2U *Copy_u8PinNum);break;
	case MGPIO_PORTC:MGPIOC->PUPDR|= (u32)( Copy_u8PullState<<2U *Copy_u8PinNum);break;
	default ://error
		break;
	}
}
u8 MGPIO_u8GetPinVal (u8 Copy_u8PortName , u8 Copy_u8PinNum )
{
	u8 L_u8PinVlaue=0;
	switch (Copy_u8PortName)
	{
	case MGPIO_PORTA:L_u8PinVlaue=GET_BIT(MGPIOA->IDR,Copy_u8PinNum);break;
	case MGPIO_PORTB:L_u8PinVlaue=GET_BIT(MGPIOB->IDR,Copy_u8PinNum);break;
	case MGPIO_PORTC:L_u8PinVlaue=GET_BIT(MGPIOC->IDR,Copy_u8PinNum);break;
	default ://error
		break;
	}
	return L_u8PinVlaue;
}
void MGPIO_voidSetPinVal (u8 Copy_u8PortName , u8 Copy_u8PinNum ,u8 Copy_u8PinVal)
{
	if(Copy_u8PinVal==MGPIO_HIGH)
	{
		switch (Copy_u8PortName)
		{
		case MGPIO_PORTA:SET_BIT(MGPIOA->ODR,Copy_u8PinNum);break;
		case MGPIO_PORTB:SET_BIT(MGPIOB->ODR,Copy_u8PinNum);break;
		case MGPIO_PORTC:SET_BIT(MGPIOC->ODR,Copy_u8PinNum);break;
		default ://error
			break;
		}
	}
	if(Copy_u8PinVal==MGPIO_LOW)
	{
		switch (Copy_u8PortName)
		{
		case MGPIO_PORTA:CLR_BIT(MGPIOA->ODR,Copy_u8PinNum);break;
		case MGPIO_PORTB:CLR_BIT(MGPIOB->ODR,Copy_u8PinNum);break;
		case MGPIO_PORTC:CLR_BIT(MGPIOC->ODR,Copy_u8PinNum);break;
		default ://error
			break;
		}
	}
}
void MGPIO_voidDirectSetReset (u8 Copy_u8PortName , u8 Copy_u8PinNum ,u8 Copy_u8SetResetState)
{
	if(Copy_u8SetResetState == MGPIO_HIGH)
	{
		switch (Copy_u8PortName)
		{
		case MGPIO_PORTA:MGPIOA->BSRR= (u32)( 1U <<Copy_u8PinNum);break;
		case MGPIO_PORTB:MGPIOB->BSRR= (u32)( 1U <<Copy_u8PinNum);break;
		case MGPIO_PORTC:MGPIOC->BSRR= (u32)( 1U <<Copy_u8PinNum);break;
		default ://error
			break;

		}
	}
	else if(Copy_u8SetResetState==MGPIO_LOW)
	{
		Copy_u8PinNum+=16;
		switch (Copy_u8PortName)
		{
		case MGPIO_PORTA:MGPIOA->BSRR= (u32)( 1U <<Copy_u8PinNum);break;
		case MGPIO_PORTB:MGPIOB->BSRR= (u32)( 1U <<Copy_u8PinNum);break;
		case MGPIO_PORTC:MGPIOC->BSRR= (u32)( 1U <<Copy_u8PinNum);break;
		default ://error
			break;
		}
	}
}

void MGPIO_voidSetPortMode (u8 Copy_u8PortName ,u32 Copy_u32OutputMode)
{
	switch (Copy_u8PortName)
	{
	case MGPIO_PORTA:MGPIOA->MODER|= (u32) Copy_u32OutputMode;break;
	case MGPIO_PORTB:MGPIOB->MODER|= (u32) Copy_u32OutputMode;break;
	case MGPIO_PORTC:MGPIOC->MODER|= (u32) Copy_u32OutputMode;break;
	default ://error
		break;
	}


}

void MGPIO_SetPortVal(u8 Copy_u8PortName , u16 Copy_u16OutputValue)
{
	switch (Copy_u8PortName)
	{
	case MGPIO_PORTA:MGPIOA->ODR|= (u16)Copy_u16OutputValue;break;
	case MGPIO_PORTB:MGPIOB->ODR|= (u16)Copy_u16OutputValue;break;
	case MGPIO_PORTC:MGPIOC->ODR|= (u16)Copy_u16OutputValue;break;
	default ://error
		break;
	}

}


u32 MGPIO_voidPinLock (u8 Copy_u8PortName , u8 Copy_u8PinNum )
{
	u32 L_u32LCKRRead;
	switch (Copy_u8PortName)
	{
	case MGPIO_PORTA:
		MGPIOA->LCKR= (u32)(1U<<16|((u16)1U<<Copy_u8PinNum));
		MGPIOA->LCKR= (u32)(0U<<16|((u16)1U<<Copy_u8PinNum));
		MGPIOA->LCKR= (u32)(1U<<16|((u16)1U<<Copy_u8PinNum));
		L_u32LCKRRead=MGPIOA->LCKR;
		break;
	case MGPIO_PORTB:
		MGPIOA->LCKR= (u32)(1U<<16|((u16)1U<<Copy_u8PinNum));
		MGPIOA->LCKR= (u32)(0U<<16|((u16)1U<<Copy_u8PinNum));
		MGPIOA->LCKR= (u32)(1U<<16|((u16)1U<<Copy_u8PinNum));
		L_u32LCKRRead=MGPIOB->LCKR;
		break;
	case MGPIO_PORTC:
		MGPIOA->LCKR= (u32)(1U<<16|((u16)1U<<Copy_u8PinNum));
		MGPIOA->LCKR= (u32)(0U<<16|((u16)1U<<Copy_u8PinNum));
		MGPIOA->LCKR= (u32)(1U<<16|((u16)1U<<Copy_u8PinNum));
		L_u32LCKRRead=MGPIOB->LCKR;
		break;

	default ://error
		break;
	}
	return L_u32LCKRRead=0;
}
void MGPIO_voidSetAltFun (u8 Copy_u8PortName , u8 Copy_u8PinNum ,u8 Copy_u8AltFun)
{
	if(Copy_u8PinNum<=7U)
	{
		switch (Copy_u8PortName)
		{
		case MGPIO_PORTA:MGPIOA->AFRL|= (u32)(Copy_u8AltFun<< 4U *Copy_u8PinNum);break;
		case MGPIO_PORTB:MGPIOB->AFRL|= (u32)(Copy_u8AltFun<< 4U *Copy_u8PinNum);break;
		case MGPIO_PORTC:MGPIOC->AFRL|= (u32)(Copy_u8AltFun<< 4U *Copy_u8PinNum);break;
		default ://error
			break;
		}
	}
	else if(Copy_u8PinNum<=15U)
	{
		switch (Copy_u8PortName)
		{
		case MGPIO_PORTA:MGPIOA->AFRH|= (u32)(Copy_u8AltFun<< 4U *Copy_u8PinNum);break;
		case MGPIO_PORTB:MGPIOB->AFRH|= (u32)(Copy_u8AltFun<< 4U *Copy_u8PinNum);break;
		case MGPIO_PORTC:MGPIOC->AFRH|= (u32)(Copy_u8AltFun<< 4U *Copy_u8PinNum);break;
		default ://error
			break;
		}
	}
}



