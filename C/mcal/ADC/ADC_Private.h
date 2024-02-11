#ifndef MCAL_ADC_PRIVATE_H_
#define MCAL_ADC_PRIVATE_H_


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
#endif
