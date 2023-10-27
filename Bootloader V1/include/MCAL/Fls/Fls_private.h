/*****************************************************************/
/* Author  : Dell                                                */
/* Layer   : MCAL                                                */
/* SWC     : Fls                                                 */
/* Version : 1.0                                                 */
/* Date    : 16 Oct 2023                                         */
/*****************************************************************/
#ifndef FLS_PRIVATE_H_
#define FLS_PRIVATE_H_

#define FLS_BASE_ADDRESS							(0x40023C00)

#define KEY1_CR 									(0x45670123)
#define KEY2_CR										(0xCDEF89AB)

typedef struct
{
	u32 ACR;
	u32 KEYR;
	u32 OPTKEYR;
	u32 SR;
	u32 CR;
	u32 OPTCR;
}Fls_t;

#define Fls								((volatile Fls_t*)FLS_BASE_ADDRESS)


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



#endif
