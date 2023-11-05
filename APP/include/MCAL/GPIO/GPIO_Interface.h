/*
 * GPIO_Interface.h
 *
 *  Created on: 2 Nov 2023
 *      Author: VGA!
 */

#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_
/*********************************************Alternate_Function_Selections**************************************/
#define TIM1
#define TIM2

/*************************************************PORTS**********************************************************/
#define PORTA           0
#define PORTB           1
#define PORTC           2

/*********************************************Pins_Ports*******************************************************/
#define PIN0           0
#define PIN1           1
#define PIN2           2
#define PIN3           3
#define PIN4           4
#define PIN5           5
#define PIN6           6
#define PIN7           7
#define PIN8           8
#define PIN9           9
#define PIN10          10
#define PIN11          11
#define PIN12          12
#define PIN13          13
#define PIN14          14
#define PIN15          15

/*********************************************Mode_Pin*******************************************************/
#define INPUT          0
#define OUTPUT         1
#define ALTERNATE      2
#define ANALOG         3

/********************************************Pin Value******************************************************/
#define HIGH           1
#define LOW            0

/******************************************OutputType********************************************************/
#define PUSH_PULL      0
#define OPEN_DRAIN     1

/*****************************************SpeedValues**********************************************************/
#define LOW_SPEED        0
#define MEDIUM_SPEED     1
#define HIGH_SPEED       2
#define VERY_HIGH_SPEED  3

/****************************************InputType*************************************************************/
#define NO_PULL_UP_DOWN    0
#define PULL_UP            1
#define PULL_DOWN          2

/*****************************************Set_ResetValues******************************************************/
#define OUPUT_SET         0
#define OUTPUT_RESET      1

/********************************************Function Prototypes*********************************************/
/* Function to choose the mode of the mode whether output or input or analog mode or alternate */
void MGPIO_SetMode(u8 u8PortCPY,u8 u8pinCPY,u8 u8ModeCPY);
/*Function to choose if the output pin is push-pull or open drain and the speed */
void MGPIO_SetOutputPinMode(u8 u8PortCPY, u8 u8pinCPY, u8 u8OutTypeCPY,u8 u8SpeedTypeCPY);
/*Function to choose if the input pin is pull up or pull down*/
void MGPIO_SetInputPinType(u8 u8PortCPY, u8 u8pinCPY,u8 u8InputModeCPY);
void MGPIO_readPin(u8 u8PortCPY,u8 u8pinCPY,u8 * PinValCPY);
void MGPIO_writePin(u8 u8PortCPY,u8 u8pinCPY,u8 u8PinValCPY);
/*function to set and reset the pin value*/
void MGPIO_SetResetValue(u8 u8PortCPY,u8 u8pinCPY, u8 u8SetOrResetCPY);
void MGPIO_SetAlternativeFuncPin(u8 Copy_u8Port,u8 Copy_u8Pin,u8  Copy_u8Data);





#endif /* GPIO_INTERFACE_H_ */
