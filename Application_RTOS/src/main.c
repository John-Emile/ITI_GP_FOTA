/********************************************************************************************************
 * Description : RC car with two modes, manual mode and Line follower mode. implemented Based on RTOS
 * Date        : 11/9/2023
 * Name        : Aya Ahmed
 *
 */
/*******************************************Includes************************************************************/
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
TaskHandle_t VtaskIRMode_select=NULL;
TaskHandle_t VtaskIRMode_Left=NULL;
/******************************************To define semaphore Hanlde****************************************/
SemaphoreHandle_t xsemaphore_1=NULL;
SemaphoreHandle_t xsemaphore_2=NULL;
SemaphoreHandle_t xsemaphore_3=NULL;
/**********************************************Tasks Prototype**********************************************/
void TaskModeOption(void*x);
void ManualMode(void *parms);
void IRMode_Selection(void*y);
void IRMode_Left(void*z);
/*************************************Global variables can be accessed by all tasks***************************/
uint8 Local_u8Mode;
uint8 u8flag_1=0;
uint8 u8flag_2=0;
uint8 u8state=1;
uint8 u8IRLeft=0;
uint8 u8IRRight=0;

/**************************************************Main*****************************************************/

int main(void)
{
	/*For RCC init*/
	MRCC_voidInit();

	/*RCC enable for GPIO*/
	MRCC_Enable_Peripheral(RCC_AHB1,RCC_AHB1_GPIOA);
	MRCC_Enable_Peripheral(RCC_AHB1,RCC_AHB1_GPIOB);

	/*RCC enable for UART*/
	MRCC_Enable_Peripheral(RCC_APB2,RCC_APB2_USART1);
	MRCC_Enable_Peripheral(RCC_APB1,RCC_APB1_USART2);

    /*To set alternate function for PIN2 AND PIN3 for UART2*/
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
	xTaskCreate(IRMode_Selection, "Task to read input of IR", 128 , NULL, 3, VtaskIRMode_select);
	xTaskCreate(IRMode_Left, "IR left", 128 , NULL, 2, VtaskIRMode_Left);
	/**********************************************Semaphore Creation****************************************/
	xsemaphore_1=xSemaphoreCreateBinary();
	xsemaphore_2=xSemaphoreCreateBinary();
	xsemaphore_3=xSemaphoreCreateBinary();

	/*To call the scheduler to start*/
	vTaskStartScheduler();

	while(1)
	{

	}
}

/*Task which executes in Lined follower mode only, responsible for the motor to turn left*/
void IRMode_Left(void*z)
{
	while(1)
	{
		/*Take semaphore 2 when the mode is line follower mode*/
		xSemaphoreTake(xsemaphore_2,(TickType_t) portMAX_DELAY);
		/*Take semaphore 3 when IR left sensor detects a signal whil IR right signal doesn't detect*/
		xSemaphoreTake(xsemaphore_3,(TickType_t) portMAX_DELAY);
		/*function responsible to make PA4 and PA7 high */
		DcMotor_voidTurnLeft();

		u8IRLeft=0;
		u8IRRight=0;
		/*Give semaphore while the mode is Line follower mode and no switch to manual mode*/
		if(u8flag_2==0)
		{
			xSemaphoreGive(xsemaphore_2);
		}

		vTaskDelay(40);
	}


}

