/*
 * STD_TYPES.h
 *
 *  Created on: 2 Nov 2023
 *      Author: VGA!
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;

typedef signed char s8;
typedef signed short int s16;
typedef signed long int s32;

typedef float f32;
typedef double f64;


#define NULL_PTR  			((void*)0)
typedef void (*pf)(void);

typedef enum
{
	EOK=0,
	ENOK,
	PARAMRETER_OUT_RANGE,
	PARAMERTE_NULL_PTR

}tenuErrrorStatus;




#endif /* STD_TYPES_H_ */
