/*****************************************************************/
/* Author  : Dell                                                */
/* SWC     : USART                                               */
/* Version : 1.0                                                 */
/* Date    : 19 Sep 2023                                         */
/*****************************************************************/
#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

/* SR register Bits */

#define PE							0
#define FE							1
#define NF							2
#define ORE							3
#define IDLE						4
#define RXNE						5
#define TC							6
#define TXE							7
#define LBD							8
#define CTS							9



/*********************************prototypes***********************************/
void MUSART1_vidInit(void);
void MUSART1_vidTransmitt(u8* Copy_u8Data);

void MUSART1_vidReceive(u8* Copy_u8Data);
void MUSART1_vidDisable(void);

tenuErrrorStatus MUSART1_vidReceiveAsync(u8* Copy_u8Data);

void MUSART1_vidCallBack(pf ptr);
#endif
