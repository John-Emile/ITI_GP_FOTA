/*****************************************************************/
/* Author  : Abdelrahman                                         */
/* SWC     : MNVIC                                               */
/* Version : 1.0                                                 */
/* Date    : 11 Sep 2023                                         */
/*****************************************************************/

#ifndef MNVIC_INTERFACE_H_
#define MNVIC_INTERFACE_H_

typedef enum
{
	Group16_Sub0=3,
	Group8_Sub2,
	Group4_Sub4,
	Group2_Sub8,
	Group0_Sub16
}NVIC_GROUP_t;


void MNVIC_vidEnableInt(u8 u8PostionCpy);
void MNVIC_vidDisableInt(u8 u8PostionCpy);

void MNVIC_vidEnablePendingFlag(u8 u8PostionCpy);
void MNVIC_vidDisablePendingFlag(u8 u8PostionCpy);

void MNVIC_vidIsIntActive(u8 u8PostionCpy, u8* pu8ReadCpy);
void MNVIC_vidSetIntGroupMode(NVIC_GROUP_t GroupModeCpy);

void MNVIC_vidSetIntPriority(u8 u8PostionCpy, u8 u8GroupNumCpy,u8 u8SubGroupNumCpy);


#endif
