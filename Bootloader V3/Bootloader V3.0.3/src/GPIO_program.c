/*****************************************************************/
/* Author  : El-Neshwy                                           */
/* Layer   : MCAL                                                */
/* SWC     : GPIO                                                */
/* Version : 1.0                                                 */
/* Date    : 09 Oct 2023                                         */
/*****************************************************************/

#include <LIB/STD_TYPES.h>
#include <LIB/BIT_MATH.h>
#include <MCAL/GPIO/GPIO_interface.h>
#include <MCAL/GPIO/GPIO_config.h>
#include <MCAL/GPIO/GPIO_private.h>



/************************************************************************************
 * Service Name: GPIO_init
 * Parameters (in): None
 * Return value: None
 * Description: initialize all GPIOs PINs according to the array of Configuration .
 ************************************************************************************/

void GPIO_init(void){
	u8 counter_local=0;
	/*using for loop to Configure all Pins according to Config_arr*/
	for(counter_local = 0 ; counter_local < 35 ; counter_local++)
	{	


		/*Configure Pin according to Config_arr*/
		switch(Config_arr[counter_local].PinxMode)
		{
		/*if PIN mode is INPUT*/
		case GPIO_INPUT:
			if(counter_local >=GPIO_PIN_NUM_A0 &&  counter_local <=GPIO_PIN_NUM_A15)
			{
				/*
				 * clear Mode Register to accept new Configuration
				 * Set PIN mode Input
				 * multiply counter_local by 2 bec each pin required 2 bits to configure four modes
				 */
				GPIOA->ModeR &=(~(TWO_BIT_MASK<<(counter_local*2)));
				GPIOA->ModeR |= ((Config_arr[counter_local].PinxMode & TWO_BIT_MASK)<<(counter_local*2));

				/*
				 * clear PUPD Register to accept new Configuration
				 * Set PIN PUPD register as Configure at Config_arr
				 * multiply counter_local by 2 bec each pin required 2 bits to configure four modes
				 */
				GPIOA->PUPDR &=(~(TWO_BIT_MASK<<(counter_local*2)));
				GPIOA->PUPDR |= ((Config_arr[counter_local].PinxPUPD & TWO_BIT_MASK)<<(counter_local*2));

			}
			else if(counter_local >=GPIO_PIN_NUM_B0 &&  counter_local <=GPIO_PIN_NUM_B15)
			{
				/*
				 * clear Mode Register to accept new Configuration
				 * Set PIN mode Input
				 * Get counter_local mod PORT_SIZE to get Pin index
				 * multiply counter_local by 2 bec each pin required 2 bits to configure four modes
				 */
				GPIOB->ModeR &=(~(TWO_BIT_MASK<<((counter_local%PORT_SIZE)*2)));
				GPIOB->ModeR |= ((Config_arr[counter_local].PinxMode & TWO_BIT_MASK)<<((counter_local%PORT_SIZE)*2));

				/*
				 * clear PUPD Register to accept new Configuration
				 * Set PIN PUPD register as Configure at Config_arr
				 * Get counter_local mod PORT_SIZE to get Pin index
				 * multiply counter_local by 2 bec each pin required 2 bits to configure four modes
				 */
				GPIOB->PUPDR &=(~(TWO_BIT_MASK<<((counter_local%PORT_SIZE)*2)));
				GPIOB->PUPDR |= ((Config_arr[counter_local].PinxPUPD & TWO_BIT_MASK)<<((counter_local%PORT_SIZE)*2));

			}
			else if(counter_local >= 32 &&  counter_local <=34)
			{
				/*
				 * clear Mode Register to accept new Configuration
				 * Set PIN mode Input
				 * Get counter_local mod PORT_SIZE to get Pin index
				 * multiply counter_local by 2 bec each pin required 2 bits to configure four modes
				 * ADD 13 to counter_local as to access pin (13 ,14 ,15) only
				 */
				GPIOC->ModeR &=(~(TWO_BIT_MASK<<((counter_local%PORT_SIZE)+13)*2));
				GPIOC->ModeR |= ((Config_arr[counter_local].PinxMode & TWO_BIT_MASK)<<((counter_local%PORT_SIZE)+13)*2);

				/*
				 * clear PUPD Register to accept new Configuration
				 * Set PIN PUPD register as Configure at Config_arr
				 * Get counter_local mod PORT_SIZE to get Pin index
				 * multiply counter_local by 2 bec each pin required 2 bits to configure four modes
				 * ADD 13 to counter_local as to access pin (13 ,14 ,15) only
				 */
				GPIOC->PUPDR &=(~(TWO_BIT_MASK<<((counter_local%PORT_SIZE)+13)*2));
				GPIOC->PUPDR |= ((Config_arr[counter_local].PinxPUPD & TWO_BIT_MASK)<<((counter_local%PORT_SIZE)+13)*2);
			}
			break;


			/*if PIN mode is OUTPUT*/
		case GPIO_OUTPUT:

			if(counter_local >= GPIO_PIN_NUM_A0 &&  counter_local <= GPIO_PIN_NUM_A15)
			{
				/*
				 * clear Mode Register to accept new Configuration
				 * Set PIN mode Output
				 * multiply counter_local by 2 bec each pin required 2 bits to configure four modes
				 */
				GPIOA->ModeR &=(~(TWO_BIT_MASK<<(counter_local*2)));
				GPIOA->ModeR |= ((Config_arr[counter_local].PinxMode & TWO_BIT_MASK)<<(counter_local*2));

				/*
				 * clear Speed Register to accept new Speed Configuration
				 * Set PIN Speed as in Config_arr
				 * multiply counter_local by 2 bec each pin required 2 bits to configure four modes
				 */
				GPIOA->SpeedR &=(~(TWO_BIT_MASK<<(counter_local*2)));
				GPIOA->SpeedR |= ((Config_arr[counter_local].PinxSpeed & TWO_BIT_MASK)<<(counter_local*2));

				/*
				 * clear Type Register to accept new Type Configuration
				 * Set PIN Type as in Config_arr
				 */
				GPIOA->TypeR &=(~(ONE_BIT_MASK<<(counter_local)));
				GPIOA->TypeR |= ((Config_arr[counter_local].PinxType & ONE_BIT_MASK)<<(counter_local));
			}


			else if(counter_local >=GPIO_PIN_NUM_B0 &&  counter_local <=GPIO_PIN_NUM_B15)
			{
				/*
				 * clear Mode Register to accept new Configuration
				 * Set PIN mode Output
				 * Get counter_local mod PORT_SIZE to get Pin index
				 * multiply counter_local by 2 bec each pin required 2 bits to configure four modes
				 */
				GPIOB->ModeR &=(~(TWO_BIT_MASK<<((counter_local%PORT_SIZE)*2)));
				GPIOB->ModeR |= ((Config_arr[counter_local].PinxMode & TWO_BIT_MASK)<<((counter_local%PORT_SIZE)*2));

				/*
				 * clear Speed Register to accept new Speed Configuration
				 * Set PIN Speed as in Config_arr
				 * multiply counter_local by 2 bec each pin required 2 bits to configure four modes
				 */
				GPIOB->SpeedR &=(~(TWO_BIT_MASK<<((counter_local%PORT_SIZE)*2)));
				GPIOB->SpeedR |= ((Config_arr[counter_local].PinxSpeed & TWO_BIT_MASK)<<((counter_local%PORT_SIZE)*2));

				/*
				 * clear Type Register to accept new Type Configuration
				 * Set PIN Type as in Config_arr
				 */
				GPIOB->TypeR &=(~(ONE_BIT_MASK<<(counter_local%PORT_SIZE)));
				GPIOB->TypeR |= ((Config_arr[counter_local].PinxType & ONE_BIT_MASK)<<(counter_local%PORT_SIZE));
			}
			else if(counter_local >= 32 &&  counter_local <= 34)
			{
				/*
				 * clear Mode Register to accept new Configuration
				 * Set PIN mode Output
				 * Get counter_local mod PORT_SIZE to get Pin index
				 * multiply counter_local by 2 bec each pin required 2 bits to configure four modes
				 */
				GPIOC->ModeR &=(~(TWO_BIT_MASK<<((counter_local%PORT_SIZE)+13)*2));
				GPIOC->ModeR |= ((Config_arr[counter_local].PinxMode & TWO_BIT_MASK)<<((counter_local%PORT_SIZE)+13)*2);

				/*
				 * clear Speed Register to accept new Speed Configuration
				 * Set PIN Speed as in Config_arr
				 * multiply counter_local by 2 bec each pin required 2 bits to configure four modes
				 * ADD 13 to counter_local as to access pin (13 ,14 ,15) only
				 */
				GPIOC->SpeedR &=(~(TWO_BIT_MASK<<((counter_local%PORT_SIZE)+13)*2));
				GPIOC->SpeedR |= ((Config_arr[counter_local].PinxSpeed & TWO_BIT_MASK)<<((counter_local%PORT_SIZE)+13)*2);

				/*
				 * clear Type Register to accept new Type Configuration
				 * Set PIN Type as in Config_arr
				 * ADD 13 to counter_local as to access pin (13 ,14 ,15) only
				 */
				GPIOC->TypeR &=(~(ONE_BIT_MASK<<((counter_local%PORT_SIZE)+13)));
				GPIOC->TypeR |= ((Config_arr[counter_local].PinxType & ONE_BIT_MASK)<<((counter_local%PORT_SIZE)+13));
			}
			break;



			/*if PIN mode is Alternate Function*/
		case GPIO_ALTERNATE_FUNCTION:
			if(counter_local >=GPIO_PIN_NUM_A0 &&  counter_local <=GPIO_PIN_NUM_A7)
			{
				/*
				 * clear Mode Register to accept new Configuration
				 * Set PIN mode Input
				 * multiply counter_local by 2 bec each pin required 2 bits to configure four modes
				 */
				GPIOA->ModeR &=(~(TWO_BIT_MASK<<(counter_local*2)));
				GPIOA->ModeR |= ((Config_arr[counter_local].PinxMode & TWO_BIT_MASK)<<(counter_local*2));

				/*
				 * clear AFRL Register to accept new AF Configuration
				 * Set PIN AF as in Config_arr
				 * multiply counter_local by 4 bec each pin required 4 bits to configure PORT_SIZE modes
				 */
				GPIOA->AFRL &=~(Alternative_Mask<<(counter_local*4));
				GPIOA->AFRL |=(Config_arr[counter_local].PinxAF<<(counter_local*4));
			}

			else if(counter_local >=GPIO_PIN_NUM_A8 &&  counter_local <=GPIO_PIN_NUM_A15)
			{
				/*
				 * clear Mode Register to accept new Configuration
				 * Set PIN mode Input
				 * multiply counter_local by 2 bec each pin required 2 bits to configure four modes
				 */
				GPIOA->ModeR &=(~(TWO_BIT_MASK<<(counter_local*2)));
				GPIOA->ModeR |= ((Config_arr[counter_local].PinxMode & TWO_BIT_MASK)<<(counter_local*2));

				/*
				 * clear AFRL Register to accept new AF Configuration
				 * Set PIN AF as in Config_arr
				 * multiply counter_local by 4 bec each pin required 4 bits to configure PORT_SIZE modes
				 */
				GPIOA->AFRH &=~(Alternative_Mask<<(counter_local*4));
				GPIOA->AFRH |=(Config_arr[counter_local].PinxAF<<(counter_local*4));
			}



			else if(counter_local >=GPIO_PIN_NUM_B0 &&  counter_local <=GPIO_PIN_NUM_B7)
			{
				/*
				 * clear Mode Register to accept new Configuration
				 * Set PIN mode Input
				 * Get counter_local mod PORT_SIZE to get Pin index
				 * multiply counter_local by 2 bec each pin required 2 bits to configure four modes
				 */
				GPIOB->ModeR &=(~(TWO_BIT_MASK<<((counter_local%PORT_SIZE)*2)));
				GPIOB->ModeR |= ((Config_arr[counter_local].PinxMode & TWO_BIT_MASK)<<((counter_local%PORT_SIZE)*2));

				/*
				 * clear AFRL Register to accept new AF Configuration
				 * Set PIN AF as in Config_arr
				 * multiply counter_local by 4 bec each pin required 4 bits to configure PORT_SIZE modes
				 */
				GPIOB->AFRL &=~(Alternative_Mask<<((counter_local%PORT_SIZE)*4));
				GPIOB->AFRL |=(Config_arr[counter_local].PinxAF<<((counter_local%PORT_SIZE)*4));
			}

			else if(counter_local >=GPIO_PIN_NUM_B8 &&  counter_local <=GPIO_PIN_NUM_B15)
			{
				/*
				 * clear Mode Register to accept new Configuration
				 * Set PIN mode Input
				 * Get counter_local mod PORT_SIZE to get Pin index
				 * multiply counter_local by 2 bec each pin required 2 bits to configure four modes
				 */
				GPIOB->ModeR &=(~(TWO_BIT_MASK<<((counter_local%PORT_SIZE)*2)));
				GPIOB->ModeR |= ((Config_arr[counter_local].PinxMode & TWO_BIT_MASK)<<((counter_local%PORT_SIZE)*2));

				/*
				 * clear AFRL Register to accept new AF Configuration
				 * Set PIN AF as in Config_arr
				 * multiply counter_local by 4 bec each pin required 4 bits to configure PORT_SIZE modes
				 */
				GPIOB->AFRH &=~(Alternative_Mask<<((counter_local%PORT_SIZE)*4));
				GPIOB->AFRH |=(Config_arr[counter_local].PinxAF<<((counter_local%PORT_SIZE)*4));
			}

			else if(counter_local >=GPIO_PIN_NUM_C13 &&  counter_local <=GPIO_PIN_NUM_C15)
			{
				/*
				 * clear Mode Register to accept new Configuration
				 * Set PIN mode Input
				 * Get counter_local mod PORT_SIZE to get Pin index
				 * multiply counter_local by 2 bec each pin required 2 bits to configure four modes
				 * ADD 13 to counter_local as to access pin (13 ,14 ,15) only
				 */
				GPIOC->ModeR &=(~(TWO_BIT_MASK<<((counter_local%PORT_SIZE)+13)*2));
				GPIOC->ModeR |= ((Config_arr[counter_local].PinxMode & TWO_BIT_MASK)<<((counter_local%PORT_SIZE)+13)*2);

				/*
				 * clear AFRL Register to accept new AF Configuration
				 * Set PIN AF as in Config_arr
				 * multiply counter_local by 4 bec each pin required 4 bits to configure PORT_SIZE modes
				 */
				GPIOC->AFRH &=~(Alternative_Mask<<(((counter_local%PORT_SIZE)+13)*4));
				GPIOC->AFRH |=(Config_arr[counter_local].PinxAF<<(((counter_local%PORT_SIZE)+13)*4));
			}
			break;





			/*if PIN mode is Analog*/
		case GPIO_ANALOG:
			if(counter_local >=GPIO_PIN_NUM_A0 &&  counter_local <=GPIO_PIN_NUM_A15)
			{
				/*
				 * clear Mode Register to accept new Configuration
				 * Set PIN mode Input
				 * multiply counter_local by 2 bec each pin required 2 bits to configure four modes
				 */
				GPIOA->ModeR &=(~(TWO_BIT_MASK<<(counter_local*2)));
				GPIOA->ModeR |= ((Config_arr[counter_local].PinxMode & TWO_BIT_MASK)<<(counter_local*2));
			}
			else if(counter_local >=GPIO_PIN_NUM_B0 &&  counter_local <=GPIO_PIN_NUM_B15)
			{
				/*
				 * clear Mode Register to accept new Configuration
				 * Set PIN mode Input
				 * Get counter_local mod PORT_SIZE to get Pin index
				 * multiply counter_local by 2 bec each pin required 2 bits to configure four modes
				 */
				GPIOB->ModeR &=(~(TWO_BIT_MASK<<((counter_local%PORT_SIZE)*2)));
				GPIOB->ModeR |= ((Config_arr[counter_local].PinxMode & TWO_BIT_MASK)<<((counter_local%PORT_SIZE)*2));
			}
			else if(counter_local >=GPIO_PIN_NUM_C13 &&  counter_local <=GPIO_PIN_NUM_C15)
			{
				/*
				 * clear Mode Register to accept new Configuration
				 * Set PIN mode Input
				 * Get counter_local mod PORT_SIZE to get Pin index
				 * multiply counter_local by 2 bec each pin required 2 bits to configure four modes
				 * ADD 13 to counter_local as to access pin (13 ,14 ,15) only
				 */
				GPIOC->ModeR &=(~(TWO_BIT_MASK<<((counter_local%PORT_SIZE)+13)*2));
				GPIOC->ModeR |= ((Config_arr[counter_local].PinxMode & TWO_BIT_MASK)<<((counter_local%PORT_SIZE)+13)*2);
			}
			break;

		default:	/*Do nothing*/
			break;
		}
	}
}




