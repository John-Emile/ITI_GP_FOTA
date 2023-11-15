/*
 * RCC_Program.c
 *
 *  Created on: 2 Nov 2023
 *      Author: VGA!
 */
#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_TYPES.h"

#include "../include/MCAL/RCC/RCC_Interface.h"
#include "../include/MCAL/RCC/RCC_Private.h"
#include "../include/MCAL/RCC/RCC_Config.h"


/************************************************************************************/
/* Init Function 																	*/
/************************************************************************************/
void MRCC_voidInit( void )
{
	#if (SYS_CLK == RCC_HSE)

	SET_BIT(RCC->CR, RCC_CR_HSE_ON);
	/* Check HSE Ready flag  */
	while(!GET_BIT(RCC->CR, RCC_CR_HSE_RDY));
	/* Switch to HSE */
	(RCC->CFGR) &= SWITCH_MASK;
	(RCC->CFGR) |= SWITCH_HSE;

	#elif (SYS_CLK == RCC_HSI)

	SET_BIT(RCC->CR, RCC_CR_HSI_ON);
	/* Check HSE Ready flag  */
	while(!GET_BIT(RCC->CR, RCC_CR_HSI_RDY));
	/* Switch to HSI */
	(RCC->CFGR) &= SWITCH_MASK;
	(RCC->CFGR) |= SWITCH_HSI;

	#elif (SYS_CLK == RCC_PLL)

	SET_BIT(RCC->CR, RCC_CR_PLL_ON);
	/* Check HSE Ready flag  */
	while(!GET_BIT(RCC->CR, RCC_CR_PLL_RDY));
	/* Switch to PLL */

	(RCC->CFGR) &= (SWITCH_MASK|SWITCH_PLL);
	(RCC->CFGR) |= SWITCH_PLL;

	#endif

}
/************************************************************************************/
/* Enable Function That take Bus address and Peripheral  need to be enable 			*/
/************************************************************************************/
void MRCC_Enable_Peripheral(u32 Copy_u32Address_Bus,u32 Copy_32Peripheral)
{
	switch(Copy_u32Address_Bus)
	{
	case RCC_APB1:
		SET_BIT(RCC->APB1ENR,Copy_32Peripheral);
		break;

	case RCC_APB2:
		SET_BIT(RCC->APB2ENR,Copy_32Peripheral);
		break;

	case RCC_AHB1:
		SET_BIT(RCC->AHB1ENR,Copy_32Peripheral);
		break;

	case RCC_AHB2:
		SET_BIT(RCC->AHB2ENR,Copy_32Peripheral);
		break;
	default:
		// Do nothing
		break;
	}
}


/************************************************************************************/
/* Disable Function That take Bus address and Peripheral  need to be Disable		*/
/************************************************************************************/
void MRCC_Disable_Peripheral(u32 Copy_u32Address_Bus,u32 Copy_32Peripheral)
{
	switch(Copy_u32Address_Bus)
	{
	case RCC_APB1:
		CLR_BIT(RCC->APB1ENR,Copy_32Peripheral);
		break;

	case RCC_APB2:
		CLR_BIT(RCC->APB2ENR,Copy_32Peripheral);
		break;

	case RCC_AHB1:
		CLR_BIT(RCC->AHB1ENR,Copy_32Peripheral);
		break;

	case RCC_AHB2:
		CLR_BIT(RCC->AHB2ENR,Copy_32Peripheral);
		break;
	default:
		// Do nothing
		break;
	}
}


