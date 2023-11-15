/********************************************************/
/* Description : RCC Driver Program File                */
/* Author      : Abdelrahman Tarek       				*/
/* Date        : 12:59:55   			   				*/
/* History     : 6 Sep 2023 			   				*/
/********************************************************/


#include"STD_Types.h"
#include"BIT_Math.h"
#include"MRCC_Private.h"
#include"MRCC_Interface.h"

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
void MRCC_Enable_Peripheral(uint32 Copy_uint32Address_Bus,uint32 Copy_32Peripheral)
{
	switch(Copy_uint32Address_Bus)
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
void MRCC_Disable_Peripheral(uint32 Copy_uint32Address_Bus,uint32 Copy_32Peripheral)
{
	switch(Copy_uint32Address_Bus)
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
