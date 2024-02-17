/*
 * TIMER_Program.c
 *
 *  Created on: Oct 26, 2023
 *      Author: Mohamed Refat
 */

#ifndef MCAL_TIMER_TIMER_PROGRAM_C_
#define MCAL_TIMER_TIMER_PROGRAM_C_


#include "../../common/Config.h"
#include "../../common/Registes.h"
#include "../../common/Types.h"
#include "../../common/Utils.h"

#include "../../mcal/GPIO/GPIO.h"
#include "TIMER_Interface.h"
#include "TIMER_Private.h"

void(*pOVF_CallBackFunctions[3])(void) = {NULL_PTR};
void(*pCTC_CallBackFunctions[4])(void) = {NULL_PTR};
void(*pICU_CallBackFunction)(void) = NULL_PTR;


error_t TIMER0_Init(uint8_t kMode, uint8_t kClock)
{
    error_t kErrorState = kNoError;

    #if MCU_TYPE == _AVR
    /* Set Timer0 Mode */
    switch (kMode)
    {
        case TIMER_NORMAL_MODE:
            CLR_BIT(TCCR0, TCCR0_WGM00);
            CLR_BIT(TCCR0, TCCR0_WGM01);
            break;

        case TIMER_CTC_MODE:
            CLR_BIT(TCCR0, TCCR0_WGM00);
            SET_BIT(TCCR0, TCCR0_WGM01);
            break;

        case TIMER_PWM_MODE:
            /* Set Timer Mode To Fast PWM */
            SET_BIT(TCCR0, TCCR0_WGM00);
            SET_BIT(TCCR0, TCCR0_WGM01);
            /* Set PWM Output To Inverting
                Clear on Top Set On Compare
            */
            SET_BIT(TCCR0, TCCR0_COMM00);
            SET_BIT(TCCR0, TCCR0_COMM01);
            break;
        default: kErrorState = kFunctionParameterError;
    }
    /* Set Timer0 Clock Source */
    TCCR0 &= ~(TIMER_CLOCK_MASK);
    kClock &= (TIMER_CLOCK_MASK);
    TCCR0 |= kClock;

    /* Enable Timer0 Overflow Interrupt */
    SET_BIT(TIMSK, TIMSK_TOIE0);
    /* Enable Timer0 CTC  Interrupt */
    SET_BIT(TIMSK, TIMSK_OCIE0);

    #endif
    return kErrorState;
}

void TIMER0_SetPreload(uint8_t preloadValue)
{
    #if MCU_TYPE == _AVR
    TCNT0 = preloadValue;
    #endif
}

void TIMER0_SetCTC(uint8_t kOCR_Value)      //IGNORE-STYLE-CHECK[B004]
{
    #if MCU_TYPE == _AVR
    OCR0 = kOCR_Value;
    #endif
}

error_t TIMER0_SetOCPinMode(uint8_t kOCPinMode)
{
    error_t kErrorState = kNoError;
    #if MCU_TYPE == _AVR
    switch (kOCPinMode)
    {
        case TIMER_OC_TURN_OFF:
            CLR_BIT(TCCR0, TCCR0_COMM00);
            CLR_BIT(TCCR0, TCCR0_COMM01);
            break;

        case TIMER_OC_TOGGLE:
            SET_BIT(TCCR0, TCCR0_COMM00);
            CLR_BIT(TCCR0, TCCR0_COMM01);
            break;

        case TIMER_OC_CLEAR:
            CLR_BIT(TCCR0, TCCR0_COMM00);
            SET_BIT(TCCR0, TCCR0_COMM01);
            break;

        case TIMER_OC_SET:
            CLR_BIT(TCCR0, TCCR0_COMM00);
            SET_BIT(TCCR0, TCCR0_COMM01);
            break;
    }
    #endif
    return kErrorState;
}

