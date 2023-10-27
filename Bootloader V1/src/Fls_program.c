/*****************************************************************/
/* Author  : Dell                                                */
/* Layer   : MCAL                                                */
/* SWC     : Fls                                                 */
/* Version : 1.0                                                 */
/* Date    : 16 Oct 2023                                         */
/*****************************************************************/

#include <LIB/STD_Types.h>
#include <LIB/BIT_MATH.h>

#include <MCAL/Fls/Fls_config.h>
#include <MCAL/Fls/Fls_private.h>
#include <MCAL/Fls/Fls_interface.h>


/*Erase Specific Sector*/
tenuErrrorStatus Fls_earseSector(u8 _sectorNo)
{
	tenuErrrorStatus ReturnErrorState_local=EOK;

	/*Polling to make sure Flash Driver has no operation*/
	while(GET_BIT(Fls->SR,BSY)== 1);

	/*Check Lock bit if CR locked then use unlock sequence*/
	if(GET_BIT(Fls->CR,LOCK)==1)
	{
		/* use the following Sequence To unlock CR*/
		Fls->KEYR = KEY1_CR;
		Fls->KEYR = KEY2_CR;
		if(GET_BIT(Fls->CR,LOCK)==1)
		{
			/* indicate if unlock Sequence is unlocked successfully or not*/
			ReturnErrorState_local = ENOK;
		}
	}

	/*Enable End of Operation Interrupt To clear Busy Flag at end of operation*/
	SET_BIT(Fls->CR,EOPIE);

	/*Clear SNB to access new Sector*/
	Fls->CR  &= (~ (0xF<< 3));
	/*Select New sector*/
	Fls->CR  |= ( (_sectorNo << 3));

	/*enable Sector Erase Activate*/
	SET_BIT(Fls->CR,SER);

	/*START erasing*/
	SET_BIT(Fls->CR,STRT);

	/*Wait until Flash Driver end operation */
	while(GET_BIT(Fls->SR,BSY)== 1);

	/*Write 1 to EOP to Clear Flag*/
	SET_BIT(Fls->SR,EOP);

	/*Clear SER bit to Stop erasing*/
	CLR_BIT(Fls->CR,SER);

	return ReturnErrorState_local;
}

/*Erase Application area*/
tenuErrrorStatus Fls_earseAppArea(void)
{
	tenuErrrorStatus ReturnErrorState_local=EOK;
	u8 counter_local=0;
	{
		for(counter_local=1 ; counter_local<6 ; counter_local++ )
		{
			/*Erasing all Sector form 1 t0 5 and left Sector 0 for bootloader*/
			ReturnErrorState_local = Fls_earseSector(counter_local);

			/*Checking if error occurs break for loop*/
			if(ReturnErrorState_local == ENOK)
			{
				break;
			}
		}
	}
	return ReturnErrorState_local;
}

/*Write Data to Specific address*/

tenuErrrorStatus Fls_write(u32 _Address,u16* _data, u8 _dataLength)
{
	tenuErrrorStatus ReturnErrorState_local=EOK;
	u8 counter_Local=0;
	/*Clear Psize Bits to access New word size*/
	Fls->CR &= (~(0x3<<8));
	/*Set new Word Size*/
	Fls->CR |= (WORD_SIZE << 8);

	/*Polling to make sure Flash Driver has no operation*/
	while(GET_BIT(Fls->SR,BSY)== 1);

	/*Check Lock bit if CR locked then use unlock sequence*/
	if(GET_BIT(Fls->CR,LOCK)==1)
	{
		/* use the following Sequence To unlock CR*/
		Fls->KEYR = KEY1_CR;
		Fls->KEYR = KEY2_CR;
		if(GET_BIT(Fls->CR,LOCK)==1)
		{
			/* indicate if unlock Sequence is unlocked successfully or not*/
			ReturnErrorState_local = ENOK;
		}
	}


	for(counter_Local=0 ; counter_Local < _dataLength ; counter_Local++)
	{
		/*Enable programming*/
		SET_BIT(Fls->CR,PG);

		/*
		 * Access first 16 Bit of Address
		 * increase _Address by 2 to goto next 16 Bit
		 */
		*((volatile u16*)_Address) = _data[counter_Local];
		_Address += 2;

		/*Wait until Flash Driver end operation */
		while(GET_BIT(Fls->SR,BSY)== 1);

		/*Write 1 to EOP to Clear Flag*/
		SET_BIT(Fls->SR,EOP);

		/*Clear SER bit to Stop erasing*/
		CLR_BIT(Fls->CR,PG);
	}

	return ReturnErrorState_local;
}