/************************************************************************************
 * Service Name: GPIO_writePinVal
 * Parameters (in): uint8 (Holds the PIN number to set its value)
 * 					uint8 (Holds the value which set to PIN)
 * Return value: None
 * Description:write a value to GPIO PIN.
 ************************************************************************************/

void GPIO_writePinVal(u8 _PINxNum, u8 _val){
	/*
	 * Do not miss with PA13,PA14,PA15,PB3,PB4 as they used at Debugging
	 * Check Pin value
	 * if its HIGH Set Bits in ODR Register
	 * if its LOW  CLR Bits in ODR Register
	 */
	if(_PINxNum == GPIO_PIN_NUM_A15 || _PINxNum == GPIO_PIN_NUM_A14 || _PINxNum == GPIO_PIN_NUM_A13 )
	{
		//Do Nothing
	}
	else if (_PINxNum == GPIO_PIN_NUM_B3 || _PINxNum == GPIO_PIN_NUM_B4 )
	{
		//Do Nothing
	}
	else
	{
		if(_val == GPIO_HIGH)
		{
			if(_PINxNum >=GPIO_PIN_NUM_A0 && _PINxNum <=GPIO_PIN_NUM_A15)
			{
				SET_BIT(GPIOA->ODR,_PINxNum);
			}
			else if(_PINxNum >=GPIO_PIN_NUM_B0 && _PINxNum <=GPIO_PIN_NUM_B15)
			{
				SET_BIT(GPIOB->ODR,_PINxNum%PORT_SIZE);
			}		
			else if(_PINxNum >=GPIO_PIN_NUM_C13 && _PINxNum <=GPIO_PIN_NUM_C15)
			{
				SET_BIT(GPIOC->ODR,(_PINxNum%PORT_SIZE));
			}
		}

		else if (_val == GPIO_LOW)
		{
			if(_PINxNum >=GPIO_PIN_NUM_A0 && _PINxNum <=GPIO_PIN_NUM_A15)
			{
				CLR_BIT(GPIOA->ODR,_PINxNum);
			}
			else if(_PINxNum >=GPIO_PIN_NUM_B0 && _PINxNum <=GPIO_PIN_NUM_B15)
			{
				CLR_BIT(GPIOB->ODR,_PINxNum%PORT_SIZE);
			}		
			else if(_PINxNum >=GPIO_PIN_NUM_C13 && _PINxNum <=GPIO_PIN_NUM_C15)
			{
				CLR_BIT(GPIOC->ODR,(_PINxNum%PORT_SIZE));
			}
		}
		else
		{
			//Do nothing
		}
	}

}


