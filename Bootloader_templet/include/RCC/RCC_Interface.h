/*
 * RCC_Interface.h
 *
 *  Created on: Sep 6, 2023
 *      Author: mayke
 */

#ifndef MCAL_RCC_RCC_INTERFACE_H_
#define MCAL_RCC_RCC_INTERFACE_H_

#include "../include/RCC/RCC_Config.h"
#include "../include/RCC/RCC_Private.h"

void MRCC_VoidInit(void);
void MRCC_VoidEnablePeripherals(u8 cpy_u8PeripheralBus,u8 cpy_u8PeripheralNb);
void MRCC_VoidDisablePeripherals(u8 cpy_u8PeripheralBus,u8 cpy_u8PeripheralNb);

#define HSI			0
#define HSE			1
#define PLL			2

#define	AHB1_bus	0
#define AHB2_bus	1
#define APB1_bus	2
#define APB2_bus	3


#endif /* MCAL_RCC_RCC_INTERFACE_H_ */
