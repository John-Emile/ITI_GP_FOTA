#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_TYPES.h"

#include "../include/MCAL/RCC/RCC_Interface.h"
#include "../include/MCAL/GPIO/GPIO_Interface.h"
#include "../include/MCAL/UART/UART_Interface.h"
#include "../include/HAL/IR/IR_Interface.h"
#include "../include/HAL/DC_MOTOR/DC_MOTOR_Interface.h"

u8 Local_u8Mode;

int main()
{
	MRCC_voidInit();
	/* for APP*/
	MRCC_Enable_Peripheral(RCC_AHB1,RCC_AHB1_GPIOB);
	MRCC_Enable_Peripheral(RCC_AHB1,RCC_AHB1_GPIOC);
	//For UART2//
	MRCC_Enable_Peripheral(RCC_AHB1,RCC_AHB1_GPIOA);
	MRCC_Enable_Peripheral(RCC_APB1,RCC_APB1_USART2);

	//PA2=(TX2)connect to RX in Bluetooth  ********** PA3=(RX2) connect to TX in Bluetooth

	//For UART2//
	MGPIO_SetMode(PORTA,PIN2,ALTERNATE);
	MGPIO_SetMode(PORTA,PIN3,ALTERNATE);
	MGPIO_SetAlternativeFuncPin(PORTA,PIN2,7);
	MGPIO_SetAlternativeFuncPin(PORTA,PIN3,7);


	MGPIO_SetMode(PORTC,PIN15,OUTPUT);
	MGPIO_SetOutputPinMode(PORTC,PIN15,PUSH_PULL,LOW_SPEED);
	MGPIO_writePin(PORTC,PIN15,HIGH);

	MGPIO_SetMode(PORTB,PIN2,OUTPUT);
	MGPIO_SetOutputPinMode(PORTB,PIN2,PUSH_PULL,LOW_SPEED);

	//for speed control
	MGPIO_SetMode(PORTB,PIN13,OUTPUT);
	MGPIO_SetOutputPinMode(PORTB,PIN13,PUSH_PULL,LOW_SPEED);
	MGPIO_writePin(PORTB,PIN13,LOW);


	// Local variable for Mode
	u8 Local_u8Mode;


	// (in mode 1) Local variable for Car direction
	u8 Local_u8direction;

	//Initialise IR
	HIR_VoidInit();

	//Initialise DC_MOTOR
	DcMotor_VoidInit();

	//Initialise UART
	MUART_voidInit();



	while(1)
	{
		//receive mode from mobile application
		MUART_Recieve(&Local_u8Mode,UART_2);
		MGPIO_writePin(PORTB,PIN13,LOW);
		DcMotor_voidStop();


		// Turn On mode 1-->control RC Car by using Mobile Application
		while (Local_u8Mode=='X'||Local_u8Mode=='x')
		{
			MGPIO_writePin(PORTC,PIN15,HIGH);
			MUART_Recieve(&Local_u8direction,UART_2);

			// f --> forward direction
			if (Local_u8direction=='F'||Local_u8direction=='f')
			{
				DcMotor_voidForward();
			}
			// R --> Right direction
			else if (Local_u8direction=='R'||Local_u8direction=='r')
			{
				DcMotor_voidTurnRight();
			}
			// L--> Left  direction
			else if (Local_u8direction=='L'||Local_u8direction=='l')
			{
				DcMotor_voidTurnLeft();
			}

			// B--> Reverse direction
			else if (Local_u8direction=='B'||Local_u8direction=='b')
			{
				DcMotor_voidReverse();
			}
			else if(Local_u8direction=='V'||Local_u8direction=='v')
			{
				MGPIO_writePin(PORTB,PIN2,HIGH);
				MGPIO_writePin(PORTC,PIN15,LOW);
			}

			// S--> Stop Car
			else if (Local_u8direction=='S'||Local_u8direction=='s')
			{
				DcMotor_voidStop();
				MGPIO_writePin(PORTB,PIN2,LOW);
				MGPIO_writePin(PORTC,PIN15,HIGH);
			}


			/* Switching to second mode */
			else if (Local_u8direction == 'Y'||Local_u8direction == 'y')
			{
				Local_u8Mode = 'Y';
				DcMotor_voidStop();
				break;
			}

		}
		//Turn on mode 2--> Line Follower using 2 IR sensors
		while (Local_u8Mode=='Y'||Local_u8Mode=='y')
		{

			MGPIO_writePin(PORTB,PIN13,HIGH);

			if((HIR_LeftState() == IR_WHITE && HIR_RightState() == IR_WHITE && HIR_CenterState() == IR_BLACK )||(HIR_LeftState() == IR_WHITE &&  HIR_RightState() == IR_BLACK && HIR_CenterState() ==IR_BLACK )||(HIR_LeftState() == IR_BLACK &&  HIR_RightState() == IR_WHITE && HIR_CenterState() ==IR_BLACK ))
			{
				DcMotor_voidForward();
			}

			else if(HIR_LeftState() == IR_BLACK  && HIR_RightState() == IR_WHITE && HIR_CenterState() == IR_WHITE)
			{
				DcMotor_voidTurnLeft();
			}
			else if(HIR_LeftState() == IR_WHITE  && HIR_RightState() == IR_BLACK && HIR_CenterState() == IR_WHITE)
			{
				DcMotor_voidTurnRight();
			}

			else if(HIR_LeftState() == IR_BLACK &&HIR_RightState() == IR_BLACK && HIR_CenterState() == IR_BLACK)
			{
				DcMotor_voidStop();
			}




		}
	}


}
