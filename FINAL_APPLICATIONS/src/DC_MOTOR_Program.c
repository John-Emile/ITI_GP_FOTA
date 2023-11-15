/*
 * DC_MOTOR_Program.c
 *
 *  Created on: 3 Nov 2023
 *      Author: VGA!
 */
#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_TYPES.h"
#include "../include/MCAL/GPIO/GPIO_Interface.h"
#include "../include/HAL/DC_MOTOR/DC_MOTOR_Interface.h"
#include "../include/HAL/DC_MOTOR/DC_MOTOR_Private.h"
#include "../include/HAL/DC_MOTOR/DC_MOTOR_Config.h"


void DcMotor_VoidInit(void)
{

	MGPIO_SetMode(MOTOR1_forward_PORT,MOTOR1_forward_PIN,OUTPUT);
	MGPIO_SetOutputPinMode(MOTOR1_forward_PORT,MOTOR1_forward_PIN,PUSH_PULL,LOW_SPEED);

	MGPIO_SetMode(MOTOR1_reverse_PORT,MOTOR1_reverse_PIN ,OUTPUT);
	MGPIO_SetOutputPinMode(MOTOR1_reverse_PORT,MOTOR1_reverse_PIN ,PUSH_PULL,LOW_SPEED);


	MGPIO_SetMode(MOTOR2_forward_PORT,MOTOR2_forward_PIN,OUTPUT);
	MGPIO_SetOutputPinMode(MOTOR2_forward_PORT,MOTOR2_forward_PIN,PUSH_PULL,LOW_SPEED);

	MGPIO_SetMode(MOTOR2_reverse_PORT,MOTOR2_reverse_PIN ,OUTPUT);
	MGPIO_SetOutputPinMode(MOTOR2_reverse_PORT,MOTOR2_reverse_PIN ,PUSH_PULL,LOW_SPEED);


}

void DcMotor_voidReverse(void)
{
	MGPIO_writePin(MOTOR1_forward_PORT,MOTOR1_forward_PIN,HIGH);
	MGPIO_writePin(MOTOR2_forward_PORT,MOTOR2_forward_PIN,HIGH);

	MGPIO_writePin(MOTOR1_reverse_PORT,MOTOR1_reverse_PIN ,LOW);
	MGPIO_writePin(MOTOR2_reverse_PORT,MOTOR2_reverse_PIN ,LOW);



}

void DcMotor_voidForward(void)
{
	MGPIO_writePin(MOTOR1_forward_PORT,MOTOR1_forward_PIN,LOW);
	MGPIO_writePin(MOTOR2_forward_PORT,MOTOR2_forward_PIN,LOW);

	MGPIO_writePin(MOTOR1_reverse_PORT,MOTOR1_reverse_PIN ,HIGH);
	MGPIO_writePin(MOTOR2_reverse_PORT,MOTOR2_reverse_PIN ,HIGH);


}

void DcMotor_voidTurnRight(void)
{
	MGPIO_writePin(MOTOR1_forward_PORT,MOTOR1_forward_PIN,LOW);
	MGPIO_writePin(MOTOR2_forward_PORT,MOTOR2_forward_PIN,HIGH);

	MGPIO_writePin(MOTOR1_reverse_PORT,MOTOR1_reverse_PIN ,HIGH);
	MGPIO_writePin(MOTOR2_reverse_PORT,MOTOR2_reverse_PIN ,LOW);

}


void DcMotor_voidTurnLeft(void)
{
	MGPIO_writePin(MOTOR1_forward_PORT,MOTOR1_forward_PIN,HIGH);
	MGPIO_writePin(MOTOR2_forward_PORT,MOTOR2_forward_PIN,LOW);

	MGPIO_writePin(MOTOR1_reverse_PORT,MOTOR1_reverse_PIN ,LOW);
	MGPIO_writePin(MOTOR2_reverse_PORT,MOTOR2_reverse_PIN ,HIGH);



}

void DcMotor_voidStop(void)
{
	MGPIO_writePin(MOTOR1_forward_PORT,MOTOR1_forward_PIN,LOW);
	MGPIO_writePin(MOTOR2_forward_PORT,MOTOR2_forward_PIN,LOW);

	MGPIO_writePin(MOTOR1_reverse_PORT,MOTOR1_reverse_PIN ,LOW);
	MGPIO_writePin(MOTOR2_reverse_PORT,MOTOR2_reverse_PIN ,LOW);


}



