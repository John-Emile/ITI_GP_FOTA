/*****************************************************************/
/* Author  : Dell                                                */
/* SWC     : USART                                               */
/* Version : 1.0                                                 */
/* Date    : 19 Sep 2023                                         */
/*****************************************************************/


#include <LIB/STD_Types.h>
#include <LIB/BIT_MATH.h>

#include <MCAL/USART/USART_config.h>
#include <MCAL/USART/USART_interface.h>
#include <MCAL/USART/USART_private.h>


pf USART1_Callback = NULL_PTR;

/************************************************************************************
 * Service Name: MUSART1_vidInit
 * Parameters (in): None
 * Return value: None
 * Description: initialize USART1 .
 ************************************************************************************/

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

	/*Set UE bit to Enable USART*/
		USART1->CR1.UE = 1 ;

		/*Enable Receiver*/
		USART1->CR1.RE = ENABLE;
}


/************************************************************************************
 * Service Name: MUSART1_vidTransmit
 * Parameters (in): u8* (holds array of data)
 * Return value: None
 * Description: Send string using USART1 .
 ************************************************************************************/

void MUSART1_vidTransmit(u8* Copy_u8Data)
{
	u32 Local_Counter=0;
	/*Set UE bit to Enable USART*/
	USART1->CR1.UE = 1 ;

	/*Enable Transmitter*/
	USART1->CR1.TE = ENABLE;
	while(Copy_u8Data[Local_Counter] != '\0')
	{
		USART1->DR = Copy_u8Data[Local_Counter];
		while(!GET_BIT(USART1->SR,6));
		Local_Counter++;
	}

}


/************************************************************************************
 * Service Name: MUSART1_vidReceive
 * Parameters (in): u8* (holds address of Local variable)
 * Return value: None
 * Description: Receive Data by polling in local variable using USART1 .
 ************************************************************************************/

void MUSART1_vidReceive(u8* Copy_u8Data)
{
	/*Set UE bit to Enable USART*/
	USART1->CR1.UE = 1 ;

	/*Enable Receiver*/
	USART1->CR1.RE = ENABLE;

	while(!GET_BIT(USART1->SR,RXNE));
	*Copy_u8Data = USART1->DR;
}


/************************************************************************************
 * Service Name: MUSART1_vidReceiveAsync
 * Parameters (in): u8* (holds address of Local variable)
 * Return value: tenuErrrorStatus (return error state of the function)
 * Description: Receive Data Asynchronous in local variable using USART1 .
 ************************************************************************************/

tenuErrrorStatus MUSART1_vidReceiveAsync(u8* Copy_u8Data)
{
	tenuErrrorStatus ReturnErrorstate=ENOK;

	if(GET_BIT(USART1->SR,RXNE) == 1)
	{
		*Copy_u8Data = USART1->DR;
		ReturnErrorstate=EOK;
	}
	else
	{
		ReturnErrorstate=ENOK;
	}

	return ReturnErrorstate;
}

/************************************************************************************
 * Service Name: MUSART1_vidDisable
 * Parameters (in): None
 * Return value: None
 * Description: Disable USART1 .
 ************************************************************************************/

void MUSART1_vidDisable(void)
{
	/*Clear UE bit to Disable USART*/
	USART1->CR1.UE = 0 ;
}


/************************************************************************************
 * Service Name: MUSART1_vidCallBack
 * Parameters (in): pf (hold address of callback Function in main)
 * Return value: None
 * Description: Set the address of callback Function in main in Global pf.
 ************************************************************************************/

void MUSART1_vidCallBack(pf ptr)
{
	/*Set UE to enable USART Read data buffer interrupt */
	USART1->CR1.RXNEIE = 1 ;

	USART1_Callback = ptr;
}

/************************************************************************************
 * Service Name: USART1_IRQHandler
 * Parameters (in): None
 * Return value: None
 * Description: ISR run Global pf when an interrupt occurs.
 ************************************************************************************/
void __attribute__ ((weak, alias ("Default_Handler")))
USART1_IRQHandler(void)
{
	USART1_Callback();
	GET_BIT(USART1->SR,RXNE);
}



