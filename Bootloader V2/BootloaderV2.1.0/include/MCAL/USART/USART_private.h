/*****************************************************************/
/* Author  : Dell                                                */
/* SWC     : USART                                               */
/* Version : 1.0                                                 */
/* Date    : 19 Sep 2023                                         */
/*****************************************************************/
#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_

#define USART_1_BASE_ADDRESS					(0x40011000)
#define USART_2_BASE_ADDRESS					(0x40004400)
#define USART_6_BASE_ADDRESS					(0x40011400)

#define STOP_1BIT				0
#define STOP_2BIT				2


#define ENABLE					1
#define DISABLE					0

#define USART_OVER_8			1
#define USART_OVER_16			0

#define USART_MODE_8_BIT		0
#define USART_MODE_9_BIT		1


#define USART_EVEN_PARITY		0
#define USART_ODD_PARITY		1
#define USART_NO_PARITY			2

typedef struct
{
	u32	SBK				:1;
	u32	RWU				:1;
	u32	RE				:1;
	u32	TE				:1;
	u32	IDLEIE			:1;
	u32	RXNEIE			:1;
	u32	TCIE			:1;
	u32	TXEIE			:1;
	u32	PEIE			:1;
	u32	PS				:1;
	u32	PCE				:1;
	u32	WAKE			:1;
	u32	M				:1;
	u32	UE				:1;
	u32	Reserved1		:1;
	u32	OVER8			:1;
	u32	Reserved2		:16;
}MUSART_CR1;

typedef struct
{
	u32 SR;
	u32 DR;
	u32 BRR;
	MUSART_CR1 CR1;
	u32 CR2;
	u32 CR3;
	u32 GTPR;
}MUSRAT_t;


#define USART1						((volatile MUSRAT_t*)USART_1_BASE_ADDRESS)
#define USART2						((volatile MUSRAT_t*)USART_2_BASE_ADDRESS)
#define USART6						((volatile MUSRAT_t*)USART_6_BASE_ADDRESS)



#endif
