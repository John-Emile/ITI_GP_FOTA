#ifndef MGPIO_PRIVATE_H_
#define MGPIO_PRIVATE_H_

#include"STD_Types.h"
#define GPIOA_BASE_ADDRESS  (0x40020000)
#define GPIOB_BASE_ADDRESS  (0x40020400)
#define GPIOC_BASE_ADDRESS  (0x40020800)


typedef struct
{
	uint32 GPIOx_MODER;
	uint32 GPIOx_OTYPER;
	uint32 GPIOx_OSPEEDR;
	uint32 GPIOx_PUPDR;
	uint32 GPIOx_IDR;
	uint32 GPIOx_ODR;
	uint32 GPIOx_BSRR;
	uint32 GPIOx_LCKR;
	uint32 AFRL;
	uint32 AFRH;

}GPIOX_t;


#define GPIOA     ((volatile GPIOX_t*)GPIOA_BASE_ADDRESS)
#define GPIOB     ((volatile GPIOX_t*)GPIOB_BASE_ADDRESS)
#define GPIOC     ((volatile GPIOX_t*)GPIOC_BASE_ADDRESS)

#define MASK  0b11
#define Alternative_Mask  0xF

#endif /* MGPIO_PRIVATE_H_ */