error_t TIMER0_SetDutyCycle(uint8_t dutyCycle)
{
    error_t kErrorState = kNoError;
    #if MCU_TYPE == _AVR
    if (dutyCycle <= 100)
    {
        uint8_t kOCRValue;
        kOCRValue = RESOLUTION_8BIT -((dutyCycle/100.0) * RESOLUTION_8BIT);
        OCR0 = kOCRValue;
    }else
    {
        kErrorState = kFunctionParameterError;
    }
    #endif
    return kErrorState;
}

error_t TIMER0_SetCallBackFun(uint8_t interruptSource,
                                                void (*pTimer_ISR)(void))
{
    error_t kErrorState = kNoError;
    #if MCU_TYPE == _AVR
    if ( pTimer_ISR != NULL_PTR )
    {

        switch (interruptSource)
        {
            case TIMER0_INTERRUPT_OVERFLOW :
                pOVF_CallBackFunctions[0] = pTimer_ISR;
                break;

            case TIMER0_INTERRUPT_CTC :
                pCTC_CallBackFunctions[0] = pTimer_ISR;
                break;

            default: kErrorState = kFunctionParameterError;
        }

    }else
    {
        kErrorState = kFunctionParameterError;
    }
    #endif
    return kErrorState;
}

void TIMER0_SetPreScalar() 
{
    #if IS_AVR()
    // Set 64 as pre
    CLR_BIT(TCCR0, TCCR0_CS02);
    SET_BIT(TCCR0, TCCR0_CS01);
    SET_BIT(TCCR0, TCCR0_CS00);
    #endif // IS_AVR
}
error_t TIMER1_Init(uint8_t kMode, uint8_t kClock)
{
    error_t kErrorState = kNoError;
    #if MCU_TYPE == _AVR
    /* Set Timer0 Mode */
    switch (kMode)
    {
        case TIMER_NORMAL_MODE:
            CLR_BIT(TCCR1A, TCCR1A_WGM10);
            CLR_BIT(TCCR1A, TCCR1A_WGM11);
            CLR_BIT(TCCR1B, TCCR1B_WGM12);
            CLR_BIT(TCCR1B, TCCR1B_WGM13);
            break;

        case TIMER_CTC_MODE:
            CLR_BIT(TCCR1A, TCCR1A_WGM10);
            CLR_BIT(TCCR1A, TCCR1A_WGM11);
            SET_BIT(TCCR1B, TCCR1B_WGM12);
            CLR_BIT(TCCR1B, TCCR1B_WGM13);
            break;

        case TIMER_PWM_MODE:
            /* Set Timer Mode To Fast PWM and the top value is ICR1 */
            CLR_BIT(TCCR1A, TCCR1A_WGM10);
            SET_BIT(TCCR1A, TCCR1A_WGM11);
            SET_BIT(TCCR1B, TCCR1B_WGM12);
            SET_BIT(TCCR1B, TCCR1B_WGM13);

        default: kErrorState = kFunctionParameterError;
    }

    /* Set Timer1 Clock Source */
    TCCR1B &= ~(TIMER_CLOCK_MASK);
    kClock &= (TIMER_CLOCK_MASK);
    TCCR1B |= kClock;

    /* Enable Timer1 Overflow Interrupt */
    SET_BIT(TIMSK, TIMSK_TOIE1);
    /* Enable Timer1 CTC A Interrupt */
    SET_BIT(TIMSK, TIMSK_OCIE1A);
    /* Enable Timer1 CTC B Interrupt */
    SET_BIT(TIMSK, TIMSK_OCIE1B);
    /* Enable Timer1 Input Capture Interrupt */
    SET_BIT(TIMSK, TIMSK_ICIE1);

    #endif
    return kErrorState;
}

void TIMER1_SetPreload(uint16  preloadValue)
{
    #if MCU_TYPE == _AVR
    TCNT1 = preloadValue;
    #endif
}

void TIMER1_SetCTCA(uint16 kOCRA_Value)
{
    #if MCU_TYPE == _AVR
    OCR1A = kOCRA_Value;
    #endif
}

void TIMER1_SetCTCB(uint16 kOCRB_Value)
{
    #if MCU_TYPE == _AVR
    OCR1B = kOCRB_Value;
    #endif
}

