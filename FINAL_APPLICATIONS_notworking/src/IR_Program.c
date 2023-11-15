/*
 * IR_Program.c
 *
 *  Created on: 3 Nov 2023
 *      Author: VGA!
 */
#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_TYPES.h"
#include "../include/MCAL/GPIO/GPIO_Interface.h"
#include "../include/HAL/IR/IR_Interface.h"
#include "../include/HAL/IR/IR_Private.h"
#include "../include/HAL/IR/IR_Config.h"
void HIR_VoidInit(void)
{
	/* to init IR_Right   */
	MGPIO_SetMode(IR_RIGHT_PORT,IR_RIGHT_PIN,INPUT);
	MGPIO_SetInputPinType(IR_RIGHT_PORT,IR_RIGHT_PIN,NO_PULL_UP_DOWN);
	/* to init IR_Left   */
	MGPIO_SetMode(IR_LEFT_PORT ,IR_LEFT_PIN,INPUT);
	MGPIO_SetInputPinType(IR_LEFT_PORT ,IR_LEFT_PIN,NO_PULL_UP_DOWN);


}
u8 HIR_RightState(void)
{
	//to read value of IR_RIGHT
   u8 Local_u8rightstate;
   MGPIO_readPin(IR_RIGHT_PORT,IR_RIGHT_PIN, &Local_u8rightstate);
   return Local_u8rightstate;

}
u8 HIR_LeftState(void)
{
	//to read value of IR_LEFT
	u8 Local_u8leftstate;
	MGPIO_readPin(IR_LEFT_PORT ,IR_LEFT_PIN,&Local_u8leftstate);

	return Local_u8leftstate;

}



