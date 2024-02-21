#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

#define USART_PARITY_MODE  (DISABLE)
#define USART_DATA_SIZE    (DATA_SIZE_8_BIT)

#if USART_PARITY_MODE != DISABLE
#if USART_PARITY_MODE != EVEN_PARITY
#if USART_PARITY_MODE != ODD_PARITY
#error "[UART_Config] : Invalid Parity Mode"
#endif
#endif
#endif

#if USART_DATA_SIZE != DATA_SIZE_5_BIT
#if USART_DATA_SIZE != DATA_SIZE_6_BIT
#if USART_DATA_SIZE != DATA_SIZE_7_BIT
#if USART_DATA_SIZE != DATA_SIZE_8_BIT
#if USART_DATA_SIZE != DATA_SIZE_9_BIT
#error "[UART_Config] : Invalid Data Size"
#endif
#endif
#endif
#endif
#endif
#endif
