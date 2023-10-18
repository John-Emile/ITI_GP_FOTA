/*
 * RCC_Private.h
 *
 *  Created on: Sep 6, 2023
 *      Author: mayke
 */

#ifndef MCAL_RCC_RCC_PRIVATE_H_
#define MCAL_RCC_RCC_PRIVATE_H_

#define RCC_BASE_ADDRESS	0x40023800


typedef struct
{
	volatile u32 RCC_CR;
	volatile u32 RCC_PLLCFGR;
	volatile u32 RCC_CFGR;
	volatile u32 RCC_CIR;
	volatile u32 RCC_AHB1RSTR;
	volatile u32 RCC_AHB2RSTR;
	volatile u32 RESERVED1;
	volatile u32 RESERVED2;

	volatile u32 RCC_APB1RSTR;
	volatile u32 RCC_APB2RSTR;

	volatile u32 RESERVED3;
	volatile u32 RESERVED4;

	volatile u32 RCC_AHB1ENR;
	volatile u32 RCC_AHB2ENR;

	volatile u32 RESERVED5;
	volatile u32 RESERVED6;

	volatile u32 RCC_APB1ENR;
	volatile u32 RCC_APB2ENR;

	volatile u32 RESERVED7;
	volatile u32 RESERVED8;

	volatile u32 RCC_AHB1LPENR;
	volatile u32 RCC_AHB2LPENR;

	volatile u32 RESERVED9;
	volatile u32 RESERVED10;

	volatile u32 RCC_APB1LPENR;
	volatile u32 RCC_APB2LPENR;

	volatile u32 RESERVED11;
	volatile u32 RESERVED12;

	volatile u32 RCC_BDCR;
	volatile u32 RCC_CSR;
	volatile u32 RCC_SSCGR;
	volatile u32 RCC_PLLI2SCFGR;

	volatile u32 RESERVED13;
	volatile u32 RCC_DCKCFGR;
}RCC;

#define MRCC ((volatile RCC *)RCC_BASE_ADDRESS)

#endif /* MCAL_RCC_RCC_PRIVATE_H_ */
