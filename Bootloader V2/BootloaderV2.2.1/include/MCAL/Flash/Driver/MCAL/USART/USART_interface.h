/*****************************************************************/
/* Author  : Dell                                                */
/* SWC     : USART                                               */
/* Version : 1.0                                                 */
/* Date    : 19 Sep 2023                                         */
/*****************************************************************/
#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_


void MUSART1_vidInit(void);
void MUSART1_vidTransmitt(u8* Copy_u8Data,u8 Copy_u8Length);

void MUSART1_vidReceive(u8* Copy_u8Data);
void MUSART1_vidDisable(void);

void MUSART1_vidCallBack(pf ptr);
#endif