error_t TIMER1_SetOCAPinMode(uint8_t kOCPinMode)
{
    error_t kErrorState = kNoError;
    #if MCU_TYPE == _AVR
    switch (kOCPinMode)
    {
        case TIMER_OC_TURN_OFF:
            CLR_BIT(TCCR1A, TCCR1A_COM1A0);
            CLR_BIT(TCCR1A, TCCR1A_COM1A1);
            break;
        case TIMER_OC_TOGGLE:
            SET_BIT(TCCR1A, TCCR1A_COM1A0);
            CLR_BIT(TCCR1A, TCCR1A_COM1A1);
            break;
        case TIMER_OC_CLEAR:
            CLR_BIT(TCCR1A, TCCR1A_COM1A0);
            SET_BIT(TCCR1A, TCCR1A_COM1A1);
            break;
        case TIMER_OC_SET:
            CLR_BIT(TCCR1A, TCCR1A_COM1A0);
            SET_BIT(TCCR1A, TCCR1A_COM1A1);
            break;
    }
    #endif
    return kErrorState;
}

error_t TIMER1_SetOCBPinMode(uint8_t kOCPinMode)
{
    error_t kErrorState = kNoError;
    #if MCU_TYPE == _AVR
    switch (kOCPinMode)
    {
        case TIMER_OC_TURN_OFF:
            CLR_BIT(TCCR1A, TCCR1A_COM1B0);
            CLR_BIT(TCCR1A, TCCR1A_COM1B1);
            break;
        case TIMER_OC_TOGGLE:
            SET_BIT(TCCR1A, TCCR1A_COM1B0);
            CLR_BIT(TCCR1A, TCCR1A_COM1B1);
            break;
        case TIMER_OC_CLEAR:
            CLR_BIT(TCCR1A, TCCR1A_COM1B0);
            SET_BIT(TCCR1A, TCCR1A_COM1B1);
            break;
        case TIMER_OC_SET:
            CLR_BIT(TCCR1A, TCCR1A_COM1B0);
            SET_BIT(TCCR1A, TCCR1A_COM1B1);
            break;
    }
    #endif
    return kErrorState;
}

error_t TIMER1_SetPWM_Channel_Mode(uint8_t kChannel, uint8_t kMode)
{
    error_t kErrorState = kNoError;
    #if MCU_TYPE == _AVR
    if ( kChannel == PWM1_OC1A )
    {
        GPIO_SetPinDirection(kPORTD, kPIN5, kOutput);
        switch (kMode)
        {
            case PWM1_INVERTING:
                SET_BIT(TCCR1A, TCCR1A_COM1A0);
                SET_BIT(TCCR1A, TCCR1A_COM1A1);
                break;
            case PWM1_NON_INVERTING:
                CLR_BIT(TCCR1A, TCCR1A_COM1A0);
                SET_BIT(TCCR1A, TCCR1A_COM1A1);
                break;
            default: kErrorState = kFunctionParameterError;
        }
    }else if ( kChannel == PWM1_OC1B)
    {
        GPIO_SetPinDirection(kPORTD, kPIN4, kOutput);
        switch (kMode)
        {
            case PWM1_INVERTING:
                SET_BIT(TCCR1A, TCCR1A_COM1B0);
                SET_BIT(TCCR1A, TCCR1A_COM1B1);
                break;
            case PWM1_NON_INVERTING:
                CLR_BIT(TCCR1A, TCCR1A_COM1B0);
                SET_BIT(TCCR1A, TCCR1A_COM1B1);
                break;
            default: kErrorState = kFunctionParameterError;
        }
    }else
    {
    	kErrorState = kFunctionParameterError;
    }
    #endif
    return kErrorState;
}
error_t TIMER1_SetPWM_Freq(uint32_t frequency, uint32_t kPrescaler)
{
    error_t kErrorState = kNoError;
    #if MCU_TYPE == _AVR
    if ( frequency <= CPU_FREQ )
    {
            /**
             * F_PWM = CPU_FREQ/(Prescaler * (1 + TOP ))
             * TOP = ICR1
             */
            ICR1 = ( ( CPU_FREQ ) / ( kPrescaler * frequency ) ) - 1;
    }else
    {
        kErrorState = kFunctionParameterError;
    }
    #endif
    return kErrorState;
}
error_t TIMER1_SetDutyCycle(f32_t dutyCycle, uint8_t kChannel)
{
    error_t kErrorState = kNoError;
    #if MCU_TYPE == _AVR
    if (dutyCycle <= 100 )
    {
        /* ICR1 --> Top value of timer1 */
        uint16 iOCRValue =  ICR1 -((dutyCycle/100.0) * ICR1);
        if (kChannel == PWM1_OC1A)
        {
            OCR1A = iOCRValue;
        }else if (kChannel == PWM1_OC1B)
        {
            OCR1B = iOCRValue;
        }else
        {
            kErrorState = kFunctionParameterError;
        }
    }else
    {
        kErrorState = kFunctionParameterError;
    }
    #endif
    return kErrorState;
}