/************************************************************************************
 * Service Name: GPIO_readPinVal
 * Parameters (in): uint8 (Holds the PIN number to get its value)
 * 					uint8* (Holds Address of variable which will contain the value)
 * Return value: None
 * Description: Get the value of PIN and store it in the Received Address.
 ************************************************************************************/

void GPIO_readPinVal(u8 _PINxNum, u8* _pval){
	/*
	 * Do not miss with PA13,PA14,PA15,PB3,PB4 as they used at Debugging
	 * Red IDR register to Get PIN value
	 */

	if( _PINxNum == GPIO_PIN_NUM_A13 ||_PINxNum == GPIO_PIN_NUM_A14  ||_PINxNum == GPIO_PIN_NUM_A15 )
	{
		//Do nothing
	}

	else if( _PINxNum == GPIO_PIN_NUM_B3 || _PINxNum == GPIO_PIN_NUM_B4 )
	{
		//Do nothing
	}

	else if(_PINxNum >= GPIO_PIN_NUM_A0 && _PINxNum <= GPIO_PIN_NUM_A15)
	{
		*_pval = GET_BIT(GPIOA->IDR,_PINxNum);
	}
	else if(_PINxNum >=GPIO_PIN_NUM_B0 && _PINxNum <=GPIO_PIN_NUM_B15)
	{
		*_pval = GET_BIT(GPIOB->IDR,(_PINxNum%PORT_SIZE));
	}		
	else if(_PINxNum >=GPIO_PIN_NUM_C13 && _PINxNum <=GPIO_PIN_NUM_C15)
	{
		*_pval = GET_BIT(GPIOC->IDR,(_PINxNum%PORT_SIZE));
	}
}


