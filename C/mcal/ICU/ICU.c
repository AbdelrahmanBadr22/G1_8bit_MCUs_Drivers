/**
 * @file ICU.c
 * @author Mohamed Refat
 * @brief
 * @version 0.1
 * @date 2024-02-18
 *
 */

#include "../../common/Config.h"
#include "../../common/Registes.h"
#include "../../common/Types.h"
#include "../../common/Utils.h"

#include "ICU.h"

void(*pICU_CallBackFunction)(void) = NULL_PTR;

#define Enable_ICU()              (SET_BIT(TIMSK, TIMSK_ICIE1))
#define Disable_ICU()             (CLR_BIT(TIMSK, TIMSK_ICIE1))

#define Enable_Noise_Canceler()   (SET_BIT(TCCR1B, TCCR1B_ICNC1))
#define Disable_Noise_Canceler()  (CLR_BIT(TCCR1B, TCCR1B_ICNC1))

#define Select_RisingEdge()       (SET_BIT(TCCR1B, TCCR1B_ICES1))
#define Select_FallingEdge()      (CLR_BIT(TCCR1B, TCCR1B_ICES1))


void ICU_Init(uint8_t prescaler)
{
    #if IS_AVR()
    Enable_ICU();
    Enable_Noise_Canceler();

    /* Set the prescaler */
    TCCR1B    &= ~(TIMER_CLOCK_MASK);
    prescaler &=  (TIMER_CLOCK_MASK);
    TCCR1B |= prescaler;

    #endif
}
error_t ICU_SelectEdge(uint8_t edge)
{
    error_t kErrorState = kNoError;
    #if IS_AVR()
    if ( ICU_FALLING_EDGE == edge)
    {
        Select_FallingEdge();

    }else if ( ICU_RISING_EDGE == edge )
    {
        Select_RisingEdge();

    }else
    {
        kErrorState = kFunctionParameterError;
    }
    #endif
    return kErrorState;
}


error_t ICU_SetCallBackFunc(void (*pISR_Fun)(void))
{
    error_t kErrorState = kNoError;
    #if IS_AVR()
    if (NULL_PTR != pISR_Fun )
    {
       pICU_CallBackFunction = pISR_Fun;

    }else
    {
        kErrorState = kFunctionParameterError;
    }
    return kErrorState;
}
error_t ICU_ReadCaptureValue(uint16 *pValue)
{
    error_t kErrorState = kNoError;
    if ( NULL_PTR != pValue )
    {
       *pValue = ICR1;

    }else
    {
        kErrorState = kFunctionParameterError;
    }
    #endif
    return kErrorState;
}
void ICU_Disable(void)
{
    #if IS_AVR()
    Disable_ICU();
    Disable_Noise_Canceler();
    #endif
}

/*TIMER1 ICU Mode ISR*/
void __vector_6(void) __attribute__((signal));
void __vector_6(void)
{
    if (pICU_CallBackFunction!=NULL_PTR)
    {
        pICU_CallBackFunction();
    }
}
