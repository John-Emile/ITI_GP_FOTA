/*****************************************************************/
/* Author  : Dell                                                */
/* SWC     : USART                                               */
/* Version : 1.0                                                 */
/* Date    : 19 Sep 2023                                         */
/*****************************************************************/


#include <LIB/STD_Types.h>
#include <LIB/BIT_MATH.h>

#include <USART/USART_private.h>
#include <USART/USART_config.h>
#include <USART/USART_interface.h>


pf USART1_Callback = NULL_PTR;

void MUSART1_vidInit(void)
{
	/*Select Over sample for CR1 Register and Over8 bit*/
#if USART_OVER_SAMPLE	==	USART_OVER_8
	/*Set Over8 bit to configure Over sampling by 8*/
	USART1->CR1.OVER8 = USART_OVER_8;

	/*Set Mantissa value and Clear Fraction */
	USART1->BRR = 0x0;
	USART1->BRR |= (USART_1_DIV_Mantissa<<4) | ((~(0x8))&(USART_1_DIV_Fraction));

#elif USART_OVER_SAMPLE	==	USART_OVER_16
	/*Clear Over8 bit to configure Over sampling by 16*/
	USART1->CR1.OVER8 = USART_OVER_16;

	/*Set Mantissa value and Fraction */
	USART1->BRR = 0x0;
	USART1->BRR |= (USART_1_DIV_Mantissa<<4) | (USART_1_DIV_Fraction);
#else
#error "Wrong USART Over_sample"
#endif

	/**********************************************************************************************************************************/
	/*Select Data bit mode for CR1 Register and M bit*/
#if USART_WORD_SIZE == USART_MODE_8_BIT
	/*Clear M bit to configure 8 bit mode*/
	USART1->CR1.M = USART_MODE_8_BIT;

#elif USART_WORD_SIZE == USART_MODE_9_BIT
	/*Set M bit to configure 9 bit mode*/
	USART1->CR1.M = USART_MODE_9_BIT;


#else
#error "Wrong USART Word size"
#endif


	/**********************************************************************************************************************************/
	/*Select Parity mode */
#if USART_1_PARITY_MODE	 == USART_EVEN_PARITY
	/*Clear PS bit to configure Even Parity mode*/
	USART1->CR1.PS = USART_EVEN_PARITY;
	/*Enable parity check*/
	USART1->CR1.PCE = ENABLE;


#elif USART_1_PARITY_MODE == USART_ODD_PARITY
	/*Set PS bit to configure odd Parity mode*/
	USART1->CR1.PS = USART_EVEN_PARITY;
	/*Enable parity check*/
	USART1->CR1.PCE = ENABLE;

#elif USART_1_PARITY_MODE == USART_NO_PARITY
	/*Disable parity check*/
	USART1->CR1.PCE = DISABLE;
#else
#error "Wrong Parity mode"
#endif


	/*********************STOP BIT MODE************************/
#if USART_1_STOP_BIT_MODE	==	STOP_1BIT
	/*Clear Both Bits 12 and 13 To Access one stop bit mode*/
	CLR_BIT(USART1->CR2,12);
	CLR_BIT(USART1->CR2,13);

#elif USART_1_OVER_SAMPLE	==	STOP_2BIT
	/*Clear Bit 12 and Set Bit 13 To Access Two stop bit mode*/
	CLR_BIT(USART1->CR2,12);
	SET_BIT(USART1->CR2,13);
#else
#error "Wrong USART Over_sample"
#endif
}


void MUSART1_vidTransmitt(u8* Copy_u8Data,u8 Copy_u8Length)
{
	u32 Local_Counter;
	/*Set UE bit to Enable USART*/
	USART1->CR1.UE = 1 ;

	/*Enable Transmitter*/
	USART1->CR1.TE = ENABLE;
	for(Local_Counter = 0 ; Local_Counter<= Copy_u8Length ; Local_Counter++)
	{
		USART1->DR = Copy_u8Data[Local_Counter];
		while(!GET_BIT(USART1->SR,6));
	}
}

void MUSART1_vidReceive(u8* Copy_u8Data)
{
	/*Set UE bit to Enable USART*/
	USART1->CR1.UE = 1 ;

	/*Enable Receiver*/
	USART1->CR1.RE = ENABLE;

	while(!GET_BIT(USART1->SR,5));
	*Copy_u8Data = USART1->DR;
}



void MUSART1_vidDisable(void)
{
	/*Clear UE bit to Disable USART*/
	USART1->CR1.UE = 0 ;

}

void MUSART1_vidCallBack(pf ptr)
{
	USART1_Callback = ptr;
}


USART1_IRQHandler(void)
{
	if(USART1_Callback != NULL_PTR)
	{
		USART1_Callback();
	}
}



