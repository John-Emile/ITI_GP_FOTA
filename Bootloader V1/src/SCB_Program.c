/*
 * SCB_Program.c
 *
 *  Created on: Sep 11, 2023
 *      Author: adham
 */
#include <LIB/STD_Types.h>

#include <MCAL/SCB/SCB_Private.h>
#include <MCAL/SCB/SCB_interface.h>

void MCAL_SCB_VTOR_SetValue(u32 value)
{
	SCB->VTOR = value ;
}
