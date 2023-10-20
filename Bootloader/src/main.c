#include <MCAL/Fls/Fls_interface.h>
#include <MCAL/GPIO/GPIO_interface.h>
#include <MCAL/MSysTick/MSTK_Interface.h>
#include <MCAL/NVIC/MNVIC_interface.h>
#include <MCAL/RCC/MRCC_Interface.h>
#include <MCAL/USART/USART_interface.h>
#include <App/HEXPARSER/HexParser.h>
#include <MCAL/MEXTI/MEXTI_interface.h>
#include <MCAL/SCB/SCB_interface.h>

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
	GPIO_writePinVal(GPIO_PIN_NUM_A1,GPIO_HIGH);
	//set the vector table offset to the first address in sector 1
	MCAL_SCB_VTOR_SetValue(0x8004000);
	//call for pointer to function
	ADD_TO_CALL=*(APP_CALL*)0x8004004;// 4 offset for vect table (startupcode first address)
	//call the app part
	ADD_TO_CALL();

}
int main (void)
{
	tenuErrrorStatus L_u8RecStatus=0;


	MRCC_voidInit();
	MRCC_Enable_Peripheral(RCC_AHB1,RCC_AHB1_GPIOB);
	MRCC_Enable_Peripheral(RCC_AHB1,RCC_AHB1_GPIOA);
	MRCC_Enable_Peripheral(RCC_APB2,RCC_APB2_USART1);
	//MRCC_VoidEnablePeripherals(APB1_bus,0);//FDI

	GPIO_init();
	MUSART1_vidInit();
	MSTK_voidInit();

	MSTK_asyncDelayms(8000,APP_voidTest);//interval 15s

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
					HexParser_vEraseAppArea();
					u8WriteReq=0;
				}
				HexParser_vParseData(RecieveBuffer);
				//send ok
				//uart send ok
				MUSART1_vidTransmitt("ok");
				u8RecCounter=0;
			}
			else
			{
				u8RecCounter++;
			}

			MSTK_asyncDelayms(8000,APP_voidTest);//interval 15s

		}

	}
	return 0;
}
