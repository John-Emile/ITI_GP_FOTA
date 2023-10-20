/*****************************************************************/
/* Author  : Dell                                                */
/* Layer   : MCAL                                                */
/* SWC     : Fls                                                 */
/* Version : 1.0                                                 */
/* Date    : 16 Oct 2023                                         */
/*****************************************************************/
#ifndef FLS_INTERFACE_H_
#define FLS_INTERFACE_H_

#include <LIB/STD_Types.h>

#define SECTOR_0							0
#define SECTOR_1							1
#define SECTOR_2							2
#define SECTOR_3							3
#define SECTOR_4							4
#define SECTOR_5							5



/**************************************** prototypes ********************************************/

/*  Initializing Flash Driver*/
void Fls_Init(void);

/*Erase Specific Sector*/
tenuErrrorStatus Fls_earseSector(u8 _sectorNo);

/*Erase Application area*/
tenuErrrorStatus Fls_earseAppArea(void);

/*
 * Write Data to Specific address
 * You can select Word size (PROGRAM_SIZE_8)(PROGRAM_SIZE_16)(PROGRAM_SIZE_32)(PROGRAM_SIZE_64) from config.h
 */

tenuErrrorStatus Fls_write(u32 _Address,u16* _data,u8 _dataLength);
#endif
