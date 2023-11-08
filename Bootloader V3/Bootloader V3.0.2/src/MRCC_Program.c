/********************************************************/
/* Description : RCC Driver Program File                */
/* Author      : Abdelrahman Tarek       				*/
/* Date        : 12:59:55   			   				*/
/* History     : 6 Sep 2023 			   				*/
/********************************************************/

#include <LIB/STD_Types.h>
#include <LIB/BIT_MATH.h>

#include <MCAL/RCC/MRCC_Config.h>
#include <MCAL/RCC/MRCC_Interface.h>
#include <MCAL/RCC/MRCC_Private.h>


/************************************************************************************
 * Service Name: MRCC_voidInit
 * Parameters (in): None
 * Return value: None
 * Description: initialize RCC clock.
 ************************************************************************************/

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


/************************************************************************************
 * Service Name: MRCC_Enable_Peripheral
 * Parameters (in): uint32 (Holds Bus addresss)
 * 					uint32 (Holds Peripheral address)
 * Return value: None
 * Description: Enable peripheral clock.
 ************************************************************************************/

void MRCC_Enable_Peripheral(u32 Copy_u32Address_Bus,u32 Copy_32Peripheral)
{
	/*Switch between Four Busses*/
	switch(Copy_u32Address_Bus)
	{
	case RCC_APB1:
		/*Set Enable flag of corresponding Peripheral to enable Peripheral clock */
		SET_BIT(RCC->APB1ENR,Copy_32Peripheral);
		break;

	case RCC_APB2:
		/*Set Enable flag of corresponding Peripheral to enable Peripheral clock */
		SET_BIT(RCC->APB2ENR,Copy_32Peripheral);
		break;

	case RCC_AHB1:
		/*Set Enable flag of corresponding Peripheral to enable Peripheral clock */
		SET_BIT(RCC->AHB1ENR,Copy_32Peripheral);
		break;

	case RCC_AHB2:
		/*Set Enable flag of corresponding Peripheral to enable Peripheral clock */
		SET_BIT(RCC->AHB2ENR,Copy_32Peripheral);
		break;
	default:
		// Do nothing
		break;
	}
}


/************************************************************************************
 * Service Name: MRCC_Disable_Peripheral
 * Parameters (in): uint32 (Holds Bus addresss)
 * 					uint32 (Holds Peripheral address)
 * Return value: None
 * Description: Disable peripheral clock.
 ************************************************************************************/

void MRCC_Disable_Peripheral(u32 Copy_u32Address_Bus,u32 Copy_32Peripheral)
{
	/*Switch between Four Busses*/
	switch(Copy_u32Address_Bus)
	{
	case RCC_APB1:
		/*Clear Enable flag of corresponding Peripheral to Disable Peripheral clock */
		CLR_BIT(RCC->APB1ENR,Copy_32Peripheral);
		break;

	case RCC_APB2:
		/*Clear Enable flag of corresponding Peripheral to Disable Peripheral clock */
		CLR_BIT(RCC->APB2ENR,Copy_32Peripheral);
		break;

	case RCC_AHB1:
		/*Clear Enable flag of corresponding Peripheral to Disable Peripheral clock */
		CLR_BIT(RCC->AHB1ENR,Copy_32Peripheral);
		break;

	case RCC_AHB2:
		/*Clear Enable flag of corresponding Peripheral to Disable Peripheral clock */
		CLR_BIT(RCC->AHB2ENR,Copy_32Peripheral);
		break;
	default:
		// Do nothing
		break;
	}
}
