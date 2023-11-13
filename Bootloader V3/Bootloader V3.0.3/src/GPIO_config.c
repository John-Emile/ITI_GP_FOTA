#include <LIB/STD_TYPES.h>
#include <LIB/BIT_MATH.h>
#include <MCAL/GPIO/GPIO_interface.h>
#include <MCAL/GPIO/GPIO_config.h>
#include <MCAL/GPIO/GPIO_private.h>


PINx_Config Config_arr[GPIO_PIN_NUM] = {
	/*MODE			Type				Speed			PUPD			AF*/
								/*GPIOA_PIN_NUM_A0*/
	{GPIO_OUTPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_DOWN,		AF_System},
								/*GPIOA_PIN_NUM_A1*/
	{GPIO_OUTPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_DOWN,		AF_System},
								/*GPIOA_PIN_NUM_A2*/
	{GPIO_OUTPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
								/*GPIOA_PIN_NUM_A3*/
	{GPIO_OUTPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
								/*GPIOA_PIN_NUM_A4*/
	{GPIO_OUTPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
								/*GPIOA_PIN_NUM_A5*/
	{GPIO_OUTPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
								/*GPIOA_PIN_NUM_A6*/
	{GPIO_OUTPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
								/*GPIOA_PIN_NUM_A7*/
	{GPIO_OUTPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
								/*GPIOA_PIN_NUM_A8*/
	{GPIO_OUTPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
								/*GPIOA_PIN_NUM_A9*/
	{GPIO_OUTPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
								/*GPIOA_PIN_NUM_A10*/
	{GPIO_OUTPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
								/*GPIOA_PIN_NUM_A11*/
	{GPIO_OUTPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
								/*GPIOA_PIN_NUM_A12*/
	{GPIO_OUTPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
	
	
	
		/**********	its Forbedin to access any Pin of A13 A14 A15 so its Mode Set NUll**********/
								/*GPIOA_PIN_NUM_A13*/
	{GPIO_NULL	,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
								/*GPIOA_PIN_NUM_A14*/
	{GPIO_NULL	,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
								/*GPIOA_PIN_NUM_A15*/
	{GPIO_NULL	,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
		/**********	its Forbedin to access any Pin of A13 A14 A15 so its Mode Set NUll**********/
	
	
	
								/*GPIOB_PIN_NUM_B0*/
	{GPIO_INPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
								/*GPIOB_PIN_NUM_B1*/
	{GPIO_OUTPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
								/*GPIOB_PIN_NUM_B2*/
	{GPIO_OUTPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
	
	
	
			/**********	its Forbedin to access any Pin of B3 B4 so its Mode Set NUll**********/
								/*GPIOB_PIN_NUM_B3*/
	{GPIO_NULL	,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},		
								/*GPIOB_PIN_NUM_B4*/
	{GPIO_NULL	,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
			/**********	its Forbedin to access any Pin of B3 B4 so its Mode Set NUll**********/



								/*GPIOB_PIN_NUM_B5*/
	{GPIO_OUTPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
								/*GPIOB_PIN_NUM_B6*/
	{GPIO_ALTERNATE_FUNCTION,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_USART_1},
								/*GPIOB_PIN_NUM_B7*/
	{GPIO_ALTERNATE_FUNCTION,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_USART_1},
								/*GPIOB_PIN_NUM_B8*/
	{GPIO_OUTPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
								/*GPIOB_PIN_NUM_B9*/
	{GPIO_OUTPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
								/*GPIOB_PIN_NUM_B10*/
	{GPIO_OUTPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
								/*GPIOB_PIN_NUM_B11*/
	{GPIO_OUTPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
								/*GPIOB_PIN_NUM_B12*/
	{GPIO_OUTPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
								/*GPIOB_PIN_NUM_B13*/
	{GPIO_OUTPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
								/*GPIOB_PIN_NUM_B14*/
	{GPIO_OUTPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
								/*GPIOB_PIN_NUM_B15*/
	{GPIO_OUTPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},


								/*GPIOC_PIN_NUM_C13*/
	{GPIO_OUTPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
								/*GPIOC_PIN_NUM_C14*/
	{GPIO_OUTPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System},
								/*GPIOC_PIN_NUM_C15*/
	{GPIO_OUTPUT,	GPIO_PUSH_PULL,		SPEED_LOW,		PULL_UP,		AF_System}
};
