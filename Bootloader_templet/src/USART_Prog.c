/*
 * USART_Prog.c
 *
 *  Created on: Sep 19, 2023
 *      Author: mayke
 */


#include "../include/LIB/Bit_Math.h"
#include "../include/LIB/STD_TYPES.h"
#include "../include/USART/USART_Interface.h"
#include<math.h>

u16 DIV_Mantissa=0;
u8 DIV_Fraction=0;

void BaudRateCalculations(u32 Copy_u32BaudRate)
{
	f64 L_USARTDIV=0;
	f32 frac=0;
	L_USARTDIV=((f32)Fclk/(8*Copy_u32BaudRate));
	DIV_Mantissa=(u16)L_USARTDIV;
	frac=(L_USARTDIV-((u16) L_USARTDIV))*16;
	DIV_Fraction=(((frac-((u16) frac)))>=0.5?((u16)((frac)+1)):((u16)frac));
}
void USART_voidInit(u32 Copy_u32BaudRate)
{
	//get BaudRate
	BaudRateCalculations(Copy_u32BaudRate);
	USART1->BRR=(DIV_Fraction);
	if(DIV_Fraction>15)
	{
		DIV_Mantissa=DIV_Mantissa+1;//(*DIV_Fraction>>4);
	}
	USART1->BRR=(USART1->BRR&0x000F);
	USART1->BRR|=(DIV_Mantissa<<4);

	SET_BIT(USART1->CR1,15);//oversampling by 8
	CLR_BIT(USART1->CR1,12);//1start,8data bits,n stop
	CLR_BIT(USART1->CR1,10);//parity control disabled
	//CLR_BIT(USART1->CR1,9);//even parity

	SET_BIT(USART1->CR1,3);//Transmitter enabled
	SET_BIT(USART1->CR1,2);//Receiver enabled

	CLR_BIT(USART1->CR2,13);//(1 stop bit),2 bits to control stop bit
	CLR_BIT(USART1->CR2,12);

}
void USART_voidEnable(void)
{
	SET_BIT(USART1->CR1,13);//enable usart
}
void USART_voidDisable(void)
{
	CLR_BIT(USART1->CR1,13);//disable usart
}
void USART_voidSend(u8 Copy_u8Data)
{
	//check flag
	//while (GET_BIT(USART1->SR,7)==0);//transmit data register empty
	USART1->DR=Copy_u8Data;
	while(GET_BIT(USART1->SR,6)==0);//transmit data completed
	CLR_BIT(USART1->SR,6);
}
u8 USART_voidRecieve(void)
{
	u8 L_Data=0;
	//check flag
	while (GET_BIT(USART1->SR,5)==0);
	L_Data=USART1->DR;
return L_Data;
}

void USART_voidSendString(u8*string)
{
	while(*string)
	{
		USART_voidSend(*string);
		string++;
	}
}
u8 USART_voidRecieveBuffer(u8*Copy_u8DataCome)
{
	u8 LOC_u8Status = 1 ;
	  if(GET_BIT(USART1->SR,5) == 1)
	  {
		  *Copy_u8DataCome = USART1->DR  ;
	  }
	  else
	  {
		  LOC_u8Status = 0 ;
	  }

	return  LOC_u8Status ;

}
