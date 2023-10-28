

#ifndef MUART_CONFIG_H_
#define MUART_CONFIG_H_

#define UART1_STATUES         UART_ENABLE

#define UART2_STATUES         UART_ENABLE

#define UART6_STATUES         UART_DISABLE

#define UART_DATA_SIZE        UART_8_BITS

#define UART_CLK_POLARITY     UART_CLK_POL_LOW

#define UART_CLK_PHASE        UART_CLK_PH_FIRST

#define UART_STOP_BITS        UART_1_STOP_BIT

#define UART_PARITY_CNTRL     UART_PARITY_DIS

#define UART_PARITY_SELC      UART_PARITY_EVEN

/*Baud-rate can be changed and calculate the Div_mantissa and Div_fraction values from the equation */
#define UART_BADURATE         9600

#define UART_OVER8            UART_OVRSMPL_16



#endif /* MUART_CONFIG_H_ */
