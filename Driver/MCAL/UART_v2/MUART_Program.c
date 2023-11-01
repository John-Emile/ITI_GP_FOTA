/**********************************************************************************************
 * Description :UART driver
 * Date : 10/12/2023
 * Author : Aya Ahmed Samir
 ************************************************************************************************/

#include"../include/BIT_Math.h"
#include"../include/STD_Types.h"
#include"../include/MAURT_private.h"
#include"../include/MUART_interface.h"
#include"MUART_Config.h"

void MUART_voidInit(void)
{
	/**********************************************FOR UART1 ***************************************************/

	/*To select the baud-rate and assign the value of mantissa and div_fraction*/
#if UART1_STATUES==UART_ENABLE

#if UART_BADURATE==9600
	/*if over sample_16 so over_8=0, When OVER8=0, the fractional part is coded on 4 bits*/
#if UART_OVER8==UART_OVRSMPL_16
	UART1->CR1.OVER8=LOW;
	UART1->USART_BRR=0;
	UART1->USART_BRR |= ( (DIV_MANTISSA_9600_OVER8_0) << 4 ) | (DIV_FRACTION_9600_OVER8_0);
	/*if over sample_8 so over_8=1, When OVER8=1, the fractional part is coded on 3 bits*/
#elif UART_OVER8==UART_OVRSMPL_8
	UART1->CR1.OVER8=HIGH;
	UART1->USART_BRR=0;
	UART1->USART_BRR |= ( (DIV_MANTISSA_9600_OVER8_0) <<4 ) | (DIV_FRACTION_9600_OVER8_0 & (0x7));
#endif
#endif

	/*To select the data length*/
#if UART_DATA_SIZE==UART_8_BITS
	UART1->CR1.M=LOW;
#elif UART_DATA_SIZE==UART_9_BITS
	UART1->CR1.M=HIGH;
#endif

	/*To select the clock polarity*/
#if UART_CLK_POLARITY==UART_CLK_POL_LOW
	CLR_BIT(UART1->USART_CR2,CLK_POL);
#elif UART_CLK_POLARITY==UART_CLK_POL_HIGH
	SET_BIT(UART1->USART_CR2,CLK_POL);
#endif

	/*To select the clock phase*/
#if UART_CLK_PHASE==UART_CLK_PH_FIRST
	CLR_BIT(UART1->USART_CR2,CLK_PH);
#elif UART_CLK_PHASE==UART_CLK_PH_SECOND
	SET_BIT(UART1->USART_CR2,CLK_PH);
#endif

	/*To select the stop bits*/
#if UART_STOP_BITS==UART_1_STOP_BIT
	CLR_BIT(UART1->USART_CR2,12);
	CLR_BIT(UART1->USART_CR2,13);
#elif UART_STOP_BITS==UART_2_STOP_BIT
	UART1->USART_CR2 |= (TWO_STOP << 12);
#endif

	/*To select the parity control*/
#if UART_PARITY_CNTRL==UART_PARITY_DIS
	UART1->CR1.PCE=LOW;
#elif UART_PARITY_CNTRL==UART_PARITY_EN
	UART1->CR1.PCE=HIGH;
	/*If the parity is enabled, select whether it is even or odd parity*/
#if UART_PARITY_SELC==UART_PARITY_EVEN
	UART1->CR1.PS=LOW;
#elif UART_PARITY_SELC==UART_PARITY_ODD
	UART1->CR1.PS=HIGH;
#endif

#endif

	/*To enable the UART*/
	UART1->CR1.UE=HIGH;
	/*To enable the transmitter*/
	UART1->CR1.TE=HIGH;
	/*To enable the receiver*/
	UART1->CR1.RE=HIGH;

#elif UART1_STATUES==UART_DISABLE
	UART1->CR1.TE=LOW;
	UART1->CR1.RE=LOW;
	UART1->CR1.UE=LOW;
#endif

	/**********************************************FOR UART2 ***************************************************/

	/*To select the baud-rate and assign the value of mantissa and div_fraction*/
#if UART2_STATUES==UART_ENABLE

#if UART_BADURATE==9600
	/*if over sample_16 so over_8=0, When OVER8=0, the fractional part is coded on 4 bits*/
#if UART_OVER8==UART_OVRSMPL_16
	UART2->CR1.OVER8=LOW;
	UART2->USART_BRR |= ( (DIV_MANTISSA_9600_OVER8_0) << 4 ) | (DIV_FRACTION_9600_OVER8_0);
	/*if over sample_8 so over_8=1, When OVER8=1, the fractional part is coded on 3 bits*/
#elif UART_OVER8==UART_OVRSMPL_8
	UART2->CR1.OVER8=HIGH;
	UART2->USART_BRR |= ( (DIV_MANTISSA_9600_OVER8_0) <<4 ) | (DIV_FRACTION_9600_OVER8_0 & (0x7));
#endif
#endif

	/*To select the data length*/
#if UART_DATA_SIZE==UART_8_BITS
	UART2->CR1.M=LOW;
#elif UART_DATA_SIZE==UART_9_BITS
	UART2->CR1.M=HIGH;
#endif

	/*To select the clock polarity*/
#if UART_CLK_POLARITY==UART_CLK_POL_LOW
	CLR_BIT(UART2->USART_CR2,CLK_POL);
#elif UART_CLK_POLARITY==UART_CLK_POL_HIGH
	SET_BIT(UART2->USART_CR2,CLK_POL);
#endif

	/*To select the clock phase*/
#if UART_CLK_PHASE==UART_CLK_PH_FIRST
	CLR_BIT(UART2->USART_CR2,CLK_PH);
#elif UART_CLK_PHASE==UART_CLK_PH_SECOND
	SET_BIT(UART2->USART_CR2,CLK_PH);
#endif

	/*To select the stop bits*/
#if UART_STOP_BITS==UART_1_STOP_BIT
	UART2->USART_CR2 |= (ONE_STOP <<12);
#elif UART_STOP_BITS==UART_2_STOP_BIT
	UART2->USART_CR2 |= (TWO_STOP << 12);
#endif

	/*To select the parity control*/
#if UART_PARITY_CNTRL==UART_PARITY_DIS
	UART2->CR1.PCE=LOW;
#elif UART_PARITY_CNTRL==UART_PARITY_EN
	UART2->CR1.PCE=HIGH;
	/*If the parity is enabled, select whether it is even or odd parity*/
#if UART_PARITY_SELC==UART_PARITY_EVEN
	UART2->CR1.PS=LOW;
#elif UART_PARITY_SELC==UART_PARITY_ODD
	UART2->CR1.PS=HIGH;
#endif

#endif

	/*To enable the UART*/
	UART2->CR1.UE=HIGH;
	/*To enable the transmitter*/
	UART2->CR1.TE=HIGH;
	/*To enable the receiver*/
	UART2->CR1.RE=HIGH;

#elif UART1_STATUES==UART_DISABLE
	UART2->CR1.TE=LOW;
	UART2->CR1.RE=LOW;
	UART2->CR1.UE=LOW;
#endif

	/**********************************************FOR UART6 ***************************************************/

	/*To select the baud-rate and assign the value of mantissa and div_fraction*/
#if UART6_STATUES==UART_ENABLE

#if UART_BADURATE==9600
	/*if over sample_16 so over_8=0, When OVER8=0, the fractional part is coded on 4 bits*/
#if UART_OVER8==UART_OVRSMPL_16
	UART6->CR1.OVER8=LOW;
	UART6->USART_BRR |= ( (DIV_MANTISSA_9600_OVER8_0) << 4 ) | (DIV_FRACTION_9600_OVER8_0);
	/*if over sample_8 so over_8=1, When OVER8=1, the fractional part is coded on 3 bits*/
#elif UART_OVER8==UART_OVRSMPL_8
	UART6->CR1.OVER8=HIGH;
	UART6->USART_BRR |= ( (DIV_MANTISSA_9600_OVER8_0) <<4 ) | (DIV_FRACTION_9600_OVER8_0 & (0x7));
#endif
#endif

	/*To select the data length*/
#if UART_DATA_SIZE==UART_8_BITS
	UART6->CR1.M=LOW;
#elif UART_DATA_SIZE==UART_9_BITS
	UART6->CR1.M=HIGH;
#endif

	/*To select the clock polarity*/
#if UART_CLK_POLARITY==UART_CLK_POL_LOW
	CLR_BIT(UART6->USART_CR2,CLK_POL);
#elif UART_CLK_POLARITY==UART_CLK_POL_HIGH
	SET_BIT(UART6->USART_CR2,CLK_POL);
#endif

	/*To select the clock phase*/
#if UART_CLK_PHASE==UART_CLK_PH_FIRST
	CLR_BIT(UART6->USART_CR2,CLK_PH);
#elif UART_CLK_PHASE==UART_CLK_PH_SECOND
	SET_BIT(UART6->USART_CR2,CLK_PH);
#endif

	/*To select the stop bits*/
#if UART_STOP_BITS==UART_1_STOP_BIT
	UART6->USART_CR2 |= (ONE_STOP <<12);
#elif UART_STOP_BITS==UART_2_STOP_BIT
	UART6->USART_CR2 |= (TWO_STOP << 12);
#endif

		/*To select the parity control*/
#if UART_PARITY_CNTRL==UART_PARITY_DIS
	UART6->CR1.PCE=LOW;
#elif UART_PARITY_CNTRL==UART_PARITY_EN
	UART6->CR1.PCE=HIGH;
	/*If the parity is enabled, select whether it is even or odd parity*/
#if UART_PARITY_SELC==UART_PARITY_EVEN
	UART6->CR1.PS=LOW;
#elif UART_PARITY_SELC==UART_PARITY_ODD
	UART6->CR1.PS=HIGH;
#endif

#endif

		/*To enable the UART*/
	UART6->CR1.UE=HIGH;
	/*To enable the transmitter*/
	UART6->CR1.TE=HIGH;
	/*To enable the receiver*/
	UART6->CR1.RE=HIGH;

#elif UART1_STATUES==UART_DISABLE
	UART6->CR1.TE=LOW;
	UART6->CR1.RE=LOW;
	UART6->CR1.UE=LOW;
#endif

}

