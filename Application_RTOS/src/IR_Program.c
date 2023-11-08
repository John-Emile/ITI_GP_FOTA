/*
 * IR_Program.c
 *
 *  Created on: 3 Nov 2023
 *      Author: VGA!
 */

#include"IR_Config.h"

void HIR_VoidInit(void)
{
	/* to init IR_Right   */
	MGPIO_SetMode(IR_RIGHT_PORT,IR_RIGHT_PIN,INPUT);
	MGPIO_SetInputPinType(IR_RIGHT_PORT,IR_RIGHT_PIN,PULL_UP);
	/* to init IR_Left   */
	MGPIO_SetMode(IR_LEFT_PORT ,IR_LEFT_PIN,INPUT);
	MGPIO_SetInputPinType(IR_LEFT_PORT ,IR_LEFT_PIN,PULL_UP);


}
uint8 HIR_RightState(void)
{
	//to read value of IR_RIGHT
   uint8 Local_uint8rightstate;
   MGPIO_readPin(IR_RIGHT_PORT,IR_RIGHT_PIN, &Local_uint8rightstate);
   return Local_uint8rightstate;

}
uint8 HIR_LeftState(void)
{
	//to read value of IR_LEFT
	uint8 Local_uint8leftstate;
	MGPIO_readPin(IR_LEFT_PORT ,IR_LEFT_PIN,&Local_uint8leftstate);

	return Local_uint8leftstate;

}



