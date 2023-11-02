#include "../include/LIB/Bit_Math.h"
#include <LIB/STD_Types.h>
#include <MCAL/RCC/MRCC_Interface.h>
#include <MCAL/GPIO/GPIO_interface.h>
#include <MCAL/MSysTick/MSTK_Interface.h>
#include <MCAL/USART/USART_interface.h>
#include <MCAL/FLASH/FLASH_Interface.h>
#include <App/Hex Parser/HEX_PARSE.h>
u8 u8_TimeoutFlag=0;
u8 RecieveBuffer[100];
u8 u8RecCounter=0;
u8 u8WriteReq=1;
u8 TransferFlag=0;
#define SCB_VTOR	*((volatile u32*)0xE000ED08)
typedef void(*APP_CALL)(void);

APP_CALL ADD_TO_CALL=0;

void APP_voidTest()
{
	/*Set Timeout flag to end while loop of Bootloader main */
	u8_TimeoutFlag=1;
	/* Turn off Led for indication of ending Bootloader Time*/
	GPIO_writePinVal(GPIO_PIN_NUM_A0,GPIO_LOW);
	/*set the vector table offset to the first address in sector 1*/
	SCB_VTOR=0x08004000;
	/*
	 * pointer to function =0x8004004
	 * 4 offset for vector table (start up code first address)
	 */
	ADD_TO_CALL=*((APP_CALL*)0x08004004);
	/*Run application by calling First address*/
	ADD_TO_CALL();
}

int main (void)
{
	tenuErrrorStatus L_enuRecStatus=ENOK;
	tenuErrrorStatus L_enuDataCheckState=ENOK;

	MRCC_voidInit();
	MRCC_Enable_Peripheral(RCC_AHB1,RCC_AHB1_GPIOB);
	MRCC_Enable_Peripheral(RCC_AHB1,RCC_AHB1_GPIOA);
	MRCC_Enable_Peripheral(RCC_APB2,RCC_APB2_USART1);

	GPIO_init();
	MUSART1_vidInit();
	MSTK_voidInit();

	if(TransferFlag == 0)
	{
		u16 checkBuffer;
		MFDI_ReadBuffer(FLASH_SECTOR_FIVE_ADDRESS,&checkBuffer,1);
		if(checkBuffer != 0xFFFF)
		{
			MFDI_voidEraseAppArea(FLASH_SECTOR_ONE,FLASH_SECTOR_FOUR);
			MFDI_voidMoveData(FLASH_SECTOR_FIVE_ADDRESS,FLASH_SECTOR_ONE_ADDRESS,(56*1024));
			TransferFlag=1;
		}
		else
		{
			//Do nothing
		}
	}


	MSTK_asyncDelayms(8000,APP_voidTest);//interval 8s
	GPIO_writePinVal(GPIO_PIN_NUM_A0,GPIO_HIGH);



	while(u8_TimeoutFlag == 0)
	{

		L_enuRecStatus=MUSART1_vidReceiveAsync(&RecieveBuffer[u8RecCounter]);

		if(L_enuRecStatus==EOK)
		{
			//stop timer
			//MSTK_voidInit();
			MSTK_StopInterval();
			//check end of file
			if(RecieveBuffer[u8RecCounter]=='\n')
			{

				if(u8WriteReq==1)
				{
					MFDI_voidEraseSector(FLASH_SECTOR_FIVE);
					u8WriteReq=0;
				}

				L_enuDataCheckState =APARSER_checkSum(RecieveBuffer);
				if(L_enuDataCheckState == EOK)
				{
					APARSER_voidParseRecord(RecieveBuffer);
					//send ok
					//uart send ok
					MUSART1_vidTransmitt("ok");
					u8RecCounter=0;
				}
				else
				{
					/*
					 * this part can be modified and add to code
					 * Send NOK to Server to ask for sending data again
					 * uart send Nok
					 * MUSART1_vidTransmitt("NOK");
					 * u8RecCounter-=Record length;
					 */
					MFDI_voidEraseSector(FLASH_SECTOR_FIVE);
					MSTK_asyncDelayms(8000,APP_voidTest);//interval 8s
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
				u8RecCounter++;
			}

			if(RecieveBuffer[8]=='1')
			{
				MSTK_asyncDelayms(8000,APP_voidTest);//interval 8s
			}

		}

	}return 0;
}