error_t TIMER1_SetCallBackFun(uint8_t interruptSource,
                                            void (*pTimer_ISR)(void))
{
    error_t kErrorState = kNoError;
    #if MCU_TYPE == _AVR
    if ( pTimer_ISR != NULL_PTR )
    {

        switch (interruptSource)
        {
            case TIMER1_INTERRUPT_OVERFLOW :
                pOVF_CallBackFunctions[1] = pTimer_ISR;
                break;

            case TIMER1_INTERRUPT_CTCA :
                pCTC_CallBackFunctions[1] = pTimer_ISR;
                break;

            case TIMER1_INTERRUPT_CTCB :
                pCTC_CallBackFunctions[3] = pTimer_ISR;
                break;

            case TIMER1_INTERRUPT_ICU1 :
                pICU_CallBackFunction = pTimer_ISR;
                break;

            default: kErrorState = kFunctionParameterError;
        }

    }else
    {
        kErrorState = kFunctionParameterError;
    }
    #endif
    return kErrorState;
}


error_t TIMER2_Init(uint8_t kMode, uint8_t kClock)
{
    error_t kErrorState = kNoError;
    #if MCU_TYPE == _AVR
    /* Set Timer2 Mode */
    switch (kMode)
    {
        case TIMER_NORMAL_MODE:
            CLR_BIT(TCCR2, TCCR2_WGM20);
            CLR_BIT(TCCR2, TCCR2_WGM21);
            break;
        case TIMER_CTC_MODE:
            CLR_BIT(TCCR2, TCCR2_WGM20);
            SET_BIT(TCCR2, TCCR2_WGM21);
            break;
        case TIMER_PWM_MODE:
            /* Set Timer Mode To Fast PWM */
            SET_BIT(TCCR2, TCCR2_WGM20);
            SET_BIT(TCCR2, TCCR2_WGM21);
            /* Set PWM Output To Inverting
                Clear on Top Set On Compare
            */
            SET_BIT(TCCR2, TCCR2_COMM20);
            SET_BIT(TCCR2, TCCR2_COMM21);
            break;
        default: kErrorState = kFunctionParameterError;
    }

    /* Set Timer2 Clock Source */
    TCCR2 &= ~(TIMER_CLOCK_MASK);
    kClock &= (TIMER_CLOCK_MASK);
    TCCR2 |= kClock;

    /* Enable Timer2 Overflow Interrupt */
    SET_BIT(TIMSK, TIMSK_TOIE2);
    /* Enable Timer2 CTC  Interrupt */
    SET_BIT(TIMSK, TIMSK_OCIE2);

    #endif
    return kErrorState;

}

void TIMER2_SetPreload(uint8_t preloadValue)
{
    #if MCU_TYPE == _AVR
    TCNT2 = preloadValue;
    #endif
}

void TIMER2_SetCTC(uint8_t kOCR_Value) //IGNORE-STYLE-CHECK[B004]
{
    #if MCU_TYPE == _AVR
    OCR2 = kOCR_Value;
    #endif
}

