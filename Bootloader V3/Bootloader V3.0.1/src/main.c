#include "../include/LIB/Bit_Math.h"
#include <LIB/STD_Types.h>
#include <MCAL/RCC/MRCC_Interface.h>
#include <MCAL/GPIO/GPIO_interface.h>
#include <MCAL/MSysTick/MSTK_Interface.h>
#include <MCAL/USART/USART_interface.h>
#include <MCAL/FLASH/FLASH_Interface.h>
#include <App/Hex Parser/HEX_PARSE.h>


/* Global flag to indicate busy wait timeout expiry */
u8 g_timeoutFlag=0;

/* Global array of char to receive data from communication protocol */
u8 g_recieveBuffer[100];

/* Global index for records received from communication protocol */
u8 g_RecCounter=0;

/* Global flag to indicate write permission */
u8 g_writeReq=1;

/* Global flag to indicate if we should transfer data */
u8 g_transferFlag=0;


#define SCB_VTOR	*((volatile u32*)0xE000ED08)

/* Typedef pointer to function */
typedef void(*APP_CALL)(void);

/* Point to Null pointer as initial value */
APP_CALL ADD_TO_CALL= ((void*)0);


void APP_voidTest()
{
	/* Set Timeout flag to end while loop of Bootloader main */
	g_timeoutFlag=1;

	/* Turn off Led for indication of ending Bootloader Time*/
	GPIO_writePinVal(GPIO_PIN_NUM_A0,GPIO_LOW);

	/* Set the vector table offset to the first address in sector 1 */
	SCB_VTOR = 0x08004000;
	
	/*
	 * pointer to function = 0x8004004
	 * 4 offset for vector table (start up code first address)
	 */
	ADD_TO_CALL=*((APP_CALL*)(SCB_VTOR + 4));

	/*Run application by calling First address*/
	ADD_TO_CALL();
}

int main (void)
{
	/* Local variable to check on record status */
	tenuErrrorStatus L_enuRecStatus=ENOK;

	/* Local variable to check on data status */
	tenuErrrorStatus L_enuDataCheckState=ENOK;

	/*** Hardware initialization ***/
	MRCC_voidInit();

	/* Enable clock for GPIOB port */
	MRCC_Enable_Peripheral(RCC_AHB1,RCC_AHB1_GPIOB);

	/* Enable clock for GPIOA port */
	MRCC_Enable_Peripheral(RCC_AHB1,RCC_AHB1_GPIOA);

	/* Enable clock for USART1 peripheral */
	MRCC_Enable_Peripheral(RCC_APB2,RCC_APB2_USART1);

	/* Enable GPIO pins using linktime configuration */
	GPIO_init();

	/* Enable USART1 as configured */
	MUSART1_vidInit();

	/* Enable systick timer as configured */
	MSTK_voidInit();

	/* Check if we should transfer data */
	if(g_transferFlag == 0)
	{
		/* local variable buffer to hold down the memory data */
		u16 checkBuffer;

		/* Read sector 4 and save its content to the buffer */
		MFDI_ReadBuffer(FLASH_SECTOR_FIVE_ADDRESS,&checkBuffer,1);

		/* Check if the buffer is not erased */
		if(checkBuffer != 0xFFFF)
		{
			/* Erase sectors 1 up to 4 */
			MFDI_voidEraseAppArea(FLASH_SECTOR_ONE,FLASH_SECTOR_FOUR);
			
			/* Move data from sector 5 to sector 1 */
			MFDI_voidMoveData(FLASH_SECTOR_FIVE_ADDRESS,FLASH_SECTOR_ONE_ADDRESS,(56*1024));
			
			/* Set transfer flag to 1 */
			g_transferFlag=1;
		}
		else
		{
			/* Do nothing - Defensive programming */
 		}
	}

	/* Wait for approximatly 8 seconds to receive data */
	MSTK_asyncDelayms(8000,APP_voidTest);

	/* Turn on Led as an indication as the 8 seconds started */
	GPIO_writePinVal(GPIO_PIN_NUM_A0,GPIO_HIGH);


	/* While we're waiting the 8 seconds */
	while(g_timeoutFlag == 0)
	{

		/* Receive data from communication protocol in a recieving buffer */
		L_enuRecStatus=MUSART1_vidReceiveAsync(&g_recieveBuffer[g_RecCounter]);

		/* If data received */
		if(L_enuRecStatus==EOK)
		{
			/* Stop timer */
			//MSTK_voidInit();
			MSTK_StopInterval();
			
			
			/* Check end of file */
			if(g_recieveBuffer[g_RecCounter]=='\n')
			{

				/* Check if we should erase where we will recieve data */
				if(g_writeReq==1)
				{
					/* Erase data from sector 5 to receive new data */
					MFDI_voidEraseSector(FLASH_SECTOR_FIVE);

					/* Clear flag to avoid erasing again */
					g_writeReq=0;
				}

				/* Check on integrity of data received using check sum mechanism */
				L_enuDataCheckState =APARSER_checkSum(g_recieveBuffer);
				
				/* If data is okay */
				if(L_enuDataCheckState == EOK)
				{
					/* Starting parsing the record and writing it to flash memory */
					APARSER_voidParseRecord(g_recieveBuffer);
					
					/* Send ack */
					MUSART1_vidTransmitt("ok");

					/* Clear the flag */
					g_RecCounter=0;
				}
				else
				{
					/*
					 * this part can be modified and add to code
					 * Send NOK to Server to ask for sending data again
					 * uart send Nok
					 * MUSART1_vidTransmitt("NOK");
					 * g_RecCounter-=Record length;
					 */
					MFDI_voidEraseSector(FLASH_SECTOR_FIVE);

					/* Wait for approximatly 8 seconds before calling the application */
					MSTK_asyncDelayms(8000,APP_voidTest);

					/*
					 * this mean that data transfer was not correct so we erased Sector Five
					 * Poll until Run The previous application
					 */
					while(1)
					{
						GPIO_writePinVal(GPIO_PIN_NUM_A1,GPIO_HIGH);
					}
				}
			}
			else
			{
				g_RecCounter++;
			}

			/* Check on end of file */
			if(g_recieveBuffer[8]=='1')
			{
				/* Wait for approximatly 8 seconds before calling the application */
				MSTK_asyncDelayms(8000,APP_voidTest);
			}

		}

	}
	return 0;
}
