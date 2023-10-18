#include "../include/LIB/Bit_Math.h"
#include "../include/LIB/STD_TYPES.h"
#include "RCC/RCC_Interface.h"
#include "GPIO/GPIO_Interface.h"
#include "STK/MSTK_Interface.h"
#include "USART/USART_Interface.h"
#include "../include/FLASH/FLASH_Interface.h"
#include"../include/HEX_Parser/HEX_PARSE.h"
u8 u8_TimeoutFlag=0;
u8 RecieveBuffer[100];
u8 u8RecCounter=0;
u8 u8WriteReq=1;

#define SCB_VTOR	*((volatile u32*)0xE000ED08)
typedef void(*APP_CALL)(void);

APP_CALL ADD_TO_CALL=0;

void APP_voidTest()
{
	u8_TimeoutFlag=1;
	//pointer to function =0x8004000

	//set the vector table offset to the first address in sector 1
	SCB_VTOR=0x8004000;
	//call for pointer to function
	ADD_TO_CALL=*(APP_CALL*)0x8004004;// 4 offset for vect table (startupcode first address)
	//call the app part
	ADD_TO_CALL();

}
int main (void)
{
	u8 L_u8RecStatus=0;

	MRCC_VoidInit();
	MRCC_VoidEnablePeripherals(AHB1_bus,MGPIO_PORTB);
	MRCC_VoidEnablePeripherals(APB2_bus,USART1EN);
	//MRCC_VoidEnablePeripherals(APB1_bus,0);//FDI


	MGPIO_voidSetPinMode(MGPIO_PORTB,MGPIO_PIN6,MGPIO_MODE_ALTFUN);//TX1
	MGPIO_voidSetAltFun(MGPIO_PORTB,MGPIO_PIN6,MGPIO_ALTFN7);
	MGPIO_voidSetPinMode(MGPIO_PORTB,MGPIO_PIN7,MGPIO_MODE_ALTFUN);//RX1
	MGPIO_voidSetAltFun(MGPIO_PORTB,MGPIO_PIN7,MGPIO_ALTFN7);

	USART_voidInit(BAUDRATE);
	USART_voidEnable();
	MSTK_voidInit();

	MSTK_SetIntervalSingle(16777215,APP_voidTest);//interval 15s

	while(u8_TimeoutFlag == 0)
	{

		L_u8RecStatus=USART_voidRecieveBuffer(&RecieveBuffer[u8RecCounter]);

		if(L_u8RecStatus==1)
		{
			//stop timer
			//MSTK_voidInit();
			MSTK_StopInterval();
			//check end of file
			if(RecieveBuffer[u8RecCounter]=='\n')
			{

				if(u8WriteReq==1)
				{
					MFDI_voidEraseAppArea();
					u8WriteReq=0;
				}
				APARSER_voidParseRecord(RecieveBuffer);
				//send ok
				//uart send ok
				USART_voidSendString("ok");
				u8RecCounter=0;
			}
			else
			{
				u8RecCounter++;
			}
			if(RecieveBuffer[8]=='1')
			{
				MSTK_SetIntervalSingle(16777215,APP_voidTest);
			}
		}

	}return 0;
}
