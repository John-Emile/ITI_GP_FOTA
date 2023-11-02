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



/*SR Bits*/
#define	EOP				    0
#define OPERR				1
#define WRPERR				4
#define PGAERR				5
#define PGPERR				6
#define PGSERR				7
#define RDERR				8
#define BSY					16

/*CR Bits*/
#define	PG				    0
#define SER					1
#define MER					2
#define STRT				16
#define EOPIE				24
#define ERRIE				25
#define LOCK				31


/* Prgoram Size*/

#define PROGRAM_SIZE_8			0
#define PROGRAM_SIZE_16			1
#define PROGRAM_SIZE_32			2
#define PROGRAM_SIZE_64			3

/* masking values*/
#define SELECT_SECTOR_MASK					0xFFFFFF87
#define SELECT_WORD_SIZE_MASK				0xFFFFFCFF


#endif /* FLASH_FLASH_PRIVATE_H_ */
