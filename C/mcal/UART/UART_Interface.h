#ifndef UART_H
#define UART_H

/*bits*/
#define TXSTA_TX9           (6)
#define TXSTA_TXEN          (5)
#define TXSTA_SYNC          (4)
#define TXSTA_BRGH          (2)
#define TXSTA_TRMT          (1)

#define RCSTA_SPEN          (7)
#define RCSTA_RX9           (6)
#define RCSTA_CREN          (4)

#define TRISC_TRISC7        (7)

#define PIR1_RCIF           (5)

#define BAUDCTL_BRG16       (3)

#define DISABLE             (0)
#define EVEN_PARITY         (1)
#define ODD_PARITY          (2)
#define DATA_SIZE_5_BIT     (0)
#define DATA_SIZE_6_BIT     (1)
#define DATA_SIZE_7_BIT     (2)
#define DATA_SIZE_8_BIT     (3)
#define DATA_SIZE_9_BIT     (0)

#define UDRE_UCSRA          (5)
#define RXC_UCSRA           (7)
#define UMSEL_UCSRC         (6)
#define UPM1_UCSRC          (5)
#define UPM0_UCSRC          (4)
#define TXEN_UCSRB          (3)
#define RXEN_UCSRB          (4)
#define USBS_UCSRC          (4)
#define UCSZ0_UCSRC         (1)
#define UCSZ1_UCSRC         (2)
#define UCSZ2_UCSRB         (2)
#define URSEL_UCSRC         (7)

error_t UART_Init(void);
error_t UART_Transmit(uint8_t data);
error_t UART_Receive(uint8_t * data);
error_t ClearFlag(void);
#endif
