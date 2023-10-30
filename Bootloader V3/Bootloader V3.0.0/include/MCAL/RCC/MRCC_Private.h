/********************************************************/
/* Description : RCC Driver Private File                */
/* Author      : Abdelrahman Tarek       				*/
/* Date        : 12:59:55   			   				*/
/* History     : 6 Sep 2023 			   				*/
/********************************************************/
#ifndef MRCC_PRIVATE_H_
#define MRCC_PRIVATE_H_


/*RCC base Address*/
#define RCC_BASE_ADDRESS (0x40023800)

/*RCC Register offset Created in struct*/
typedef struct
{
	u32 CR;
	u32 PLLCFGR;
	u32 CFGR;
	u32 CIR;
	u32 AHB1RSTR;
	u32 AHB2RSTR;
	u32 Reserved1;
	u32 Reserved2;
	u32 APB1RSTR;
	u32 APB2RSTR;
	u32 Reserved3;
	u32 Reserved4;
	u32 AHB1ENR;
	u32 AHB2ENR;
	u32 Reserved5;
	u32 Reserved6;
	u32 APB1ENR;
	u32 APB2ENR;
	u32 Reserved7;
	u32 Reserved8;
	u32 AHB1LPENR;
	u32 AHB2LPENR;
	u32 Reserved9;
	u32 Reserved10;
	u32 APB1LPENR;
	u32 APB2LPENR;
	u32 Reserved11;
	u32 Reserved12;
	u32 BDCR;
	u32 CSR;
	u32 Reserved13;
	u32 Reserved14;
	u32 SSCGR;
	u32 PLLI2SCFGR;
	u32 Reserved15;
	u32 DCKCFGR;
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
