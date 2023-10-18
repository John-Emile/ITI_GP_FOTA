/*
 * GPIO_Private.h
 *
 *  Created on: Sep 7, 2023
 *      Author: mayke
 */

#ifndef MCAL_GPIO_GPIO_PRIVATE_H_
#define MCAL_GPIO_GPIO_PRIVATE_H_


/*
 ******************************************************************
 ******************************************************************
 ***********************Base Addresses For GPIOx*******************
 ******************************************************************
 */

#define GPIOA_BASE_ADDRESS                  (0x40020000)

#define GPIOB_BASE_ADDRESS                  (0x40020400)

#define GPIOC_BASE_ADDRESS                  (0x40020800)

#define GPIOD_BASE_ADDRESS                  (0x40020C00)

#define GPIOE_BASE_ADDRESS                  (0x40021000)

#define GPIOH_BASE_ADDRESS                  (0x40021C00)

/*
 ******************************************************************
 ******************************************************************
 ***********************GPIO Register Map**************************
 *			Define each register port for each GPIO
 ******************************************************************
 */

// #define GPIO_MODER 				(((volatile u32*)GPIOA_BASE_ADDRESS+0x00)

/*
 ******************************************************************
 ******************************************************************
 ***********************GPIO Register Map(register Definition)*****
 ******************************************************************
 */

typedef struct
{
	volatile u32 MODER ;  //GPIO port mode register  			(address offset : 0x00)
	volatile u32 OTYPER ; //GPIO port output type register  	(address offset : 0x04)
	volatile u32 OSPEEDR ;//GPIO port output speed register  	(address offset : 0x08)
	volatile u32 PUPDR ;  //GPIO port pull up/ pull down register  (address offset : 0x0C)
	volatile u32 IDR ;    //GPIO port input data register  		(address offset : 0x10)
	volatile u32 ODR ;    //GPIO port output data register  	(address offset : 0x14)
	volatile u32 BSRR ;   //GPIO port bit set/reset register  	(address offset : 0x18)
	volatile u32 LCKR ;   //GPIO port Lock Pin register  		(address offset : 0x1C)
	volatile u32 AFRL ;   //GPIO port Alternate Function Low register  (address offset : 0x20)
	volatile u32 AFRH ;   //GPIO port Alternate Function High  	(address offset : 0x24)

}GPIOx_r;

/*
 ******************************************************************
 ******************************************************************
 ***********************Struct Base Addresses For GPIOA************
 ******************************************************************
 */
#define MGPIOA			((volatile GPIOx_r*)GPIOA_BASE_ADDRESS)
/*
 ******************************************************************
 ******************************************************************
 ***********************Struct Base Addresses For GPIOB************
 ******************************************************************
 */
#define MGPIOB			((volatile GPIOx_r*)GPIOB_BASE_ADDRESS)
/*
 ******************************************************************
 ******************************************************************
 ***********************Struct Base Addresses For GPIOC************
 ******************************************************************
 */
#define MGPIOC			((volatile GPIOx_r*)GPIOC_BASE_ADDRESS)
/*
 ******************************************************************
 ******************************************************************
 ***********************Struct Base Addresses For GPIOD************
 ******************************************************************
 */
#define MGPIOD			((volatile GPIOx_r*)GPIOD_BASE_ADDRESS)
/*
 ******************************************************************
 ******************************************************************
 ***********************Struct Base Addresses For GPIOE************
 ******************************************************************
 */
#define MGPIOE			((volatile GPIOx_r*)GPIOE_BASE_ADDRESS)
/*
 ******************************************************************
 ******************************************************************
 ***********************Struct Base Addresses For GPIOH************
 ******************************************************************
 */
#define MGPIOH			((volatile GPIOx_r*)GPIOH_BASE_ADDRESS)


#endif /* MCAL_GPIO_GPIO_PRIVATE_H_ */
