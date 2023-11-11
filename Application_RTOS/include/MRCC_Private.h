/********************************************************/
/* Description : RCC Driver Private File                */
/* Author      : Abdelrahman Tarek       				*/
/* Date        : 12:59:55   			   				*/
/* History     : 6 Sep 2023 			   				*/
/********************************************************/
#ifndef MRCC_PRIVATE_H_
#define MRCC_PRIVATE_H_

#include"STD_Types.h"
/*RCC base Address*/
#define RCC_BASE_ADDRESS (0x40023800)

/*RCC Register offset Created in struct*/
typedef struct
{
	uint32 CR;
	uint32 PLLCFGR;
	uint32 CFGR;
	uint32 CIR;
	uint32 AHB1RSTR;
	uint32 AHB2RSTR;
	uint32 Reserved1;
	uint32 Reserved2;
	uint32 APB1RSTR;
	uint32 APB2RSTR;
	uint32 Reserved3;
	uint32 Reserved4;
	uint32 AHB1ENR;
	uint32 AHB2ENR;
	uint32 Reserved5;
	uint32 Reserved6;
	uint32 APB1ENR;
	uint32 APB2ENR;
	uint32 Reserved7;
	uint32 Reserved8;
	uint32 AHB1LPENR;
	uint32 AHB2LPENR;
	uint32 Reserved9;
	uint32 Reserved10;
	uint32 APB1LPENR;
	uint32 APB2LPENR;
	uint32 Reserved11;
	uint32 Reserved12;
	uint32 BDCR;
	uint32 CSR;
	uint32 Reserved13;
	uint32 Reserved14;
	uint32 SSCGR;
	uint32 PLLI2SCFGR;
	uint32 Reserved15;
	uint32 DCKCFGR;
}RCC_t;

/**/
#define RCC		((volatile RCC_t*)RCC_BASE_ADDRESS)


/********************* Clk options *********************/
#define RCC_HSI				0
#define RCC_HSE				1
#define RCC_PLL				2


/***************************System Clk****************************/
#define SWITCH_HSI			0
#define SWITCH_HSE			1
#define SWITCH_PLL			2
#define SWITCH_MASK			(0xFFFFFFFC)

#endif /* MRCC_PRIVATE_H_ */
