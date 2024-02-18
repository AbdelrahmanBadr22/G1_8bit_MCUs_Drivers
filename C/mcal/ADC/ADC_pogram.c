#include "../../common/Config.h"
#include "../../common/Types.h"
#include "../../common/Utils.h"
#include "../../common/Registes.h"
#include "../ISR/ISR.h"
#include "ADC_config.h"
#include "ADC_interface.h"

static uint16* aSynchResult;
//-----------------------------------------------------------------------------
//                           HELPER FUNCTIONS
//-----------------------------------------------------------------------------
#if IS_AVR()
static void ADC_AVR_CONFIG_HELPER()
{
     /* Select ADC Voltage Reference */
    #if ADC_VREF == ADC_AREF
        CLR_BIT(ADMUX_REG, ADMUX_REFS0);
        CLR_BIT(ADMUX_REG, ADMUX_REFS1);
    #elif ADC_VREF == ADC_AVCC
        SET_BIT(ADMUX_REG, ADMUX_REFS0);
        CLR_BIT(ADMUX_REG, ADMUX_REFS1);
    #elif ADC_VREF == ADC_INTERNAL_2_56
        SET_BIT(ADMUX_REG, ADMUX_REFS0);
        SET_BIT(ADMUX_REG, ADMUX_REFS1);
    #endif //ADC_VREF == ADC_AREF

    /* Select ADC Right/Left Adjust */
    #if ADC_ADJUSTMENT == LEFT_ADJUSTMENT
        SET_BIT(ADMUX_REG, ADMUX_ADLAR);
    #elif ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
        CLR_BIT(ADMUX_REG, ADMUX_ADLAR);
    #endif //ADC_ADJUSTMENT == LEFT_ADJUSTMENT
}
#elif IS_PIC()
static void ADC_PIC_CONFIG_HELPER()
{
    /* Select ADC Voltage Reference */
    #if AVR_VREF == ADC_EXT_REF
      #if ADC_SUP == ADC_NEGATIVE_SUP
        SET_BIT(ADCON1_REG, ADCON1_VFG1);
      #elif ADC_SUP == ADC_POSITIVE_SUP
        SET_BIT(ADCON1_REG, ADCON1_VFG0);
      #endif //ADC_SUP == ADC_NEGATIVE_SUP
    #elif AVR_VREF == ADC_INT_REF
      #if ADC_SUP == ADC_NEGATIVE_SUP
        CLR_BIT(ADCON1_REG, ADCON1_VFG1);
      #elif ADC_SUP == ADC_POSITIVE_SUP
        CLR_BIT(ADCON1_REG, ADCON1_VFG0);
      #endif //ADC_SUP == ADC_NEGATIVE_SUP
    #endif //AVR_VREF == ADC_EXT_REF

    /* Select ADC Right/Left Adjust */
    #if ADC_ADJUSTMENT == LEFT_ADJUSTMENT
    CLR_BIT(ADCON2_REG, ADCON2_ADFM);
      #elif ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
      SET_BIT(ADCON2_REG, ADCON2_ADFM);
        #endif //ADC_ADJUSTMENT == LEFT_ADJUSTMENT
}
#endif //IS_AVR()
//-----------------------------------------------------------------------------
//                             ADC FUNCTIONS
//-----------------------------------------------------------------------------
void ADC_Init (void)
{
    #if IS_AVR()
    ADC_AVR_CONFIG_HELPER();
    #elif IS_PIC()
    ADC_PIC_CONFIG_HELPER();
    #endif //IS AVR()
    /* Select Prescaler */
    ADC_PRESCALER_REG  &= ADC_PRE_MASK;
    ADC_PRESCALER_REG  |= ADC_PRESCALER;
}

void ADC_ENABLE(void)
{
    #if  IS_AVR()
    SET_BIT(ADCSRA_REG, ADCSRA_ADEN);
    #elif IS_PIC()
    SET_BIT(ADCON0_REG, ADCON0_ADON);
    #endif // IS_AVR()
}

void ADC_DISABLE(void)
{
    #if IS_AVR()
    CLR_BIT(ADCSRA_REG, ADCSRA_ADEN);
    #elif IS_PIC()
    CLR_BIT(ADCON0_REG, ADCON0_ADON);
    #endif // IS_AVR()
}

void ADC_INTERRUPT_ENABLE(void)
{
    #if IS_AVR()
    SET_BIT(ADCSRA_REG, ADCSRA_ADIE);
    #elif IS_PIC()
    SET_BIT(PIE1_REG, PIE1_ADIE);
    #endif // IS_AVR()
}

