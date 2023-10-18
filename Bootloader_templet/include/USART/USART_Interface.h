/*
 * USART_Interface.h
 *
 *  Created on: Sep 19, 2023
 *      Author: mayke
 */

#ifndef USART_USART_INTERFACE_H_
#define USART_USART_INTERFACE_H_

#include"USART_Config.h"
#include"USART_Private.h"


void USART_voidInit(u32 Copy_u32BaudRate);
void USART_voidEnable(void);
void USART_voidDisable(void);
void USART_voidSend(u8 Copy_u8Data);
u8 USART_voidRecieve(void);
void USART_voidSendString(u8*string);
u8 USART_voidRecieveBuffer(u8*Copy_u8DataCome);

#endif /* USART_USART_INTERFACE_H_ */
