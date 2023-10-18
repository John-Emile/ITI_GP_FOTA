/*
 * Bit_Math.h
 *
 *  Created on: Aug 5, 2023
 *      Author: mayke
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_


#define SET_BIT(REG,BIT)    REG=(REG | (1<<BIT))
#define CLR_BIT(REG,BIT)	REG=(REG & ~(1<<BIT))
#define TGL_BIT(REG,BIT)    REG=(REG^(1<<BIT)  )
#define GET_BIT(REG,BIT)    ((REG >>(BIT))&1)

#endif /* BIT_MATH_H_ */
