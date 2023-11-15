

#ifndef  STD_TYPES_H
#define  STD_TYPES_H

typedef   unsigned char      uint8  ;
typedef   unsigned short int uint16 ;
typedef   unsigned long  int uint32 ;
typedef   signed char        sint8  ;
typedef   signed short int   sint16 ;
typedef   signed long  int   sint32 ;
typedef   float              float32 ;
typedef   double             float64 ;
typedef   long double        float128 ;


typedef enum  
{
	EOK,
	ENOK,
	PARAMRETER_OUT_RANGE,
	PARAMERTE_NULL_PTR
	
}tenuErrrorStatus;

#define NULL_PTR (void *) 0
#define HIGH              1
#define LOW               0
#endif



