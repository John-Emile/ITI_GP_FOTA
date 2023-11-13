#ifndef MEXTI_INT_H
#define MEXTI_INT_H

typedef enum{
	EXTI_Enable,
	EXTI_Disable
}EXTI_ENDis;

typedef enum{
	EXTI_Rising,
	EXTI_Falling,
	EXTI_OnChange
}EXTI_Trigger;

typedef enum{
	EXTI_LineZero=0,
	EXTI_LineOne,
	EXTI_LineTwo,
	EXTI_LineThree,
	EXTI_LineFour,
	EXTI_LineFive,
	EXTI_LineSix,
	EXTI_LineSeven,
	EXTI_LineEight,
	EXTI_LineNine,
	EXTI_LineTen,
	EXTI_LineEleven,
	EXTI_LineTwelve,
	EXTI_LineThirteen,
	EXTI_LineFourteen,
	EXTI_LineFifteen

}EXTI_Line;

typedef enum{
EXTI_PortA=0,
EXTI_PortB,
EXTI_PortC,
EXTI_PortD,
EXTI_PortE,
EXTI_PortH=7,

}EXTI_Port;

















void MEXTI_voidInerruptSetPort(EXTI_Line Copy_u8Line,EXTI_Port Copy_u8Port);
void MEXTI_voidInterruptEnableDisable(EXTI_Line Copy_u8IntLine , EXTI_ENDis Copy_u8ENDis);
void MEXTI_voidInterruptTrigger(EXTI_Line Copy_u8IntLine,EXTI_Trigger Copy_u8Trig);
void MEXTI0_voidCallBack(void (*ptr)(void));
void MEXTI1_voidCallBack(void (*ptr)(void));
void MEXTI15_voidCallBack(void (*ptr)(void));








#endif