void ADC_INTERRUPT_DISABLE(void)
{
    #if IS_AVR()
    CLR_BIT(ADCSRA_REG, ADCSRA_ADIE);
    #elif IS_PIC()
    CLR_BIT(PIE1_REG, PIE1_ADIE);
    #endif // IS_AVR()
}

error_t  ADC_Prescaler (uint8_t prescalerVal)
{
    error_t kErrorState = kNoError;
    if (prescalerVal<ADC_PRESCALER_128)
    {
        #if IS_AVR()
        ADCSRA_REG&=ADC_PRE_MASK;
        ADCSRA_REG|=prescalerVal;
        #elif IS_PIC()
        ADCON2_REG &= ADC_PRE_MASK;
        ADCON2_REG |= prescalerVal;
        #endif // IS_AVR()
    }
    else
    {
        kErrorState = kFunctionParameterError;
    }
    return kErrorState;
}
error_t ADC_GetResultSynch(uint8_t channel, uint16* result)
{
    error_t kErrorState = kNoError;
    if (result!=NULL)
    {
        #if IS_AVR()
        /* Select Channel */
        ADMUX_REG &=ADC_CH_MASK;
        ADMUX_REG |=channel;

        /* Start Conversion */
        SET_BIT(ADCSRA_REG, ADCSRA_ADSC);

        uint8_t timer=0;
        while ((GET_BIT(ADCSRA_REG, ADCSRA_ADIF)==0)&&(timer<TIMEOUT))
        {
            timer++;
        }
        if (timer==TIMEOUT)
        {
            kErrorState =kTimeoutError;
        }
        else
        {
            /* Clear ADC Interrupt Flag */
            SET_BIT(ADCSRA_REG, ADCSRA_ADIF);

            #if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
                *result = ADCL_REG | (ADCH_REG<<8);

            #elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT
                *result = (ADCL_REG>>6) | (ADCH_REG<<2);

            #else
                kErrorState = kFunctionParameterError;
            #endif
        }
        #elif IS_PIC()
        /* Select Channel */
        ADCON0_REG &= 0b11000011;
        ADCON0_REG |= channel;

        /* Start Conversion */
        SET_BIT(ADCON0_REG, ADCON0_GODONE);

        while ((GET_BIT(ADCON0_REG, ADCON0_GODONE) == 1)
            && (GET_BIT(PIR1_REG, PIR1_ADIF) == 0))
        {

        }
        /* Clear ADC Interrupt Flag */
        CLR_BIT(PIR1_REG, PIR1_ADIF);

        #if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
            *result = ADRESL_REG | (ADRESH_REG<<8);

        #elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT
            *result = (ADRESH_REG>>6) | (ADRESL_REG<<2);

        #else
            kErrorState = kFunctionParameterError;
        #endif
        #endif // IS_AVR()
    }
    else
    {
        kErrorState = kFunctionParameterError;
    }
    return kErrorState;
}
error_t ADC_StartConvASynch(uint8_t channel, uint16* result,
                            void (*function)(void))
{
    error_t kErrorState = kNoError;
    if (result!=NULL)
    {
        #if IS_AVR()
        aSynchResult=result;
        ISR_Init(ADC_INT, function);
        ADMUX_REG &=ADC_CH_MASK;
        ADMUX_REG =channel;
        SET_BIT(ADCSRA_REG, ADCSRA_ADSC);
        ADC_INTERRUPT_ENABLE();
        #elif IS_PIC()
        aSynchResult = result;
        ISR_Init(ADC_INT, function);
        ADCON0_REG &= 0b11000011;
        ADCON0_REG |= channel;
        /* Start Conversion */
        SET_BIT(ADCON0_REG, ADCON0_GODONE);
        /*Enable Interrupt*/
        //Clear ADC interrupt flag
        CLR_BIT(PIR1_REG, PIR1_ADIF);
        //Enable ADC interrupt
        SET_BIT(PIE1_REG, PIE1_ADIE);
        /*Disable priority*/
        CLR_BIT(RCON_REG, RCON_IPEN);
        //Enable peripheral interrupt
        SET_BIT(INTCON_REG, INTCON_PEIE);
        //Enable global interrupt
        SET_BIT(INTCON_REG, INTCON_GIE);
        #endif // IS_AVR()
    }
    else
    {
        kErrorState = kFunctionParameterError;
    }
    return kErrorState;
}
