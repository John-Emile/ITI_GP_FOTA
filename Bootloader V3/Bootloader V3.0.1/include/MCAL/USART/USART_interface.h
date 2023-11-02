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

/************************************************************************************
 * Service Name: MUSART1_vidInit
 * Parameters (in): None
 * Return value: None
 * Description: initialize USART1 .
 ************************************************************************************/

void MUSART1_vidInit(void);

/************************************************************************************
 * Service Name: MUSART1_vidTransmit
 * Parameters (in): u8* (holds array of data)
 * Return value: None
 * Description: Send string using USART1 .
 ************************************************************************************/

void MUSART1_vidTransmitt(u8* Copy_u8Data);

/************************************************************************************
 * Service Name: MUSART1_vidReceive
 * Parameters (in): u8* (holds address of Local variable)
 * Return value: None
 * Description: Receive Data by polling in local variable using USART1 .
 ************************************************************************************/

void MUSART1_vidReceive(u8* Copy_u8Data);

/************************************************************************************
 * Service Name: MUSART1_vidDisable
 * Parameters (in): None
 * Return value: None
 * Description: Disable USART1 .
 ************************************************************************************/

void MUSART1_vidDisable(void);

/************************************************************************************
 * Service Name: MUSART1_vidDisable
 * Parameters (in): None
 * Return value: None
 * Description: Disable USART1 .
 ************************************************************************************/

tenuErrrorStatus MUSART1_vidReceiveAsync(u8* Copy_u8Data);

/************************************************************************************
 * Service Name: MUSART1_vidCallBack
 * Parameters (in): pf (hold address of callback Function in main)
 * Return value: None
 * Description: Set the address of callback Function in main in Global pf.
 ************************************************************************************/

void MUSART1_vidCallBack(pf ptr);
#endif
