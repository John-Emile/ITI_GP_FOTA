#include "../include/LIB/Bit_Math.h"
#include "../include/LIB/STD_TYPES.h"
#include <MCAL/RCC/MRCC_Interface.h>
#include <MCAL/GPIO/GPIO_interface.h>
#include <MCAL/MSysTick/MSTK_Interface.h>
#include <MCAL/USART/USART_interface.h>
#include <MCAL/FLASH/FLASH_Interface.h>
#include <App/HEX_Parser/HEX_PARSE.h>
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
	u8_TimeoutFlag=1;
	//pointer to function =0x8004000
	GPIO_writePinVal(GPIO_PIN_NUM_A0,GPIO_LOW);
	//set the vector table offset to the first address in sector 1
	SCB_VTOR=0x08004000;
	//call for pointer to function
	ADD_TO_CALL=*((APP_CALL*)0x08004004);// 4 offset for vect table (startupcode first address)
	//call the app part
	ADD_TO_CALL();
}
int main (void)
{
	u8 L_u8RecStatus=ENOK;

	MRCC_voidInit();
	MRCC_Enable_Peripheral(RCC_AHB1,RCC_AHB1_GPIOB);
	MRCC_Enable_Peripheral(RCC_AHB1,RCC_AHB1_GPIOA);
	MRCC_Enable_Peripheral(RCC_APB2,RCC_APB2_USART1);

	GPIO_init();
	MUSART1_vidInit();
	MSTK_voidInit();

	if(TransferFlag == 0)
	{
		MFDI_voidEraseSector(1);
		APAESER_voidMoveData(0x08008000,0x08004000,(8*1024));
		TransferFlag=1;
	}


	MSTK_asyncDelayms(8000,APP_voidTest);//interval 15s
	GPIO_writePinVal(GPIO_PIN_NUM_A0,GPIO_HIGH);



	while(u8_TimeoutFlag == 0)
	{

		L_u8RecStatus=MUSART1_vidReceiveAsync(&RecieveBuffer[u8RecCounter]);

		if(L_u8RecStatus==EOK)
		{
			//stop timer
			//MSTK_voidInit();
			MSTK_StopInterval();
			//check end of file
			if(RecieveBuffer[u8RecCounter]=='\n')
			{

				if(u8WriteReq==1)
				{
					MFDI_voidEraseSector(2);
					u8WriteReq=0;
				}
				APARSER_voidParseRecord(RecieveBuffer);
				//send ok
				//uart send ok
				MUSART1_vidTransmitt("ok");
				u8RecCounter=0;
			}
			else
			{
				u8RecCounter++;
			}

			if(RecieveBuffer[8]=='1')
			{
				MSTK_asyncDelayms(8000,APP_voidTest);//interval 15s
			}

		}

	}return 0;
}
