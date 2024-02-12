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


#include "TIMER_Interface.h"
#include "TIMER_Private.h"

void(*pOVF_CallBackFunctions[3])(void) = {NULL_PTR};
void(*pCTC_CallBackFunctions[4])(void) = {NULL_PTR};
void(*pICU_CallBackFunction)(void) = NULL_PTR;
/*PIC*/
static uint16 preload_value = 0;
static void ( * Interrupt_Action) (void)=NULL_PTR;

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

    #elif MCU_TYPE == _PIC
    /*Display Timer0*/
    CLR_BIT(T0CON_REG, TIMER0_TMR0ON);

    /*Configure Prescaler*/
    #if TIMER0_PRESCALER_SET == ENABLED
        CLR_BIT(T0CON_REG, TIMER0_PSA);
        T0CON_REG &=TIMER0_PRESCALER_MASK;
        T0CON_REG |=TIMER0_PRESCALER_VALUE;
    #elif TIMER0_PRESCALER_SET == DISABLED
        SET_BIT(T0CON_REG, TIMER0_PSA);
    #endif

    /*Configure Timer Mode */
    #if TIMER0_MODE == TIMER_MODE
        CLR_BIT(T0CON_REG, TIMER0_T0CS);
    #elif TIMER0_MODE == COUNTER_MODE
        SET_BIT(T0CON_REG, TIMER0_T0CS);
        #if TIMER0_COUNTER_EDGE == RAISING_EDGE
            CLR_BIT(T0CON_REG, TIMER0_T0SE);
        #elif TIMER0_COUNTER_EDGE == FALING_EDGE
            SET_BIT(T0CON_REG, TIMER0_T0SE);
        #else
            kErrorState = kFunctionParameterError;
        #endif
    #else
        kErrorState = kFunctionParameterError;
    #endif

    /*Configure TIMER0 Register Size*/
    #if TIMER0_REG_SIZE == TIMER_8BIT
        SET_BIT(T0CON_REG, TIMER0_T08BIT);
    #elif TIMER0_REG_SIZE == TIMER_16BIT
        CLR_BIT(T0CON_REG, TIMER0_T08BIT);
    #endif

    TMR0L_REG = 0;
    TMR0H_REG = 0;

    #if TIMER0_INTERRUPT == ENABLED
        SET_BIT(INTCON_REG, INTCON_TMR0IE);
        CLR_BIT(INTCON_REG, INTCON_TMR0IF);
        GIC_voidGlobalInterruptControl(GLOBAL_INTERRUPT_ENABLE);
        SET_BIT(INTCON_REG, INTCON_PEIE);
    #elif TIMER0_INTERRUPT == DISABLED

    #endif

    /*Display Timer0*/
    SET_BIT(T0CON_REG, TIMER0_TMR0ON);
    #endif
    return kErrorState;
}

void TIMER0_SetPreload(uint8_t preloadValue)
{
    #if MCU_TYPE == _AVR
    TCNT0 = preloadValue;
    #elif MCU_TYPE == _PIC
    TMR0L_REG = preloadValue;
    TMR0H_REG = (preloadValue>>8);
    preload_value = preloadValue;
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
#if MCU_TYPE == _PIC
error_t TIMER0_Handle_ISR(void ( * pFunction) (void))
{
    error_t retErrorState = kNoError;
    if (pFunction != NULL_PTR)
    {
        Interrupt_Action = pFunction;
    }
    else
    {
        retErrorState = kFunctionParameterError;
    }
    return retErrorState;
}
void TIMER0_WriteValue(uint16 value)
{
    TMR0L_REG = (uint8_t)value;
    TMR0H_REG = (value >> 8);
}
error_t TIMER0_ReadValue(uint16 * value)
{
    error_t retErrorState = kNoError;
    if (value != NULL_PTR)
    {
        *value = (uint16)(TMR0L_REG + (TMR0H_REG << 8));
    }
    else
    {
        retErrorState = kFunctionParameterError;
    }
    return retErrorState;
}
#endif
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
            /* Set Timer Mode To Fast PWM 10 bit*/
            SET_BIT(TCCR1A, TCCR1A_WGM10);
            SET_BIT(TCCR1A, TCCR1A_WGM11);
            SET_BIT(TCCR1B, TCCR1B_WGM12);
            CLR_BIT(TCCR1B, TCCR1B_WGM13);
            /* Set PWM Output To Inverting
                Clear on Top Set On Compare
            */
            SET_BIT(TCCR1A, TCCR1A_COM1A0);
            SET_BIT(TCCR1A, TCCR1A_COM1A1);
            break;
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

error_t TIMER1_SetDutyCycle(uint8_t dutyCycle)
{
    error_t kErrorState = kNoError;
    #if MCU_TYPE == _AVR
    if (dutyCycle <= 100)
    {
        uint16 kOCRValue;
        kOCRValue = RESOLUTION_10BIT -((dutyCycle/100.0) * RESOLUTION_10BIT);
        OCR1A = kOCRValue;
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
/*#if MCU_TYPE == _PIC
void __interrupt() ISR(void)
{
    if (INTCON_TMR0IF)
    {
        CLR_BIT(INTCON_REG, INTCON_TMR0IF);
        TMR0L_REG = (uint8_t)preload_value;
        TMR0H_REG = (preload_value>>8);
        Interrupt_Action();
    }
}
#endif*/
#endif /* MCAL_TIMER_TIMER_PROGRAM_C_ */
