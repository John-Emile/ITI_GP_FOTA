/*
 * RCC_Interface.h
 *
 *  Created on: 2 Nov 2023
 *      Author: VGA!
 */

#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_


/***************** Buses *****************/
#define RCC_APB1				0
#define RCC_APB2				1
#define RCC_AHB1				2
#define RCC_AHB2				3


/**********************APB1************************/

#define RCC_APB1_TIM2			0
#define RCC_APB1_TIM3			1
#define RCC_APB1_TIM4			2
#define RCC_APB1_TIM5			3

#define RCC_APB1_WWDG			11

#define RCC_APB1_SPI2			14
#define RCC_APB1_SPI3			15

#define RCC_APB1_USART2			17

#define RCC_APB1_I2C1			21
#define RCC_APB1_I2C2			22
#define RCC_APB1_I2C3			23

#define RCC_APB1_PWR			28


/**********************APB2************************/


#define RCC_APB2_TIM1			0

#define RCC_APB2_USART1			4
#define RCC_APB2_USART6			5

#define RCC_APB2_ADC1			8

#define RCC_APB2_SDIO			11

#define RCC_APB2_SPI1			12
#define RCC_APB2_SPI4			13

#define RCC_APB2_SYSCFG			14

#define RCC_APB2_TIM9			16
#define RCC_APB2_TIM10			17
#define RCC_APB2_TIM11			18



/**********************AHB1************************/

#define RCC_AHB1_GPIOA			0
#define RCC_AHB1_GPIOB			1
#define RCC_AHB1_GPIOC			2
#define RCC_AHB1_GPIOD			3
#define RCC_AHB1_GPIOE			4
#define RCC_AHB1_GPIOH			7

#define RCC_AHB1_CRC			12
#define RCC_AHB1_FLS			15
#define RCC_AHB1_DMA1			21
#define RCC_AHB1_DMA2			22



/**********************AHB2************************/
#define RCC_AHB2_OTGFS			7




/*************************** RCC_CR ******************************/
#define RCC_CR_HSI_ON				0
#define RCC_CR_HSI_RDY				1

#define RCC_CR_HSI_TRIM0			3
#define RCC_CR_HSI_TRIM1			4
#define RCC_CR_HSI_TRIM2			5
#define RCC_CR_HSI_TRIM3			6
#define RCC_CR_HSI_TRIM4			7

#define RCC_CR_HSI_CAL0				8
#define RCC_CR_HSI_CAL1				9
#define RCC_CR_HSI_CAL2				10
#define RCC_CR_HSI_CAL3				11
#define RCC_CR_HSI_CAL4				12
#define RCC_CR_HSI_CAL5				13
#define RCC_CR_HSI_CAL6				14
#define RCC_CR_HSI_CAL7				15


#define RCC_CR_HSE_ON				16
#define RCC_CR_HSE_RDY				17

#define RCC_CR_HSE_BYP				18
#define RCC_CR_CSS_ON				19

#define RCC_CR_PLL_ON				24
#define RCC_CR_PLL_RDY				25
#define RCC_CR_PLLI2S_ON			26
#define RCC_CR_PLLI2S_RDY			27


/*************************** RCC_PLLCFGR ******************************/

#define RCC_PLLCFGR_PLLM0			0
#define RCC_PLLCFGR_PLLM1			1
#define RCC_PLLCFGR_PLLM2			2
#define RCC_PLLCFGR_PLLM3			3
#define RCC_PLLCFGR_PLLM4			4
#define RCC_PLLCFGR_PLLM5			5

#define RCC_PLLCFGR_PLLN0			6
#define RCC_PLLCFGR_PLLN1			7
#define RCC_PLLCFGR_PLLN2			8
#define RCC_PLLCFGR_PLLN3			9
#define RCC_PLLCFGR_PLLN4			10
#define RCC_PLLCFGR_PLLN5			11
#define RCC_PLLCFGR_PLLN6			12
#define RCC_PLLCFGR_PLLN7			13
#define RCC_PLLCFGR_PLLN8			14

#define RCC_PLLCFGR_PLLP0			16
#define RCC_PLLCFGR_PLLP1			17

#define RCC_PLLCFGR_PLLSRC			22

#define RCC_PLLCFGR_PLLQ0			24
#define RCC_PLLCFGR_PLLQ1			25
#define RCC_PLLCFGR_PLLQ2			26
#define RCC_PLLCFGR_PLLQ3			27


/*****************************APIs Prototypes*******************************/

void MRCC_voidInit(void);
void MRCC_Enable_Peripheral(u32 Copy_u32Address_Bus,u32 Copy_32Peripheral);
void MRCC_Disable_Peripheral(u32 Copy_u32Address_Bus,u32 Copy_32Peripheral);




#endif /* RCC_INTERFACE_H_ */