error_t TIMER2_SetOCPinMode(uint8_t kOCPinMode)
{
    error_t kErrorState = kNoError;
    #if MCU_TYPE == _AVR
    switch (kOCPinMode)
    {
        case TIMER_OC_TURN_OFF:
            CLR_BIT(TCCR2, TCCR2_COMM20);
            CLR_BIT(TCCR2, TCCR2_COMM21);
            break;
        case TIMER_OC_TOGGLE:
            SET_BIT(TCCR2, TCCR2_COMM20);
            CLR_BIT(TCCR2, TCCR2_COMM21);
            break;
        case TIMER_OC_CLEAR:
            CLR_BIT(TCCR2, TCCR2_COMM20);
            SET_BIT(TCCR2, TCCR2_COMM21);
            break;
        case TIMER_OC_SET:
            CLR_BIT(TCCR2, TCCR2_COMM20);
            SET_BIT(TCCR2, TCCR2_COMM21);
            break;
    }
    #endif
    return kErrorState;
}

error_t TIMER2_SetDutyCycle(uint8_t dutyCycle)
{
    error_t kErrorState = kNoError;
    #if MCU_TYPE == _AVR
    if (dutyCycle <= 100)
    {
        uint8_t kOCRValue;
        kOCRValue = RESOLUTION_8BIT -((dutyCycle/100.0) * RESOLUTION_8BIT);
        OCR2 = kOCRValue;
    }else
    {
        kErrorState = kFunctionParameterError;
    }
    #endif
    return kErrorState;
}


error_t TIMER2_SetCallBackFun(uint8_t interruptSource,
                                        void (*pTimer_ISR)(void))
{
    error_t kErrorState = kNoError;
    #if MCU_TYPE == _AVR
    if ( pTimer_ISR != NULL_PTR )
    {

        switch (interruptSource)
        {
            case TIMER2_INTERRUPT_OVERFLOW :
                pOVF_CallBackFunctions[2] = pTimer_ISR;
                break;

            case TIMER2_INTERRUPT_CTC :
                pCTC_CallBackFunctions[2] = pTimer_ISR;
                break;

            default: kErrorState = kFunctionParameterError;
        }

    }else
    {
        kErrorState = kFunctionParameterError;
    }
    #endif
    return kErrorState;
}


/*TIMER0 Normal Mode ISR*/
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
    if (pOVF_CallBackFunctions[0]!=NULL_PTR)
    {
        pOVF_CallBackFunctions[0]();
    }
}
/*TIMER0 CTC  Mode ISR*/
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
    if (pCTC_CallBackFunctions[0]!=NULL_PTR)
    {
        pCTC_CallBackFunctions[0]();
    }
}


/*TIMER1 Normal Mode ISR*/
void __vector_9(void) __attribute__((signal));
void __vector_9(void)
{
    if (pOVF_CallBackFunctions[1]!=NULL_PTR)
    {
        pOVF_CallBackFunctions[1]();
    }
}
/*TIMER1 CTC A Mode ISR*/
void __vector_7(void) __attribute__((signal));
void __vector_7(void)
{
    if (pCTC_CallBackFunctions[1]!=NULL_PTR)
    {
        pCTC_CallBackFunctions[1]();
    }
}
/*TIMER1 CTC B Mode ISR*/
void __vector_8(void) __attribute__((signal));
void __vector_8(void)
{
    if (pCTC_CallBackFunctions[3]!=NULL_PTR)
    {
        pCTC_CallBackFunctions[3]();
    }
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

/*TIMER2 Normal Mode ISR*/
void __vector_5(void) __attribute__((signal));
void __vector_5(void)
{
    if (pOVF_CallBackFunctions[2]!=NULL_PTR)
    {
        pOVF_CallBackFunctions[2]();
    }
}

/*TIMER2 CTC Mode ISR*/
void __vector_4(void) __attribute__((signal));
void __vector_4(void)
{
    if (pCTC_CallBackFunctions[2]!=NULL_PTR)
    {
        pCTC_CallBackFunctions[2]();
    }
}

#endif /* MCAL_TIMER_TIMER_PROGRAM_C_ */
