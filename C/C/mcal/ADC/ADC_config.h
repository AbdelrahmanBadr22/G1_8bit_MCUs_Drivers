#ifndef MCAL_ADC_CONFIG_H_
#define MCAL_ADC_CINFIG_H_

/* FOR AVR:
    Options:
            ADC_AVCC  --> internal Voltage reference
                (connect AVCC pin to the Vcc same as the controller)

            ADC_AREF  --> External Voltage reference
                (connect ADC_AREF pin to the Vcc[0 , 5v])
                
            ADC_INTERNAL_2_56 --> internal voltage
    FOR PIC:
    Options:
            ADC_EXT_REF
            ADC_INT_REF
 */
#if IS_AVR()
#define ADC_VREF (ADC_AVCC)
#if ADC_VREF != ADC_AVCC
#if ADC_VREF != ADC_AREF
#if ADC_VREF != ADC_INTERNAL_2_56
#error "[ADC_Config]: Invalid value for ADC_VREF macro"
#endif //ADC_VREF != ADC_INTERNAL_2_56
#endif //ADC_VREF != ADC_AREF
#endif //ADC_VREF != ADC_AVCC
#elif IS_PIC()
#define ADC_VREF  (ADC_EXT_REF)
#if ADC_VREF != ADC_EXT_REF
#if ADC_VREF != ADC_INT_REF
#error "[ADC_Config]: Invalid value for ADC_VREF macro"
#endif //ADC_VREF != ADC_INT_REF
#endif //ADC_VREF != ADC_EXT_REF
#endif // MCU_TYPE

/* Options:
            ADC_POSITIVE_SUP
            ADC_NEGATIVE_SUP
*/
#if IS_PIC()
#define ADC_SUP (ADC_NEGATIVE_SUP)
#if ADV_SUP != ADC_POSITIVE_SUP
#if ADC_SUP != ADC_NEGATIVE_SUP
#error "[ADC_Config]: Invalid value for ADC_SUP macro"
#endif //ADC_SUP != ADC_NEGATIVE_SUP
#endif //ADV_SUP != ADC_POSITIVE_SUP
#endif

/* Options:
            LEFT_ADJUSTMENT
            RIGHT_ADJUSTMENT
            
 */
#define ADC_ADJUSTMENT (RIGHT_ADJUSTMENT)
#if ADC_ADJUSTMENT != RIGHT_ADJUSTMENT
#if ADC_ADJUSTMENT != LEFT_ADJUSTMENT
#error "[ADC_Config]: Invalid value for ADC_ADJUSTMENT macro"
#endif //ADC_ADJUSTMENT != LEFT_ADJUSTMENT
#endif //ADC_ADJUSTMENT != RIGHT_ADJUSTMENT

/* Options:
            ADC_PRESCALER_2
            ADC_PRESCALER_4
            ADC_PRESCALER_8
            ADC_PRESCALER_16
            ADC_PRESCALER_32
            ADC_PRESCALER_64
            if IS_AVR()
            ADC_PRESCALER_128
 */
#define ADC_PRESCALER (ADC_PRESCALER_128)

#define TIMEOUT (5000)

#endif /* MCAL_ADC_CONFIG_H_ */
