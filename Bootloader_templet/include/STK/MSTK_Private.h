/*
 * MSTK_Private.h
 *
 *  Created on: Sep 12, 2023
 *      Author: mayke
 */

#ifndef STK_MSTK_PRIVATE_H_
#define STK_MSTK_PRIVATE_H_


#define STK_BASE_ADDRESS		(0xE000E010)

typedef struct
{
	volatile u32 STK_CTRL;
	volatile u32 STK_LOAD;
	volatile u32 STK_VAL;
	volatile u32 STK_CALIB;
}STK_t;


#define MSTK			((volatile STK_t*)STK_BASE_ADDRESS)

#endif /* STK_MSTK_PRIVATE_H_ */
