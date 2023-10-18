/*
 * USART_Private.h
 *
 *  Created on: Sep 19, 2023
 *      Author: mayke
 */

#ifndef USART_USART_PRIVATE_H_
#define USART_USART_PRIVATE_H_


//#define BaudRateSpeed(Copy_u32BaudRate)			(f32)((Fclk)/(8*Copy_u32BaudRate)));
#define USART1EN			4U
#define USART1_BASE_ADDRESS  (0x40011000)

typedef struct
{
volatile u32 SR;
volatile u32 DR;
volatile u32 BRR;
volatile u32 CR1;
volatile u32 CR2;
volatile u32 GTPT;

}USART;

#define   USART1      ((volatile USART  *)USART1_BASE_ADDRESS)



#endif /* USART_USART_PRIVATE_H_ */