void MUART_Transmit(uint8* u8DataCPY,uint8 u8UART_Number_CPY)
{

	uint32 u32i=0;

	if(u8UART_Number_CPY==UART_1)
	{
	while(u8DataCPY[u32i] !='\0')
	 {
		 UART1->USART_DR=u8DataCPY[u32i];
		 // wait till the  Transmission completes//
		 while(GET_BIT(UART1->USART_SR,T_COMPLETE)==LOW){}
		 u32i++;
	 }
	}

	else if(u8UART_Number_CPY==UART_2)
	{
		while(u8DataCPY[u32i] !='\0')
		{
			UART2->USART_DR=u8DataCPY[u32i];
			// wait till the  Transmission completes//
			while(GET_BIT(UART2->USART_SR,T_COMPLETE)==LOW){}
			u32i++;
		}
	}

	else if(u8UART_Number_CPY==UART_6)
	{
		while(u8DataCPY[u32i] !='\0')
		{
			UART6->USART_DR=u8DataCPY[u32i];
			// wait till the  Transmission completes//
			while(GET_BIT(UART6->USART_SR,T_COMPLETE)==LOW){}
			u32i++;
		}
	}

}

void MUART_Recieve(uint8* u8DataCPY,uint8 u8UART_Number_CPY)
{
	if(u8UART_Number_CPY==UART_1)
	{
		while(GET_BIT(UART1->USART_SR,READ_REG_NOT_EMPTY)==0);
		*u8DataCPY = UART1->USART_DR;
	}
	else if(u8UART_Number_CPY==UART_2)
	{
		while(GET_BIT(UART2->USART_SR,READ_REG_NOT_EMPTY)==0);
		*u8DataCPY = UART2->USART_DR;
	}
	else if(u8UART_Number_CPY==UART_6)
	{
		while(GET_BIT(UART6->USART_SR,READ_REG_NOT_EMPTY)==0);
		*u8DataCPY = UART6->USART_DR;
	}

}

