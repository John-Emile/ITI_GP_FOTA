/*
 * MSTK_Interface.h
 *
 *  Created on: Sep 12, 2023
 *      Author: Hesham Yasser
 */

#ifndef MSTK_INTERFACE_H_
#define MSTK_INTERFACE_H_

/************************************************************************************
 * Service Name: MSTK_voidInit
 * Parameters (in): None
 * Return value: None
 * Description: Initialize SystemTick.
 ************************************************************************************/

void MSTK_voidInit(void);

/************************************************************************************
 * Service Name: MSTK_voidClearCurrentValue
 * Parameters (in): None
 * Return value: None
 * Description: Clear counter value .
 ************************************************************************************/

void MSTK_voidClearCurrentValue (void);

/************************************************************************************
 * Service Name: MSTK_voidSetPreloadValue
 * Parameters (in): uint32 (hold value of Counter)
 * Return value: None
 * Description: Set new value in counter register.
 ************************************************************************************/

void MSTK_voidSetPreloadValue (u32 A_u32PreLoadVal);

/************************************************************************************
 * Service Name: MSTK_voidGetFlagValue
 * Parameters (in): uint8* (hold Address of Local variable that)
 * Return value: None
 * Description: Set value of Counter Flag value in Local Variable.
 ************************************************************************************/

void MSTK_voidGetFlagValue (u8 * p_Read);

/************************************************************************************
 * Service Name: MSTK_voidEnableSTK
 * Parameters (in): None
 * Return value: None
 * Description: Enable SystemTick.
 ************************************************************************************/

void MSTK_voidEnableSTK (void);

/************************************************************************************
 * Service Name: MSTK_voiDisableSTK
 * Parameters (in): None
 * Return value: None
 * Description: Disable SystemTick.
 ************************************************************************************/

void MSTK_voiDisableSTK (void);

/************************************************************************************
 * Service Name: MSTK_voidGetElapsedTime
 * Parameters (in): uint32* (Hold address of local variable)
 * Return value: None
 * Description: Set the elapsed time value in the Local variable.
 ************************************************************************************/

void MSTK_voidGetElapsedTime (u32 * p_Read);

/************************************************************************************
 * Service Name: MSTK_voidGetRemainingTime
 * Parameters (in): uint32* (Hold address of local variable)
 * Return value: None
 * Description: Set the Remaining time value in the Local variable.
 ************************************************************************************/

void MSTK_voidGetRemainingTime (u32 * p_Read);

/************************************************************************************
 * Service Name: MSTK_voidEnableInterrupt
 * Parameters (in): None
 * Return value: None
 * Description: Enable SystemTick Interrupt.
 ************************************************************************************/

void MSTK_voidEnableInterrupt (void);

/************************************************************************************
 * Service Name: MSTK_voidDisableInterrupt
 * Parameters (in): None
 * Return value: None
 * Description: Disable SystemTick Interrupt.
 ************************************************************************************/

void MSTK_voidDisableInterrupt (void);

/************************************************************************************
 * Service Name: MSTK_voidDelayms
 * Parameters (in): uint32 (Hold value of Delay Time in msec)
 * Return value: None
 * Description: Delay system with the required time in msec by polling.
 ************************************************************************************/

void MSTK_voidDelayms (u32 A_u32Delayms);

/************************************************************************************
 * Service Name: MSTK_voidDelayus
 * Parameters (in): uint32 (Hold value of Delay Time in usec)
 * Return value: None
 * Description: Delay system with the required time in usec by polling.
 ************************************************************************************/

void MSTK_voidDelayus (u32 A_u32Delayus);


/************************************************************************************
 * Service Name: MSTK_asyncDelayms
 * Parameters (in): uint32 (Hold value of Delay Time in msec)
 * 					pf (hold Address of Function)
 * Return value: None
 * Description: Delay Function with the required time in msec by interrupt handler.
 ************************************************************************************/

void MSTK_asyncDelayms (u32 A_u32Delayms,pf ptr);

/************************************************************************************
 * Service Name: MSTK_StopInterval
 * Parameters (in): None
 * Return value: None
 * Description: Stop systemTick.
 ************************************************************************************/

void MSTK_StopInterval(void);

/************************************************************************************
 * Service Name: MSYSTICK_CallBack
 * Parameters (in): pf (hold Address of Function)
 * Return value: None
 * Description: Set address of Function of Global pointer to Function.
 ************************************************************************************/

void MSYSTICK_CallBack(void(*ptr)(void));

#endif /* MSTK_INTERFACE_H_ */
