#ifndef MCAL_ADC_INTERFACE_H_
#define MCAL_ADC_INTERFACE_H_

#define ADC_AREF            (0)
#define ADC_AVCC            (1)

#define RIGHT_ADJUSTMENT    (0)
#define LEFT_ADJUSTMENT     (1)

#define ADC_EXT_REF         (0)
#define ADC_INT_REF         (1)
#define ADC_INTERNAL_2_56   (3)

#define ADC_POSITIVE_REF    (0)
#define ADC_NEGATIVE_REF    (1)


#define ADMUX_REFS1     (7)
#define ADMUX_REFS0     (6)
#define ADMUX_ADLAR     (5)
#define ADCSRA_ADIE     (3)
#define ADCSRA_ADIF     (4)
#define ADCSRA_ADSC     (6)
#define ADCSRA_ADEN     (7)

#define ADCON2_ADFM     (7)
#define PIE1_ADIE       (6)
#define PIR1_ADIF       (6)
#define ADCON1_VFG1     (5)
#define ADCON1_VFG0     (4)

#define ADCON0_ADON     (0)
#define ADCON0_GODONE   (1)
#define ADCON0_CHS0     (2)
#define ADCON0_CHS1     (3)
#define ADCON0_CHS2     (4)
#define ADCON0_CHS3     (5)

#define ADC_PRE_MASK (0b1111000)
#define ADC_CH_MASK (0b1110000)

#define ADC_PRESCALER_2    (1)
#define ADC_PRESCALER_4    (2)
#define ADC_PRESCALER_8    (3)
#define ADC_PRESCALER_16   (4)
#define ADC_PRESCALER_32   (5)
#define ADC_PRESCALER_64   (6)
#define ADC_PRESCALER_128  (7)

#define RCON_IPEN           (7)
#define INTCON_PEIE         (6)
#define INTCON_GIE          (7)

#if IS_AVR()
#define ADC_PRESCALER_REG   (ADCSRA_REG)
#elif IS_PIC()
#define ADC_PRESCALER_REG   (ADCON2_REG)
#endif //IS_AVR()
typedef enum
{
    ADC_CHANNEL0,
    ADC_CHANNEL1,
    ADC_CHANNEL2,
    ADC_CHANNEL3,
    ADC_CHANNEL4,
    ADC_CHANNEL5,
    ADC_CHANNEL6,
    ADC_CHANNEL7,
    #if IS_PIC()
    ADC_CHANNEL8,
    ADC_CHANNEL9,
    ADC_CHANNEL10,
    ADC_CHANNEL11,
    ADC_CHANNEL12
    #endif
}ADC_Channel_t;


void ADC_Init(void);
void ADC_ENABLE(void);
void ADC_DISABLE(void);
void ADC_INTERRUPT_ENABLE(void);
void ADC_INTERRUPT_DISABLE(void);
error_t ADC_Prescaler (uint8_t prescalerVal);
error_t ADC_GetResultSynch(uint8_t channel, uint16* result);
error_t ADC_StartConvASynch(uint8_t channel, uint16* result,
                                void (*function)(void));
#endif /* MCAL_ADC_INTERFACE_H_ */
