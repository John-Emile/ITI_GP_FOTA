/*
 * MSTK_Interface.h
 *
 *  Created on: Sep 12, 2023
 *      Author: Hesham Yasser
 */

#ifndef MSTK_INTERFACE_H_
#define MSTK_INTERFACE_H_


void MSTK_voidInit(void);

void MSTK_voidClearCurrentValue (void);

void MSTK_voidSetPreloadValue (u32 A_u32PreLoadVal);

void MSTK_voidGetFlagValue (u8 * p_Read);

void MSTK_voidEnableSTK (void);

void MSTK_voiDisableSTK (void);

void MSTK_voidGetElapsedTime (u32 * p_Read);

void MSTK_voidGetRemainingTime (u32 * p_Read);

void MSTK_voidEnableInterrupt (void);

void MSTK_voidDisableInterrupt (void);

void MSTK_voidDelayms (u32 A_u32Delayms);

void MSTK_voidDelayus (u32 A_u32Delayus);

void MSTK_asyncDelayms (u32 A_u32Delayms,pf ptr);

void MSYSTICK_CallBack(void(*ptr)(void));

#endif /* MSTK_INTERFACE_H_ */
