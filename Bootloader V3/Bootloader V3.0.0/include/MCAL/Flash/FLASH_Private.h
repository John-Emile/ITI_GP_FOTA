 /*************************************************************************************************************************************************************
 *
 * File Name: Flash_Private.h
 *
 * Description: Private header file for the Flash memory.
 *
 * Author: Abdulrahman El-Neshwy, Abdulrahman Khalaf, Aya Samir, Seba Ammar, Ziad Gomaa, John Emile
 *
 * Date : Sept 28, 2023
 *
 *************************************************************************************************************************************************************/

#ifndef FLASH_FLASH_PRIVATE_H_
#define FLASH_FLASH_PRIVATE_H_


#define MFDI_BASE_ADDRESS			0x40023C00

typedef struct
{
	volatile u32 ACR ;
	volatile u32 KEYR ;
	volatile u32 OPTKEYR;
	volatile u32 SR ;
	volatile u32 CR ;
	volatile u32 OPTCR ;
}MFDI_t;

#define MFDI_KEY1		0x45670123
#define MFDI_KEY2		0xCDEF89AB

#define WRITE_HALF_WORD		1

#define MFDI		((volatile MFDI_t*)MFDI_BASE_ADDRESS)

#endif /* FLASH_FLASH_PRIVATE_H_ */
