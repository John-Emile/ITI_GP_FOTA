/*****************************************************************/
/* Author  : El-Neshwy                                           */
/* Layer   : MCAL                                                */
/* SWC     : GPIO                                                */
/* Version : 1.0                                                 */
/* Date    : 09 Oct 2023                                         */
/*****************************************************************/
#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_


#define GPIO_PIN_NUM			35
/*******************GPIOA PINS***************/
#define GPIO_PIN_NUM_A0						0
#define GPIO_PIN_NUM_A1						1
#define GPIO_PIN_NUM_A2						2
#define GPIO_PIN_NUM_A3						3
#define GPIO_PIN_NUM_A4						4
#define GPIO_PIN_NUM_A5						5
#define GPIO_PIN_NUM_A6						6
#define GPIO_PIN_NUM_A7						7
#define GPIO_PIN_NUM_A8						8
#define GPIO_PIN_NUM_A9						9
#define GPIO_PIN_NUM_A10					10
#define GPIO_PIN_NUM_A11					11
#define GPIO_PIN_NUM_A12					12
#define GPIO_PIN_NUM_A13					13
#define GPIO_PIN_NUM_A14					14
#define GPIO_PIN_NUM_A15					15

/*******************GPIOB PINS***************/
#define GPIO_PIN_NUM_B0						16
#define GPIO_PIN_NUM_B1						17
#define GPIO_PIN_NUM_B2						18
#define GPIO_PIN_NUM_B3						19
#define GPIO_PIN_NUM_B4						20
#define GPIO_PIN_NUM_B5						21
#define GPIO_PIN_NUM_B6						22
#define GPIO_PIN_NUM_B7						23
#define GPIO_PIN_NUM_B8						24
#define GPIO_PIN_NUM_B9						25
#define GPIO_PIN_NUM_B10					26
#define GPIO_PIN_NUM_B11					27
#define GPIO_PIN_NUM_B12					28
#define GPIO_PIN_NUM_B13					29
#define GPIO_PIN_NUM_B14					30
#define GPIO_PIN_NUM_B15					31


/*******************GPIOC PINS***************/
#define GPIO_PIN_NUM_C13					45
#define GPIO_PIN_NUM_C14					46
#define GPIO_PIN_NUM_C15					47

/********************GPIO PINS Mode********************/
#define GPIO_INPUT							0
#define GPIO_OUTPUT							1
#define GPIO_ALTERNATE_FUNCTION				2
#define GPIO_ANALOG							3
#define GPIO_NULL							4


/******************* Atomic Value ***********************/
#define GPIO_SET							0
#define GPIO_RESET							1


/******************* GPIO Value ***********************/
#define GPIO_LOW							0
#define GPIO_HIGH							1

/********************GPIO Output type********************/
#define GPIO_PUSH_PULL						0
#define OPEN_DRAIN							1

/********************GPIO output speed********************/
#define SPEED_LOW							0
#define SPEED_MEDIUM						1
#define SPEED_HIGH							2
#define SPEED_VERY_HIGH						3

/********************GPIO output pull up /pull down********************/
#define NO_PULL_UP_PULL_DOWN				0
#define PULL_UP								1
#define PULL_DOWN							2

/********************Alternate Functions value********************/

#define AF_System							0

#define AF_TIMR_1							1
#define AF_TIMR_2							1

#define AF_TIMR_3							2
#define AF_TIMR_4							2
#define AF_TIMR_5							2

#define AF_TIMR_9							3
#define AF_TIMR_10							3
#define AF_TIMR_11							3

#define AF_I2C_1							4
#define AF_I2C_3							4

#define AF_SPI_1							5
#define AF_SPI_2							5
#define AF_SPI_4							5

#define AF_SPI_3							6

#define	AF_USART_1							7
#define	AF_USART_2							7

#define	AF_USART_6							8

#define AF_I2C_2							9

#define	AF_OTG_FS							10

#define	AF_SDIO								12

#define	AF_EVENTOUT							15
/*=======================================================================================================================================
=========================================================================================================================================*/


/*******************************Function prototype*************************/

void GPIO_init(void);

void GPIO_setAtomicBit(u8 _PINxNum , u8 _state);

void GPIO_writePinVal(u8 _PINxNum, u8 _val);
void GPIO_readPinVal(u8 _PINxNum, u8* _pval);

void GPIO_writeGroupVal(u8 _size ,u8* _PINxNum, u8* _pval);




#endif