uint8 MUART_RecieveAsynch(uint8 *u8Data_CPY,uint8 u8UART_Number_CPY)
{
	uint8 u8statuesLOCAL=1; // a variable to check if there is anything received by UART or not//
	/*Check which UART to receive from*/
	if(u8UART_Number_CPY==UART_1)
	{
		//Check if received data is ready to be read//
	if(GET_BIT(UART1->USART_SR,READ_REG_NOT_EMPTY)==HIGH)
	{
		*u8Data_CPY=UART1->USART_DR; /* put the data in the data register in the
		                               variable passed to the function*/
	}
	else
	{
		/*if nothing received by uart , make the variable =0 and return the variable*/
		u8statuesLOCAL=0;
	}
	}

	else if(u8UART_Number_CPY==UART_2)
	{
		if(GET_BIT(UART2->USART_SR,READ_REG_NOT_EMPTY)==HIGH)
		{
			*u8Data_CPY=UART2->USART_DR; /* put the data in the data register in the
				                               variable passed to the function*/
		}
		else
		{
			/*if nothing received by uart , make the variable =0 and return the variable*/
			u8statuesLOCAL=0;
		}

	}

	else if(u8UART_Number_CPY==UART_6)
	{
		if(GET_BIT(UART6->USART_SR,READ_REG_NOT_EMPTY)==HIGH)
		{
			*u8Data_CPY=UART6->USART_DR; /* put the data in the data register in the
						                               variable passed to the function*/
		}
		else
		{
			/*if nothing received by uart , make the variable =0 and return the variable*/
			u8statuesLOCAL=0;
		}
	}

	return u8statuesLOCAL;

}


