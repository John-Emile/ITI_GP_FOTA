
#ifndef MAURT_PRIVATE_H_
#define MAURT_PRIVATE_H_

/* Base address of the three UARTS */
#define BASE_ADDRESS_UASRT1  (0x40011000) // At APB1 bus//
#define BASE_ADDRESS_UASRT2  (0x40004400) // At APB1 bus//
#define BASE_ADDRESS_UASRT6  (0x40011400) // At APB1 bus//

/*Structure to access the bits in register CR1*/
typedef struct
{
	u32 SBK      :1;
	u32 RWU      :1;
	u32 RE       :1;
	u32 TE       :1;
	u32 IDLEIE   :1;
	u32 RXNEIE   :1;
	u32 TCIE     :1;
	u32 TXEIE    :1;
	u32 PEIE     :1;
	u32 PS       :1;
	u32 PCE      :1;
	u32 WAKE     :1;
	u32 M        :1;
	u32 UE       :1;
	u32 Reserved :1;
	u32  OVER8   :1;
	u32 RESERVED :16;


}MUART_CR1	;

/* structure that contains the UART registers */
typedef struct
{
	u32    USART_SR;
	u32    USART_DR;
	u32   USART_BRR;
	MUART_CR1      CR1;
	u32   USART_CR2;
	u32   USART_CR3;
	u32  USART_GTPR;
}MUART_t;

/*Pointer to structure to access the elements of the struct*/
#define UART1     ((volatile MUART_t*)BASE_ADDRESS_UASRT1)
#define UART2     ((volatile MUART_t*)BASE_ADDRESS_UASRT2)
#define UART6     ((volatile MUART_t*)BASE_ADDRESS_UASRT6)

/*For mantissa and div_farction values*/
#define DIV_MANTISSA_9600_OVER8_0           0x68
#define DIV_MANTISSA_9600_OVER8_1           0xD0
#define DIV_FRACTION_9600_OVER8_0           0x3
#define DIV_FRACTION_9600_OVER8_1           0x5

/*Bits for CR2 register*/
#define CLK_POL                 10
#define CLK_PH                  9
/*Bits for statues register*/
#define T_COMPLETE              6
#define READ_REG_NOT_EMPTY      5

#endif /* MAURT_PRIVATE_H_ */
