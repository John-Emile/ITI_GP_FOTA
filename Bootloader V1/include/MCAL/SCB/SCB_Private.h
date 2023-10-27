/*
 * SCB_Private.h
 *
 *  Created on: Sep 11, 2023
 *      Author: adham
 */

#ifndef MCAL_SCB_SCB_PRIVATE_H_
#define MCAL_SCB_SCB_PRIVATE_H_
/*****************************File Includes**************************************/
#include <LIB/STD_Types.h>
/********************************************************************************/

/*****************************SCB Base Address***********************************/
#define SCB_BASE_ADDRESS		0xE000ED00
/********************************************************************************/

/*****************************Registers Structure********************************/
typedef struct
{
volatile u32 CPUID ;
volatile u32 ICSR  ;
volatile u32 VTOR  ;
volatile u32 AIRCR ;
volatile u32 SCR   ;
volatile u32 CCR   ;
volatile u32 SHPR1 ;
volatile u32 SHPR2 ;
volatile u32 SHPR3 ;
volatile u32 SHCSR ;
volatile u32 CFSR  ;
volatile u32 HFSR  ;
volatile u32 MMAR  ;
volatile u32 BFAR  ;
volatile u32 AFSR  ;
}SCB_Registers_t;

/*****************************Peripheral Instance*********************************/
#define SCB			((volatile SCB_Registers_t*)SCB_BASE_ADDRESS)
/*********************************************************************************/
#endif /* MCAL_SCB_SCB_PRIVATE_H_ */
