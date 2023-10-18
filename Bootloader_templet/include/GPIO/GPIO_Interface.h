/*
 * GPIO_Interface.h
 *
 *  Created on: Sep 7, 2023
 *      Author: maykel
 */

#ifndef MCAL_GPIO_GPIO_INTERFACE_H_
#define MCAL_GPIO_GPIO_INTERFACE_H_

/*
 ******************************************************************
 ******************************************************************
 ***********************MCAL Components****************************
 ******************************************************************
 */

#include "GPIO_Private.h"
#include "GPIO_Config.h"

/*
 ******************************************************************
 ******************************************************************
 ***********************PORT Macros********************************
 ******************************************************************
 */

#define MGPIO_PORTA            0U
#define MGPIO_PORTB            1U
#define MGPIO_PORTC            2U
#define MGPIO_PORTD            3U
#define MGPIO_PORTE            4U
#define MGPIO_PORTF            5U
#define MGPIO_PORTG            6U
#define MGPIO_PORTH            7U



/*
 ******************************************************************
 ******************************************************************
 ***********************PIN Macros*********************************
 ******************************************************************
 */


#define MGPIO_PIN0              0U
#define MGPIO_PIN1              1U
#define MGPIO_PIN2              2U
#define MGPIO_PIN3              3U
#define MGPIO_PIN4              4U
#define MGPIO_PIN5              5U
#define MGPIO_PIN6              6U
#define MGPIO_PIN7              7U
#define MGPIO_PIN8              8U
#define MGPIO_PIN9              9U
#define MGPIO_PIN10             10U
#define MGPIO_PIN11             11U
#define MGPIO_PIN12             12U
#define MGPIO_PIN13             13U
#define MGPIO_PIN14             14U
#define MGPIO_PIN15             15U




/*
 ******************************************************************
 ******************************************************************
 ***********************MODE Macros********************************
 ******************************************************************
 */


#define MGPIO_MODE_INPUT			0b00
#define MGPIO_MODE_OUTPUT			0b01
#define MGPIO_MODE_ALTFUN			0b10
#define MGPIO_MODE_ANALOG			0b11




/*
 ******************************************************************
 ******************************************************************
 ***********************Types Macros*******************************
 ******************************************************************
 */

#define MGPIO_OUTPUT_TYPE_PUSH_PULL			(0U)
#define MGPIO_OUTPUT_TYPE_OPEN_DRAIN		(1U)




/*
 ******************************************************************
 ******************************************************************
 ***********************Speed Macros*******************************
 ******************************************************************
 */

#define MGPIO_OUTPUT_SPEED_LOW                      (0b00)
#define MGPIO_OUTPUT_SPEED_MEDIUM                   (0b01)
#define MGPIO_OUTPUT_SPEED_HIGH                  	(0b10)
#define MGPIO_OUTPUT_SPEED_VERY_HIGH                (0b11)

/*
 ******************************************************************
 ******************************************************************
 ***********************PULL State Macros**************************
 ******************************************************************
 */


#define MGPIO_PULL_FLOATING                          (0b00)
#define MGPIO_PULL_PULL_UP                           (0b01)
#define MGPIO_PULL_PULL_DOWN                         (0b10)







/*
 ******************************************************************
 ******************************************************************
 ***********************Write Data Macros**************************
 ******************************************************************
 */

#define MGPIO_HIGH							(1U)
#define MGPIO_LOW							(0U)



/*
 ******************************************************************
 ******************************************************************
 ***********************Alternate Function Macros******************
 ******************************************************************
 */

#define MGPIO_ALTFN0                        (0b0000)
#define MGPIO_ALTFN1                        (0b0001)
#define MGPIO_ALTFN2                        (0b0010)
#define MGPIO_ALTFN3                        (0b0011)
#define MGPIO_ALTFN4                        (0b0100)
#define MGPIO_ALTFN5                        (0b0101)
#define MGPIO_ALTFN6                        (0b0110)
#define MGPIO_ALTFN7                        (0b0111)
#define MGPIO_ALTFN8                        (0b1000)
#define MGPIO_ALTFN9                        (0b1001)
#define MGPIO_ALTFN10                       (0b1010)
#define MGPIO_ALTFN11                       (0b1011)
#define MGPIO_ALTFN12                       (0b1100)
#define MGPIO_ALTFN13                       (0b1101)
#define MGPIO_ALTFN14                       (0b1110)
#define MGPIO_ALTFN15                       (0b1111)



/*
 ******************************************************************
 ******************************************************************
 ***********************Function Prototypes************************
 ******************************************************************
 */




/*
 * ******************************************************************
 ***********************01-MGPIO_voidSetPinMode**********************
 *
 * 1- function description -> function set mode of the pin
 * 2-options : A)MGPIO_MODE_INPUT
 *             B)MGPIO_MODE_OUTPUT
 *             C)MGPIO_MODE_ALTFUN
 *             D)MGPIO_MODE_ANALOG
 * 3-function arguments : A) Copy_u8PortName : The port Number (ex MGPIO_PORTA,MGPIO_PORTB)
 * 						  B) Copy_u8PinNum   : The Pin Number (ex MGPIO_PIN0,MGPIO_PIN1)
 * 						  C) Copy_u8Mode     : The Mode (ex : MGPIO_MODE_INPUT)
 *
 * 4-Function Return -> void
 */
void MGPIO_voidSetPinMode (u8 Copy_u8PortName , u8 Copy_u8PinNum ,u8 Copy_u8Mode);

void MGPIO_voidSetPortMode (u8 Copy_u8PortName ,u32 Copy_u32OutputMode);//assignment

void MGPIO_voidSetOutputMode (u8 Copy_u8PortName , u8 Copy_u8PinNum ,u8 Copy_u8OutputMode);

void MGPIO_voidSetOutputSpeed (u8 Copy_u8PortName , u8 Copy_u8PinNum ,u8 Copy_u8OutputSpeed);

void MGPIO_voidSetPullState (u8 Copy_u8PortName , u8 Copy_u8PinNum ,u8 Copy_u8PullState);

u8 MGPIO_u8GetPinVal (u8 Copy_u8PortName , u8 Copy_u8PinNum );

void MGPIO_voidSetPinVal (u8 Copy_u8PortName , u8 Copy_u8PinNum ,u8 Copy_u8PinVal);

void MGPIO_voidDirectSetReset (u8 Copy_u8PortName , u8 Copy_u8PinNum ,u8 Copy_u8SetResetState);

void MGPIO_SetPortVal(u8 Copy_u8PortName ,u16 Copy_u16OutputValue);

u32 MGPIO_voidPinLock (u8 Copy_u8PortName , u8 Copy_u8PinNum );

void MGPIO_voidSetAltFun (u8 Copy_u8PortName , u8 Copy_u8PinNum ,u8 Copy_u8AltFun);

#endif /* MCAL_GPIO_GPIO_INTERFACE_H_ */
