#include "Config.h"
#include "Types.h"
#include "Utils.h"
#include "Registes.h"
#include "UART_Config.h"
#include "UART_Interface.h"

//-----------------------------------------------------------------------------
///////////////// HELPER FUNCTIONS ////////////////////////////////////////////
//-----------------------------------------------------------------------------
#if IS_AVR()
uint8_t ucsrcVal=0;
static void AVR_PARITY_MODE()
{
    #if UART_PARITY_MODE == DISABLE
    CLR_BIT(ucsrcVal, UPM0_UCSRC);
    CLR_BIT(ucsrcVal, UPM1_UCSRC);
    #elif UART_PARITY_MODE == EVEN_PARITY
    CLR_BIT(ucsrcVal, UPM0_UCSRC);
    SET_BIT(ucsrcVal, UPM1_UCSRC);
    #elif UART_PARITY_MODE == ODD_PARITY
    SET_BIT(ucsrcVal, UPM0_UCSRC);
    SET_BIT(ucsrcVal, UPM1_UCSRC);
    #else
    #error "wrong UART_PARITY_MODE config"
    #endif
}
static void UART_DATA_SIZE()
{
    #if IS_AVR()
    #if USART_DATA_SIZE == DATA_SIZE_5_BIT
    CLR_BIT(ucsrcVal, UCSZ0_UCSRC);
    CLR_BIT(ucsrcVal, UCSZ1_UCSRC);
    CLR_BIT(ucsrcVal, UCSZ2_UCSRB);
    #elif USART_DATA_SIZE == DATA_SIZE_6_BIT
    SET_BIT(ucsrcVal, UCSZ0_UCSRC);
    CLR_BIT(ucsrcVal, UCSZ1_UCSRC);
    CLR_BIT(ucsrcVal, UCSZ2_UCSRB);
    #elif USART_DATA_SIZE == DATA_SIZE_7_BIT
    CLR_BIT(ucsrcVal, UCSZ0_UCSRC);
    SET_BIT(ucsrcVal, UCSZ1_UCSRC);
    CLR_BIT(ucsrcVal, UCSZ2_UCSRB);
    #elif USART_DATA_SIZE == DATA_SIZE_8_BIT
    SET_BIT(ucsrcVal, UCSZ0_UCSRC);
    SET_BIT(ucsrcVal, UCSZ1_UCSRC);
    CLR_BIT(ucsrcVal, UCSZ2_UCSRB);
    #elif USART_DATA_SIZE == DATA_SIZE_9_BIT
    SET_BIT(ucsrcVal, UCSZ0_UCSRC);
    SET_BIT(ucsrcVal, UCSZ1_UCSRC);
    SET_BIT(ucsrcVal, UCSZ2_UCSRB);
    #endif
    #elif IS_PIC()
    #if USART_DATA_SIZE == DATA_SIZE_8_BIT
    CLR_BIT(TXSTA_REG, TXSTA_TX9);
    CLR_BIT(RCSTA_REG, RCSTA_RX9);
    #elif USART_DATA_SIZE == DATA_SIZE_9_BIT
    SET_BIT(TXSTA_REG, TXSTA_TX9);
    SET_BIT(RCSTA_REG, RCSTA_RX9);
    #endif
    #else
    #error "Unkown MCU"
    #endif
}
static void AVR_UART_Init()
{
    /*Asynchronous mode*/
    CLR_BIT(ucsrcVal, UMSEL_UCSRC);
    AVR_PARITY_MODE();
    /*Transmitter Enable*/
    SET_BIT(ucsrcVal, TXEN_UCSRB);
    /*Receiver Enable*/
    SET_BIT(ucsrcVal, RXEN_UCSRB);
    /*Stop Bit*/
    CLR_BIT(ucsrcVal, USBS_UCSRC);
    /*Data Size*/
    UART_DATA_SIZE();
    SET_BIT(ucsrcVal, URSEL_UCSRC);
    UCSRC_REG=ucsrcVal;
    /*Baud Rate 9600*/
    UBRRL_REG=103;
}
#elif IS_PIC()
static void PIC_UART_Init()
{
    /*Asynchronous mode*/
    SET_BIT(RCSTA_REG, RCSTA_SPEN);
    CLR_BIT(TXSTA_REG, TXSTA_SYNC);
    /*Data Size*/
    UART_DATA_SIZE();
    /*Baud Rate High Speed*/
    SET_BIT(TXSTA_REG, TXSTA_BRGH);
    CLR_BIT(BAUDCTL_REG, BAUDCTL_BRG16);
    SPBRGH_REG = 51;
    /*TRIS Control*/
    SET_BIT(TRISC_REG, TRISC_TRISC7);
    /*Transmitter Enable*/
    SET_BIT(TXSTA_REG, TXSTA_TXEN);
    /*Receiver Enable*/
    SET_BIT(RCSTA_REG, RCSTA_CREN);
}
#endif

//-----------------------------------------------------------------------------
///////////////// UART FUNCTIONS ///////////////////////////////////////////////
//-----------------------------------------------------------------------------
error_t UART_Init(void)
{
    error_t kErrorState = kNoError;
    #if IS_AVR()
    AVR_UART_Init();
    #elif IS_PIC()
    PIC_UART_Init();
    #else
    #error "Unkown MCU"
    #endif
    return kErrorState;
}
error_t UART_Transmit(uint8_t data)
{
    error_t kErrorState = kNoError;
    #if IS_AVR()
    #define UART_WRITE_REG              (UDR_REG)
    #define UART_GET_TRANSMIT_STATUS()  (GET_BIT(UCSRA_REG, UDRE_UCSRA))
    #elif IS_PIC()
    #define UART_WRITE_REG              (TXREG_REG)
    #define UART_GET_TRANSMIT_STATUS()  (GET_BIT(TXSTA_REG, TXSTA_TRMT))
    #else
    #error "Unkown MCU"
    #endif
    while (UART_GET_TRANSMIT_STATUS() == 0)
    {

    }
    UART_WRITE_REG= data;
    return kErrorState;
}
error_t UART_Receive(uint8_t *data)
{
    error_t kErrorState = kNoError;
    #if IS_AVR()
    #define UART_WRITE_REG              (UDR_REG)
    #define UART_GET_RECEIVE_STATUS()  (GET_BIT(UCSRA_REG, RXC_UCSRA))
    #elif IS_PIC()
    #define UART_WRITE_REG              (RCREG_REG)
    #define UART_GET_RECEIVE_STATUS()  (GET_BIT(PIR1_REG, PIR1_RCIF))
    #else
    #error "Unkown MCU"
    #endif
    while ((UART_GET_RECEIVE_STATUS()) == 0)
    {

    }
    *data = UART_WRITE_REG;
    return kErrorState;
}
#if IS_PIC()
error_t ClearFlag(void)
{
    error_t kErrorState = kNoError;
    if ((GET_BIT(PIR1_REG, PIR1_RCIF)) == 1)
    {
      CLR_BIT(PIR1_REG, PIR1_RCIF);
    }
    return kErrorState;
}
#endif
