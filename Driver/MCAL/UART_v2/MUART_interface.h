

#ifndef MUART_INTERFACE_H_
#define MUART_INTERFACE_H_

typedef enum
{
	ONE_STOP,TWO_STOP=2
}STOP_BITS;

/*For enable and disable of UART*/
#define UART_ENABLE                     1
#define UART_DISABLE                    0
/*For Data length*/
#define UART_8_BITS                     0
#define UART_9_BITS                     1
/*For Clk Polarity*/
#define UART_CLK_POL_LOW                0
#define UART_CLK_POL_HIGH               1
/*For Clk Phase*/
#define UART_CLK_PH_FIRST               0
#define UART_CLK_PH_SECOND              1
/*For the stop bits*/
#define UART_1_STOP_BIT                 0
#define UART_2_STOP_BIT                 1
/*For parity enable*/
#define UART_PARITY_EN                  1
#define UART_PARITY_DIS                 0
/*For parity selection*/
#define UART_PARITY_EVEN                0
#define UART_PARITY_ODD                 1
/*For oversampling*/
#define UART_OVRSMPL_16                 0
#define UART_OVRSMPL_8                  1
/*For number of UART*/
#define UART_1                          0
#define UART_2                          1
#define UART_6                          2


void MUART_voidInit(void);
void MUART_Transmit(uint8* u8DataCPY, uint8 u8UART_Number_CPY);
void MUART_TransmitByte(uint8 u8Data,uint8 u8UART_Number_CPY);
void MUART_Recieve(uint8* u8DataCPY,uint8 u8UART_Number_CPY);
uint8 MUART_RecieveAsynch(uint8 *u8Data_CPY,uint8 u8UART_Number_CPY);
void MUART_voidCallBack(void(*ptr)(void));




#endif /* MUART_INTERFACE_H_ */
