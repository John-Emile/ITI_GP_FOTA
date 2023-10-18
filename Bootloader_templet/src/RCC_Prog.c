/*
 * RCC_Prog.c
 *
 *  Created on: Sep 6, 2023
 *      Author: mayke
 */

#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/Bit_Math.h"

#include "../include/RCC/RCC_Interface.h"





void MRCC_VoidInit(void)
{
#if CLOCK_TYPE == HSI

	CLR_BIT(MRCC->RCC_CFGR,0);
	CLR_BIT(MRCC->RCC_CFGR,1);

	SET_BIT(MRCC->RCC_CR,0);

#elif CLOCK_TYPE == HSE

	SET_BIT(MRCC->RCC_CFGR,0);
	CLR_BIT(MRCC->RCC_CFGR,1);

	SET_BIT(MRCC->RCC_CR,16);

#elif CLOCK_TYPE == PLL
	CLR_BIT(MRCC->RCC_CFGR,0);
	SET_BIT(MRCC->RCC_CFGR,1);

	SET_BIT(MRCC->RCC_CR,24);

#endif
}
void MRCC_VoidEnablePeripherals(u8 cpy_u8PeripheralBus,u8 cpy_u8PeripheralNb)
{
	switch (cpy_u8PeripheralBus)
	{
	case AHB1_bus:
		SET_BIT(MRCC->RCC_AHB1ENR,cpy_u8PeripheralNb);
		break;
	case AHB2_bus:
		SET_BIT(MRCC->RCC_AHB2ENR,cpy_u8PeripheralNb);
		break;
	case APB1_bus:
		SET_BIT(MRCC->RCC_APB1ENR,cpy_u8PeripheralNb);
		break;
	case APB2_bus:
		SET_BIT(MRCC->RCC_APB2ENR,cpy_u8PeripheralNb);
		break;
	}

}
void MRCC_VoidDisablePeripherals(u8 cpy_u8PeripheralBus,u8 cpy_u8PeripheralNb)
{
	switch (cpy_u8PeripheralBus)
		{
		case AHB1_bus:
			CLR_BIT(MRCC->RCC_AHB1ENR,cpy_u8PeripheralNb);
			break;
		case AHB2_bus:
			CLR_BIT(MRCC->RCC_AHB2ENR,cpy_u8PeripheralNb);
			break;
		case APB1_bus:
			CLR_BIT(MRCC->RCC_APB1ENR,cpy_u8PeripheralNb);
			break;
		case APB2_bus:
			CLR_BIT(MRCC->RCC_APB2ENR,cpy_u8PeripheralNb);
			break;
		}
}