/************************************************************************************
 * Service Name: GPIO_writeGroupVal
 * Parameters (in): uint8 (Holds the number of PINS that will configure)
 * 					uint8* (Holds array of PINS that will be configure at a time)
 * 					uint8* (Holds array of Values that will be Set to the PINs)
 * Return value: None
 * Description: write a group of values to group of PINs.
 ************************************************************************************/


void GPIO_writeGroupVal(u8 _size ,u8* _PINxNum, u8* _pval){
	u8 counter_local=0;
	/*
	 * For loop with size of input Pin and Set their values using GPIO_wirtePinVal
	 */
	for(counter_local = 0 ; counter_local < _size ; counter_local ++)
	{
		GPIO_writePinVal(_PINxNum[counter_local],_pval[counter_local]);
	}
}

/************************************************************************************
 * Service Name: GPIO_setAtomicBit
 * Parameters (in): uint8 (Holds the PIN number to Set its value)
 * 					uint8 (Holds state of PIN the will be configure)
 * Return value: None
 * Description: Set value of PIN in one Cycle .
 ************************************************************************************/


void GPIO_setAtomicBit(u8 _PINxNum , u8 _state)
{
	switch(_state)
	{
	case GPIO_SET:
		if( _PINxNum == GPIO_PIN_NUM_A13 ||_PINxNum == GPIO_PIN_NUM_A14  ||_PINxNum == GPIO_PIN_NUM_A15 )
		{
			//Do nothing
		}

		else if( _PINxNum == GPIO_PIN_NUM_B3 || _PINxNum == GPIO_PIN_NUM_B4 )
		{
			//Do nothing
		}

		else if(_PINxNum >=GPIO_PIN_NUM_A0 && _PINxNum <=GPIO_PIN_NUM_A15)
		{
			SET_BIT(GPIOA->BSRR,_PINxNum);
		}
		else if(_PINxNum >=GPIO_PIN_NUM_B0 && _PINxNum <=GPIO_PIN_NUM_B15)
		{
			SET_BIT(GPIOB->BSRR,_PINxNum%PORT_SIZE);
		}
		else if(_PINxNum >=GPIO_PIN_NUM_C13 && _PINxNum <=GPIO_PIN_NUM_C15)
		{
			SET_BIT(GPIOC->BSRR,(_PINxNum%PORT_SIZE));
		}

		break;

	case GPIO_RESET:
		if( _PINxNum == GPIO_PIN_NUM_A13 ||_PINxNum == GPIO_PIN_NUM_A14  ||_PINxNum == GPIO_PIN_NUM_A15 )
		{
			//Do nothing
		}

		else if( _PINxNum == GPIO_PIN_NUM_B3 || _PINxNum == GPIO_PIN_NUM_B4 )
		{
			//Do nothing
		}

		else if(_PINxNum >=GPIO_PIN_NUM_A0 && _PINxNum <=GPIO_PIN_NUM_A15)
		{
			SET_BIT(GPIOA->BSRR,(_PINxNum+16));
		}
		else if(_PINxNum >=GPIO_PIN_NUM_B0 && _PINxNum <=GPIO_PIN_NUM_B15)
		{
			SET_BIT(GPIOB->BSRR,((_PINxNum%PORT_SIZE)+16));
		}
		else if(_PINxNum >=GPIO_PIN_NUM_C13 && _PINxNum <=GPIO_PIN_NUM_C15)
		{
			SET_BIT(GPIOC->BSRR,((_PINxNum%PORT_SIZE)+16));
		}
		break;

	default:		//Do nothing
		break;
	}

}
