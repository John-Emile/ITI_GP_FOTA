/*
 * GPIO_Private.h
 *
 *  Created on: 2 Nov 2023
 *      Author: VGA!
 */

#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_
#define GPIOA_BASE_ADDRESS  (0x40020000)
#define GPIOB_BASE_ADDRESS  (0x40020400)
#define GPIOC_BASE_ADDRESS  (0x40020800)


typedef struct
{
	u32 GPIOx_MODER;
	u32 GPIOx_OTYPER;
	u32 GPIOx_OSPEEDR;
	u32 GPIOx_PUPDR;
	u32 GPIOx_IDR;
	u32 GPIOx_ODR;
	u32 GPIOx_BSRR;
	u32 GPIOx_LCKR;
	u32 AFRL;
	u32 AFRH;

}GPIOX_t;


#define GPIOA     ((volatile GPIOX_t*)GPIOA_BASE_ADDRESS)
#define GPIOB     ((volatile GPIOX_t*)GPIOB_BASE_ADDRESS)
#define GPIOC     ((volatile GPIOX_t*)GPIOC_BASE_ADDRESS)

#define MASK  0b11
#define Alternative_Mask  0xF


#endif /* GPIO_PRIVATE_H_ */
