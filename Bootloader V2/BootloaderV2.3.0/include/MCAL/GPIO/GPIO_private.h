/*****************************************************************/
/* Author  : El-Neshwy                                           */
/* Layer   : MCAL                                                */
/* SWC     : GPIO                                                */
/* Version : 1.0                                                 */
/* Date    : 09 Oct 2023                                         */
/*****************************************************************/
#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_

#define TWO_BIT_MASK				(0x3)
#define ONE_BIT_MASK				(0x1)
#define Alternative_Mask			0xF
#define PORT_SIZE					16


#define GPIO_A_BASE_ADDRESS			(0x40020000)
#define GPIO_B_BASE_ADDRESS			(0x40020400)
#define GPIO_C_BASE_ADDRESS			(0x40020800)

typedef struct
{
	u32 ModeR;
	u32 TypeR;
	u32 SpeedR;
	u32 PUPDR;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 LCKR;
	u32 AFRL;
	u32 AFRH;
}GPIOx_t;

#define GPIOA ((volatile GPIOx_t*)GPIO_A_BASE_ADDRESS)

#define GPIOB ((volatile GPIOx_t*)GPIO_B_BASE_ADDRESS)

#define GPIOC ((volatile GPIOx_t*)GPIO_C_BASE_ADDRESS)


/*******************Pin configurations*********************/
typedef struct
{
	/*Setting PIN Mode(OUTPUT,INPUT,ALTERNATE FUNCTION,ANALOG)*/
	u8 PinxMode; 
	/*
	* incase pin mode is output
	* Setting PIN type is its open Drain or Push pull 
	* Select pin Speed (LOW,Medium,High,Very High)
	*/
	u8 PinxType;
	u8 PinxSpeed;
	
	/*
	* incase pin Mode is Input 
	* Setting PIN interfacing Mode is it pull up or pull down or external interface
	*/
	u8 PinxPUPD;
	
	/*
	* incase pin Mode is Alternate FUNCTION 
	* Setting PIN peripheral access
	*/
	u8 PinxAF;
	
	
}PINx_Config;

extern PINx_Config Config_arr[GPIO_PIN_NUM];
#endif