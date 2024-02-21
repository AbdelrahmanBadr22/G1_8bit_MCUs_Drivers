#ifndef MCAL_ADC_CONFIG_H_
#define MCAL_ADC_CINFIG_H_

/* Options:
            ADC_AVCC  --> internal Voltage reference
                (connect AVCC pin to the Vcc same as the controller)

            ADC_AREF  --> External Voltage reference
                (connect ADC_AREF pin to the Vcc[0 , 5v])
                
            ADC_INTERNAL_2_56 --> internal voltage
 */
#define ADC_VREF (ADC_AVCC)
/* Options:
            ADC_POSITIVE_SUP
            ADC_NEGATIVE_SUP
*/
#if MCU_TYPE == _PIC
#define ADC_SUP (ADC_NEGATIVE_SUP)
#endif
/* Options:
            LEFT_ADJUSTMENT
            RIGHT_ADJUSTMENT
            
 */
#define ADC_ADJUSTMENT (RIGHT_ADJUSTMENT)

/* Options:
            ADC_PRESCALER_2
            ADC_PRESCALER_4
            ADC_PRESCALER_8
            ADC_PRESCALER_16
            ADC_PRESCALER_32
            ADC_PRESCALER_64
            if MCU_TYPE == _AVR
            ADC_PRESCALER_128
 */
#define ADC_PRESCALER (ADC_PRESCALER_128)

#define TIMEOUT (5000)

#endif /* MCAL_ADC_CONFIG_H_ */
