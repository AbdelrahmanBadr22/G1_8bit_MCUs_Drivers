#ifndef UART_H
#define UART_H

error_t UART_Init(void);
error_t UART_Transmit(uint8_t data);
error_t UART_Receive(uint8_t * data);
error_t ClearFlag(void);
#endif
