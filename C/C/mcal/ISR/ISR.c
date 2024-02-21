#include "Config.h"
#include "Types.h"
#include "Utils.h"
#include "Registes.h"
#include "EXTI_Interface.h"
#include "ADC_interface.h"
#include "ISR.h"

uint16* aSynchResult;
static void (*EXTI_pCallBackFun[3]) (void) = {NULL_PTR};
static void (*ADC_pCallBackFun) (void) = NULL_PTR;

#if IS_PIC()
static volatile INT0Flag=0, INT0IE=0;
static volatile INT1Flag=0, INT1IE=0;
static volatile INT2Flag=0, INT2IE=0;
static volatile ADIF=0, ADIE=0;
#endif

error_t ISR_Init(uint8_t kInterruptSource, void (*pFun)(void))
{
    error_t retErrorState = kNoError;
    if (pFun != NULL_PTR)
    {
        switch (kInterruptSource)
        {
           case EXTI_INT0 : EXTI_pCallBackFun[0] = pFun; break;
           case EXTI_INT1 : EXTI_pCallBackFun[1] = pFun; break;
           case EXTI_INT2 : EXTI_pCallBackFun[2] = pFun; break;
           case ADC_INT   : ADC_pCallBackFun = pFun;     break;
        }
    }
    else
    {
        retErrorState = kFunctionParameterError;
    }
    return retErrorState;
}
#if IS_AVR()
/* ISR Implementation   */
/*ISR OF INT0*/
void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
    if (EXTI_pCallBackFun[0]!=NULL_PTR)
    {
        EXTI_pCallBackFun[0]();
    }
}
/*ISR OF INT1*/
void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
    if (EXTI_pCallBackFun[1]!=NULL_PTR)
    {
        EXTI_pCallBackFun[1]();
    }
}
/*ISR OF INT2*/
void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
    if (EXTI_pCallBackFun[2]!=NULL_PTR)
    {
        EXTI_pCallBackFun[2]();
    }
}
/*ISR OF ADC*/
void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
             #if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
                *aSynchResult = ADCL_REG | (ADCH_REG<<8);

            #elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT
                *aSynchResult = ADCH_REG;

            #else
                kErrorState = kFunctionParameterError;
            #endif
            //ISRfunction();
            CLR_BIT(ADCSRA_REG, ADCSRA_ADIE);
}
#elif IS_PIC()
#if priorityState == ENABLED
void __interrupt(high_priority) ISR_HIGH(void)
{
    INT0Flag = GET_BIT(INTCON_REG, INTCON_INT0IF);
    INT0IE   = GET_BIT(INTCON_REG, INTCON_INT0IE);
    INT1Flag = GET_BIT(INTCON3_REG, INTCON3_INT1IF);
    INT1IE   = GET_BIT(INTCON3_REG, INTCON3_INT1IE);
    INT2Flag = GET_BIT(INTCON3_REG, INTCON3_INT2IF);
    INT2IE   = GET_BIT(INTCON3_REG, INTCON3_INT2IE);
    if (INT0IE == HIGH && INT0Flag == HIGH)
    {
        /*Clear Flag*/
        SET_BIT(INTCON_REG, INTCON_INT0IF);
        /* Do Action*/
        EXTI_pCallBackFun[0]();
    }
    if (INT1IE == HIGH && INT1Flag == HIGH)
    {
        /*Clear Flag*/
        SET_BIT(INTCON3_REG, INTCON3_INT1IF);
        /* Do Action*/
        EXTI_pCallBackFun[1]();
    }
    if (INT2IE == HIGH && INT2Flag == HIGH)
    {
        /*Clear Flag*/
        SET_BIT(INTCON3_REG, INTCON3_INT2IF);
        /* Do Action*/
        EXTI_pCallBackFun[2]();
    }
}
void __interrupt(low_priority) ISR_LOW(void)
{
    INT1Flag = GET_BIT(INTCON3_REG, INTCON3_INT1IF);
    INT1IE   = GET_BIT(INTCON3_REG, INTCON3_INT1IE);
    INT2Flag = GET_BIT(INTCON3_REG, INTCON3_INT2IF);
    INT2IE   = GET_BIT(INTCON3_REG, INTCON3_INT2IE);
    if (INT1IE == HIGH && INT1Flag == HIGH)
    {
        /*Clear Flag*/
        SET_BIT(INTCON3_REG, INTCON3_INT1IF);
        /* Do Action*/
        EXTI_pCallBackFun[1]();
    }
    if (INT2IE == HIGH && INT2Flag == HIGH)
    {
        /*Clear Flag*/
        SET_BIT(INTCON3_REG, INTCON3_INT2IF);
        /* Do Action*/
        EXTI_pCallBackFun[2]();
    }
}
#elif priorityState == DISABLED
void __interrupt() ISR(void)
{
    INT0Flag = GET_BIT(INTCON_REG, INTCON_INT0IF);
    INT0IE   = GET_BIT(INTCON_REG, INTCON_INT0IE);
    INT1Flag = GET_BIT(INTCON3_REG, INTCON3_INT1IF);
    INT1IE   = GET_BIT(INTCON3_REG, INTCON3_INT1IE);
    INT2Flag = GET_BIT(INTCON3_REG, INTCON3_INT2IF);
    INT2IE   = GET_BIT(INTCON3_REG, INTCON3_INT2IE);
    ADIF = GET_BIT(PIR1_REG, PIR1_ADIF);
    ADIE = GET_BIT(PIE1_REG, PIE1_ADIE);
    if (INT0IE == HIGH && INT0Flag == HIGH)
    {
        /*Clear Flag*/
        SET_BIT(INTCON_REG, INTCON_INT0IF);
        /* Do Action*/
        EXTI_pCallBackFun[0]();
    }
    if (INT1IE == HIGH && INT1Flag == HIGH)
    {
        /*Clear Flag*/
        SET_BIT(INTCON3_REG, INTCON3_INT1IF);
        /* Do Action*/
        EXTI_pCallBackFun[1]();
    }
    if (INT2IE == HIGH && INT2Flag == HIGH)
    {
        /*Clear Flag*/
        SET_BIT(INTCON3_REG, INTCON3_INT2IF);
        /* Do Action*/
        EXTI_pCallBackFun[2]();
    }
    if (ADIE == HIGH && ADIF == HIGH)
    {
         #if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
        *aSynchResult = ADRESL_REG | (ADRESH_REG<<8);

        #elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT
            *aSynchResult = (ADRESH_REG>>6) | (ADRESL_REG<<2);
        #else
            kErrorState = kFunctionParameterError;
        #endif
        ADC_pCallBackFun();
        //Disable ADC interrupt
        CLR_BIT(PIE1_REG, PIE1_ADIE);
    }
}
#endif //priorityState
#endif //MCU_TYPE
