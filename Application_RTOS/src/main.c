#include"FreeRTOS.h"
#include"FreeRTOSConfig.h"
#include"task.h"
#include"queue.h"
#include"semphr.h"
#include"STD_Types.h"
#include"BIT_Math.h"
#include"MGPIO_Private.h"
#include"MGPIO_interface.h"
#include"MRCC_Private.h"
#include"MRCC_Interface.h"
#include"MAURT_private.h"
#include"MUART_interface.h"
#include"IR_Config.h"
#include"IR_Interface.h"
#include"DC_MOTOR_Interface.h"


/******************************************To define Task Handle*******************************************/
TaskHandle_t VtaskManualMode=NULL;
TaskHandle_t VtaskOptionMode=NULL;
TaskHandle_t VtaskIRMode=NULL;
SemaphoreHandle_t xsemaphore_1=NULL;
SemaphoreHandle_t xsemaphore_2=NULL;
/**********************************************Task Prototype**********************************************/
void TaskModeOption(void*x);
void ManualMode(void *parms);
void IRMode(void*y);

uint8 Local_u8Mode;
uint8 u8flag_1=0;
uint8 u8flag_2=0;
uint8 u8state=1;
uint8 u8Leftstatues=1;
uint8 u8Rightstatues=1;


int main(void)
{
	MRCC_voidInit();
	// RCC enable for GPIO
	MRCC_Enable_Peripheral(RCC_AHB1,RCC_AHB1_GPIOA);
	MRCC_Enable_Peripheral(RCC_AHB1,RCC_AHB1_GPIOB);
	//RCC enable for UART
	MRCC_Enable_Peripheral(RCC_APB2,RCC_APB2_USART1);
	MRCC_Enable_Peripheral(RCC_APB1,RCC_APB1_USART2);

    //To set alternate function for PIN2 AND PIN3 for UART2
	MGPIO_SetMode(PORTA,PIN2,ALTERNATE);
	MGPIO_SetMode(PORTA,PIN3,ALTERNATE);

	MGPIO_SetAlternativeFuncPin(PORTA,PIN2,7);
	MGPIO_SetAlternativeFuncPin(PORTA,PIN3,7);

	HIR_VoidInit();
	DcMotor_VoidInit();
	MUART_voidInit();
	/**********************************************Task Creation********************************************/
	xTaskCreate(TaskModeOption, "choose mode1 or mode2", 128 , NULL, 1, VtaskOptionMode);
	xTaskCreate(ManualMode, "mode 1_manual", 128 , NULL, 2, VtaskManualMode);
	xTaskCreate(IRMode, "mode 2_IR", 128 , NULL, 2, VtaskIRMode);
	/**********************************************Semaphore Creation****************************************/
	xsemaphore_1=xSemaphoreCreateBinary();
	xsemaphore_2=xSemaphoreCreateBinary();
	vTaskStartScheduler();

	while(1)
	{
		MGPIO_readPin(PORTA,PIN9,&u8Leftstatues);
		if( (u8Leftstatues ==0))
		{
			MGPIO_writePin(PORTA,PIN4,HIGH);
		}

	}
}

void IRMode(void*y)
{
	uint8 Local_u8direction=0;

	while(1)
	{
		xSemaphoreTake(xsemaphore_2,(TickType_t) portMAX_DELAY);

		MGPIO_readPin(PORTA,PIN9,&u8Leftstatues);
		MGPIO_readPin(PORTA,PIN8,&u8Rightstatues);

		//MGPIO_writePin(PORTA,PIN4,HIGH);
		if( (u8Leftstatues == IR_WHITE) && (u8Rightstatues == IR_WHITE) )
		{
			DcMotor_voidForward(); //Led PA4 on//
		}

		if( (u8Leftstatues == IR_BLACK)  && (u8Rightstatues == IR_WHITE) )
		{
			DcMotor_voidTurnLeft();
		}

		if( (u8Leftstatues == IR_WHITE)  && (u8Rightstatues == IR_BLACK) )
		{
			DcMotor_voidTurnRight();
		}

		if( (u8Leftstatues == IR_BLACK) && (u8Rightstatues == IR_BLACK) )
		{
			DcMotor_voidStop();
		}

		MUART_Recieve(&Local_u8direction,UART_2);

		if(Local_u8direction=='X'||Local_u8direction=='x')
		{
			DcMotor_voidStop();
			u8flag_2=1;
			u8flag_1=0;
			xSemaphoreGive(xsemaphore_1);
		}

		if(u8flag_2==0)
		{
			xSemaphoreGive(xsemaphore_2);
		}

		vTaskDelay(40);
	}
}

void ManualMode(void *parms)
{
	uint8 Local_u8direction=0;
	while(1)
	{
		xSemaphoreTake(xsemaphore_1,(TickType_t) portMAX_DELAY);

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

		else if (Local_u8direction == 'Y'||Local_u8direction == 'y')
		{
			DcMotor_voidStop();
			u8flag_1=1;// To not give semaphore_1 and block manual mode if IR mode is activated //
			u8flag_2=0;
			xSemaphoreGive(xsemaphore_2);
		}

		if(u8flag_1==0)
		{
			xSemaphoreGive(xsemaphore_1);
		}

		vTaskDelay(50);
	}
}

void TaskModeOption(void*x)
{

	while(1)
	{
		//receive mode from mobile application
		MUART_Recieve(&Local_u8Mode,UART_2);

		if(Local_u8Mode=='X'||Local_u8Mode=='x')
		{
			xSemaphoreGive(xsemaphore_1);
		}
		if(Local_u8Mode=='Y'||Local_u8Mode=='y')
		{
			xSemaphoreGive(xsemaphore_2);

		}

		vTaskDelay(100);
	}

}