/*Task responsible to detect the value of both IR sensors and also takes action according to this value*/
void IRMode_Selection(void*y)
{
	while(1)
	{
		/*block Line follower mode unless there is a switch from manual mode to line follower
		 * when in manual mode, u8flag_1=0 so this condition will not execute which results in blocking
		 * line follower mode in case manual mode*/
		if(u8flag_1==1)
		{
			/*Read the value of IR left sensor*/
			MGPIO_readPin(PORTA,PIN9,&u8IRLeft);
			/*Read the value of IR right sensor*/
			MGPIO_readPin(PORTA,PIN8,&u8IRRight);
			/*If IR left sensor decets HIGH and IR right sensor detects LOW*/
			if(u8IRLeft==1 && u8IRRight==0 )
			{
				xSemaphoreGive(xsemaphore_3);    /*Give semaphore and activate IRMode_Left task*/
			}
			/*If IR left sensor decets LOW and IR right sensor detects LOW*/
			if(u8IRLeft==0 && u8IRRight==0)
			{
				DcMotor_voidForward();           /*Make PA4 and PA6 HIGH*/
			}
			/*If IR left sensor decets LOW and IR right sensor detects HIGH*/
			if(u8IRLeft==0 && u8IRRight==1)
			{
				DcMotor_voidTurnRight();         /*Make PA6 and PA5 HIGH*/
			}
			/*If IR left sensor decets HIGH and IR right sensor detects HIGH*/
			if(u8IRLeft==1 && u8IRRight==1 )
			{
				DcMotor_voidStop();              /*Make all pins LOW*/
			}
		}
		vTaskDelay(35);
	}
}

void ManualMode(void *parms)
{
	uint8 Local_u8direction=0;

	while(1)
	{
		/*Take semaphore 1 when its a manual mode*/
		xSemaphoreTake(xsemaphore_1,(TickType_t) portMAX_DELAY);
		DcMotor_voidStop();
		while(Local_u8Mode=='x' || Local_u8Mode=='X')
		{
			/*Make global variable u8flag_1=0 to block the line follower state*/
			u8flag_1=0;
			/*Receive the value of the direction when in manual mode*/
			MUART_Recieve(&Local_u8direction,UART_2);
			/*f --> forward direction*/
			if (Local_u8direction=='F'||Local_u8direction=='f')
			{
				DcMotor_voidForward();      /*Make PA4 and PA6 HIGH*/
			}
			/* R --> Right direction*/
			else if (Local_u8direction=='R'||Local_u8direction=='r')
			{
				DcMotor_voidTurnRight();    /*Make PA6 and PA5 HIGH*/
			}
			/* L--> Left  direction*/
			else if (Local_u8direction=='L'||Local_u8direction=='l')
			{
				DcMotor_voidTurnLeft();   /*Make PA4 and PA7 HIGH*/
			}

			/* G--> Reverse direction*/
			else if (Local_u8direction=='G'||Local_u8direction=='g')
			{
				DcMotor_voidReverse();    /*Make PA5 and PA7 HIGH*/
			}
			/* S--> Stop Car*/
			else if (Local_u8direction=='S'||Local_u8direction=='s')
			{
				DcMotor_voidStop();     /*Make all pins LOW*/
			}
			/*If the mode is switched to line follower mode*/
			else if (Local_u8direction == 'Y'||Local_u8direction == 'y')
			{
				DcMotor_voidStop();
				u8flag_1=1;/* To not give semaphore_1 and block manual mode if line follower mode is activated */
				u8flag_2=0;
				xSemaphoreGive(xsemaphore_2); /*Give semaphore 2 to activate line follower mode*/
				break;
			}
		}
		/*Give semaphore while mode is manual mode and there is no switch in modes*/
		if(u8flag_1==0)
		{
			xSemaphoreGive(xsemaphore_1);
		}

		vTaskDelay(50);
	}
}
/*Task which executes to take the value of the mode whether manual mode or line follower mode
 * and give the semaphore according to the mode*/
void TaskModeOption(void*x)
{
	while(1)
	{
		/*receive mode from mobile application via bluetooth through UART*/
		MUART_Recieve(&Local_u8Mode,UART_2);
		/*X indicates for manual mode */
		if(Local_u8Mode=='X'||Local_u8Mode=='x')
		{
			xSemaphoreGive(xsemaphore_1);

		}
		/*Y indicates for manual mode */
		if(Local_u8Mode=='Y'||Local_u8Mode=='y')
		{
			xSemaphoreGive(xsemaphore_2);

		}

		vTaskDelay(100);
	}

}


