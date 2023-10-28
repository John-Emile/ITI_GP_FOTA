/*****************************************************************/
/* Author  : Abdelrahman                                         */
/* SWC     : MNVIC                                               */
/* Version : 1.0                                                 */
/* Date    : 11 Sep 2023                                         */
/*****************************************************************/

#ifndef MNVIC_PRIVATE_H_
#define MNVIC_PRIVATE_H_

#include <LIB/STD_Types.h>


#define NVIC_BASE_ADDRESS				(0xE000E100)


typedef struct
{
	u32 ISER[8];
	u32 RESERVED1[24];
	u32 ICER[8];
	u32 RESERVED2[24];
	u32 ISPR[8];
	u32 RESERVED3[24];
	u32 ICPR[8];
	u32 RESERVED4[24];
	u32 IABR[8];
	u32 RESERVED5[56];
	u8 IPR[240];
	u32 RESERVED6[580];
	u32 STIR;
}NVIC_t;


#define NVIC		((volatile NVIC_t*)NVIC_BASE_ADDRESS)

#define SCB_AIRCR				(*(volatile u32*)0xE000ED0C)

#define MNVIC_VECT_KEY			0x05FA0000

#define REG_SIZE				32
#endif
