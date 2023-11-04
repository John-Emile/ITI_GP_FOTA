#include "../include/LIB/BIT_MATH.h"
#include "../include/LIB/STD_TYPES.h"

#include "../include/MCAL/RCC/RCC_Interface.h"
#include "../include/MCAL/GPIO/GPIO_Interface.h"
#include "../include/MCAL/UART/UART_Interface.h"
#include "../include/HAL/IR/IR_Interface.h"
#include "../include/HAL/DC_MOTOR/DC_MOTOR_Interface.h"


int main()
{
	MRCC_voidInit();
	/* for APP*/
	MRCC_Enable_Peripheral(RCC_AHB1,RCC_AHB1_GPIOB);

	//For UART2//
	MRCC_Enable_Peripheral(RCC_AHB1,RCC_AHB1_GPIOA);
	MRCC_Enable_Peripheral(RCC_APB1,RCC_APB1_USART2);

	//PA2=(TX2)connect to RX in Bluetooth  ********** PA3=(RX2) connect to TX in Bluetooth

	//For UART2//
	MGPIO_SetMode(PORTA,PIN2,ALTERNATE);
	MGPIO_SetMode(PORTA,PIN3,ALTERNATE);
	MGPIO_SetAlternativeFuncPin(PORTA,PIN2,7);
	MGPIO_SetAlternativeFuncPin(PORTA,PIN3,7);



	// Local variable for Mode
	u8 Local_u8Mode;


	// (in mode 1) Local variable for Car direction
	u8 Local_u8direction;
	MUART_voidInit();

	while(1)
	{
		//receive mode from mobile application
		MUART_Recieve(&Local_u8Mode,UART_2);

		//Initialise DC_MOTOR
		DcMotor_VoidInit();

		// Turn On mode 1-->control RC Car by using Mobile Application
		while (Local_u8Mode=='X'||Local_u8Mode=='x')
		{
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
			// L--> Reverse direction
			else if (Local_u8direction=='L'||Local_u8direction=='l')
			{
				DcMotor_voidTurnLeft();
			}

			// G--> Reverse direction
			else if (Local_u8direction=='G'||Local_u8direction=='g')
			{
				DcMotor_voidReverse();
			}
			// S--> Stop Car
			else if (Local_u8direction=='S'||Local_u8direction=='s')
			{
				DcMotor_voidStop();
			}



			/* Switching to second mode */
			else if (Local_u8direction == 'Y'||Local_u8direction == 'y')
			{
				Local_u8Mode = 'Y';
				break;
			}

		}
		//Turn on mode 2--> Line Follower using 2 IR sensors
		while (Local_u8Mode=='Y'||Local_u8Mode=='y')
		{
			if(HIR_LeftState() == IR_WHITE && HIR_RightState() == IR_WHITE)
			{
				DcMotor_voidForward();
			}

		    else if(HIR_LeftState() == IR_BLACK  && HIR_RightState() == IR_WHITE)
			{
				DcMotor_voidTurnLeft();
			}
			else if(HIR_LeftState() == IR_WHITE  && HIR_RightState() == IR_BLACK)
			{
				DcMotor_voidTurnRight();
			}

			else if(HIR_LeftState() == IR_BLACK &&HIR_RightState() == IR_BLACK)
			{
				DcMotor_voidStop();
			}




		}
	}


}
