#include "../include/LIB/STD_Types.h"
#include "../include/LIB/BIT_MATH.h"

#include "../include/MCAL/RCC/MRCC_Interface.h"
#include "../include/MCAL/GPIO/GPIO_interface.h"
#include "../include/MCAL/MSysTick/MSTK_Interface.h"
#include "../include/MCAL/UART/MUART_interface.h"

int main()
{
	
	MRCC_voidInit();

	MRCC_Enable_Peripheral(RCC_AHB1,RCC_AHB1_GPIOA);
	MRCC_Enable_Peripheral(RCC_APB2,RCC_APB2_USART1);

	GPIO_init();
	MUART_voidInit();
	MSTK_voidInit();
	/* Define local variable to receive data sent by UART for car controlled mode */
	//u8 Local_U8_Data ;

	 /* Define local variable to receive car mode sent by UART  */
	 u8 Local_u8Mode;
	 /* Receive car mode from user */

	while(1){
		MUART_Recieve(&Local_u8Mode);

		if(Local_u8Mode=='X')
		{
			GPIO_writePinVal(GPIO_PIN_NUM_A1,GPIO_HIGH);
		}
		else if (Local_u8Mode=='Y')
		{
			GPIO_writePinVal(GPIO_PIN_NUM_A1,GPIO_LOW);
		}

		
		
		
		
	}


}
