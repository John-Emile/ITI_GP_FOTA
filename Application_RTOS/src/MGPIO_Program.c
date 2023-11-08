#include"BIT_Math.h"
#include"STD_Types.h"
#include"MGPIO_Private.h"
#include"MGPIO_interface.h"


void MGPIO_SetMode(uint8 u8PortCPY,uint8 u8pinCPY,uint8 u8ModeCPY)
{
	if(u8PortCPY==PORTA && (u8pinCPY ==13 || u8pinCPY ==14 || u8pinCPY==15))
	{
		/*Do nothing ,pins for debugging*/
	}
	else if(u8PortCPY==PORTB && (u8pinCPY==4 || u8pinCPY ==3))
	{
		/*Do nothing ,pins for debugging*/
	}
	else
	{
		/*switch on the port to choose which port*/
		switch(u8PortCPY)
		{
		case PORTA:
			/*register is 32 bits,  pins from 0 to 15 and each pin has two values
			 make the two bits zero and then insert the value by OR operation
			 if pin 2 so start from bit 4 and if pin 3 start from bit 6, so number of bit is
			 equal to number of (pin*2) */
			GPIOA->GPIOx_MODER &= ~(MASK <<(u8pinCPY*2));
			GPIOA->GPIOx_MODER |=  (u8ModeCPY <<(u8pinCPY*2));
			break;

		case PORTB:
			/*register is 32 bits,  pins from 0 to 15 and each pin has two values
			make the two bits zero and then insert the value by OR operation
			if pin 2 so start from bit 4 and if pin 3 start from bit 6, so number of bit is
			equal to number of (pin*2) */
			GPIOB->GPIOx_MODER &= ~(MASK <<(u8pinCPY*2));
			GPIOB->GPIOx_MODER |=  (u8ModeCPY <<(u8pinCPY*2));
			break;

		case PORTC:
			/*register is 32 bits,  pins from 0 to 15 and each pin has two values
			make the two bits zero and then insert the value by OR operation
			if pin 2 so start from bit 4 and if pin 3 start from bit 6, so number of bit is
			equal to number of (pin*2) */
			GPIOC->GPIOx_MODER &= ~(MASK <<(u8pinCPY*2));
			GPIOC->GPIOx_MODER |=  (u8ModeCPY <<(u8pinCPY*2));
			break;
		default:
			break;

		}
	}

}
void MGPIO_SetOutputPinMode(uint8 u8PortCPY, uint8 u8pinCPY, uint8 u8OutTypeCPY,uint8 u8SpeedTypeCPY)
{
	/*switch on the port to choose which port*/
	switch(u8PortCPY)
	{
	case PORTA:
		/*register is 32 bits , only bits from 0 to 15 is used and each pin has one value
		 make the bits zero first and then insert the value whether 1 or 0*/

		GPIOA->GPIOx_OTYPER &= ~(1<<u8pinCPY); // to make it zero//
		GPIOA->GPIOx_OTYPER |= (u8OutTypeCPY<<u8pinCPY);

		/*register is 32 bits,  pins from 0 to 15 and each pin has two values
		make the two bits zero and then insert the value by OR operation
		if pin 2 so start from bit 4 and if pin 3 start from bit 6, so number of bit is
		equal to number of (pin*2) */

		GPIOA->GPIOx_OSPEEDR &= ~(MASK <<(u8pinCPY*2));
		GPIOA->GPIOx_OSPEEDR |=(u8SpeedTypeCPY<<(u8pinCPY*2));
		break;

	case PORTB:
		/*register is 32 bits , only bits from 0 to 15 is used and each pin has one value
		make the bits zero first and then insert the value whether 1 or 0*/

		GPIOB->GPIOx_OTYPER &= ~(1<<u8pinCPY); // to make it zero//
		GPIOB->GPIOx_OTYPER |= (u8OutTypeCPY<<u8pinCPY);

		/*register is 32 bits,  pins from 0 to 15 and each pin has two values
		make the two bits zero and then insert the value by OR operation
		if pin 2 so start from bit 4 and if pin 3 start from bit 6, so number of bit is
		equal to number of (pin*2) */

		GPIOB->GPIOx_OSPEEDR &= ~(MASK <<(u8pinCPY*2));
		GPIOB->GPIOx_OSPEEDR |=(u8SpeedTypeCPY<<(u8pinCPY*2));
		break;

	case PORTC:
		/*register is 32 bits , only bits from 0 to 15 is used and each pin has one value
		make the bits zero first and then insert the value whether 1 or 0*/
		GPIOC->GPIOx_OTYPER &= ~(1<<u8pinCPY); // to make it zero//
		GPIOC->GPIOx_OTYPER |= (u8OutTypeCPY<<u8pinCPY);

		/*register is 32 bits,  pins from 0 to 15 and each pin has two values
		make the two bits zero and then insert the value by OR operation
		if pin 2 so start from bit 4 and if pin 3 start from bit 6, so number of bit is
		equal to number of (pin*2) */

		GPIOC->GPIOx_OSPEEDR &= ~(MASK <<(u8pinCPY*2));
		GPIOC->GPIOx_OSPEEDR |=(u8SpeedTypeCPY<<(u8pinCPY*2));
		break;
	}


}
void MGPIO_SetInputPinType(uint8 u8PortCPY, uint8 u8pinCPY,uint8 u8InputModeCPY)
{
	switch(u8PortCPY)
	{
	case PORTA:
		/*register is 32 bits,  pins from 0 to 15 and each pin has two values
		make the two bits zero and then insert the value by OR operation
		if pin 2 so start from bit 4 and if pin 3 start from bit 6, so number of bit is
		equal to number of (pin*2) */
		GPIOA->GPIOx_PUPDR &= ~(MASK <<(u8pinCPY*2));
		GPIOA->GPIOx_PUPDR |=  (u8InputModeCPY <<(u8pinCPY*2));
		break;

	case PORTB:
		/*register is 32 bits,  pins from 0 to 15 and each pin has two values
		make the two bits zero and then insert the value by OR operation
		if pin 2 so start from bit 4 and if pin 3 start from bit 6, so number of bit is
		equal to number of (pin*2) */
		GPIOB->GPIOx_PUPDR &= ~(MASK <<(u8pinCPY*2));
		GPIOB->GPIOx_PUPDR |=  (u8InputModeCPY <<(u8pinCPY*2));
		break;

	case PORTC:
		/*register is 32 bits,  pins from 0 to 15 and each pin has two values
		make the two bits zero and then insert the value by OR operation
		if pin 2 so start from bit 4 and if pin 3 start from bit 6, so number of bit is
		equal to number of (pin*2) */
		GPIOC->GPIOx_PUPDR &= ~(MASK <<(u8pinCPY*2));
		GPIOC->GPIOx_PUPDR |=  (u8InputModeCPY <<(u8pinCPY*2));
		break;
	default:
		break;
	}

}
void MGPIO_readPin(uint8 u8PortCPY,uint8 u8pinCPY,uint8 * PinValCPY)
{
	switch(u8PortCPY)
	{
	case PORTA:
		/*get the value of the required pin and assign it to the variable passed*/
		*PinValCPY=GET_BIT(GPIOA->GPIOx_IDR,u8pinCPY);
		break;
	case PORTB:
		/*get the value of the required pin and assign it to the variable passed*/
		*PinValCPY=GET_BIT(GPIOB->GPIOx_IDR,u8pinCPY);
		break;
	case PORTC:
		/*get the value of the required pin and assign it to the variable passed*/
		*PinValCPY=GET_BIT(GPIOC->GPIOx_IDR,u8pinCPY);
		break;
	default:
		break;
	}



}
void MGPIO_writePin(uint8 u8PortCPY,uint8 u8pinCPY,uint8 u8PinValCPY)
{

	switch(u8PortCPY)
	{
	case PORTA:
		/*Check if the value is low or high and then write one or zero to the required pin */
		if(u8PinValCPY==HIGH)
			SET_BIT(GPIOA->GPIOx_ODR,u8pinCPY);
		else if(u8PinValCPY==LOW)
			CLR_BIT(GPIOA->GPIOx_ODR,u8pinCPY);
		break;
	case PORTB:
		/*Check if the value is low or high and then write one or zero to the required pin */
		if(u8PinValCPY==HIGH)
			SET_BIT(GPIOB->GPIOx_ODR,u8pinCPY);
		else if(u8PinValCPY==LOW)
			CLR_BIT(GPIOB->GPIOx_ODR,u8pinCPY);
		break;
	case PORTC:
		/*Check if the value is low or high and then write one or zero to the required pin */
		if(u8PinValCPY==HIGH)
			SET_BIT(GPIOC->GPIOx_ODR,u8pinCPY);
		else if(u8PinValCPY==LOW)
			CLR_BIT(GPIOC->GPIOx_ODR,u8pinCPY);
		break;
	default:
		break;

	}

}
void MGPIO_SetResetValue(uint8 u8PortCPY,uint8 u8pinCPY, uint8 u8SetOrResetCPY)
{
	/* the BSRR register is configured that bits from 0 to 15 is for the set, to set the pin write
 one from bit 0 to 15, and bits from 16 to 31 is for the reset, to reset the pin write one
 so first switch on whether it is set or reset to choose of it is bits from 0 to 15
 or from 16 to 32*/
	if(u8SetOrResetCPY==OUPUT_SET)
	{
		/*if it is set, switch on port and write 1 in the required pin */
		switch(u8PortCPY)
		{
		case PORTA:
			GPIOA->GPIOx_BSRR &= ~(1 <<(u8pinCPY));
			GPIOA->GPIOx_BSRR |=  (1 <<(u8pinCPY));
			break;

		case PORTB:
			GPIOB->GPIOx_BSRR &= ~(1 <<(u8pinCPY));
			GPIOB->GPIOx_BSRR |=  (1 <<(u8pinCPY));
			break;

		case PORTC:
			GPIOC->GPIOx_BSRR &= ~(1 <<(u8pinCPY));
			GPIOC->GPIOx_BSRR |=  (1 <<(u8pinCPY));
			break;
		default:
			break;
		}
	}
	else if(u8SetOrResetCPY==OUTPUT_RESET)
	{
		/*if it is reset, switch on the port and its bits from 16 to 32, so pin 0
		  corresponds to bit 16 and pin 1 corresponds to bit 17 so make (pin+16) */
		u8pinCPY+=16;
		switch(u8PortCPY)
		{
		case PORTA:
			GPIOA->GPIOx_BSRR &= ~(1 <<(u8pinCPY));
			GPIOA->GPIOx_BSRR |=  (1 <<(u8pinCPY));
			break;

		case PORTB:
			GPIOB->GPIOx_BSRR &= ~(1 <<(u8pinCPY));
			GPIOB->GPIOx_BSRR |=  (1 <<(u8pinCPY));
			break;

		case PORTC:
			GPIOC->GPIOx_BSRR &= ~(1 <<(u8pinCPY));
			GPIOC->GPIOx_BSRR |=  (1 <<(u8pinCPY));
			break;
		default:
			break;
		}
	}


}
void MGPIO_SetAlternativeFuncPin(uint8 Copy_u8Port,uint8 Copy_u8Pin,uint8  Copy_u8Data)
{
	if(Copy_u8Port==PORTA && (Copy_u8Pin==PIN13 || Copy_u8Pin==14 || Copy_u8Pin==15))
		{
			/* Do Nothing */
		}
		else if(Copy_u8Port==PORTB && (Copy_u8Pin==PIN3 || Copy_u8Pin==4 ))
		{
			/* Do Nothing */
		}
		else
		{
			switch (Copy_u8Port) {
			case PORTA:
				if(Copy_u8Pin<=7)
				{
					GPIOA->AFRL &=~(Alternative_Mask<<(Copy_u8Pin*4));
					GPIOA->AFRL |=(Copy_u8Data<<(Copy_u8Pin*4));
				}
				else
				{
					GPIOA->AFRH &=~(Alternative_Mask<<((Copy_u8Pin-8)*4));
					GPIOA->AFRH |=(Copy_u8Data<<((Copy_u8Pin-8)*4));
				}
				break;
			case PORTB:
				if(Copy_u8Pin<=7)
				{
					GPIOB->AFRL &=~(Alternative_Mask<<(Copy_u8Pin*4));
					GPIOB->AFRL |=(Copy_u8Data<<(Copy_u8Pin*4));
				}
				else
				{
					GPIOB->AFRH &=~(Alternative_Mask<<((Copy_u8Pin-8)*4));
					GPIOB->AFRH |=(Copy_u8Data<<((Copy_u8Pin-8)*4));
				}
				break;
			case PORTC:
				if(Copy_u8Pin<=7)
				{
					GPIOC->AFRL &=~(Alternative_Mask<<(Copy_u8Pin*4));
					GPIOC->AFRL |=(Copy_u8Data<<(Copy_u8Pin*4));
				}
				else
				{
					GPIOC->AFRH &=~(Alternative_Mask<<((Copy_u8Pin-8)*4));
					GPIOC->AFRH |=(Copy_u8Data<<((Copy_u8Pin-8)*4));
				}
				break;
			default:
				break;
			}
		}
}



