/**
 * @file ICU.h
 * @author Mohamed Refat
 * @brief
 * @version 0.1
 * @date 2024-02-18
 *
 */

#ifndef MCAL_ICU_ICU_H_
#define MCAL_ICU_ICU_H_

#define ICU_FALLING_EDGE (0)
#define ICU_RISING_EDGE  (1)

/* This values are fixed dont change them*/

#define ICU_PRESCALER_1          (1)
#define ICU_PRESCALER_8          (2)
#define ICU_PRESCALER_64         (3)
#define ICU_PRESCALER_128        (4)
#define ICU_PRESCALER_1024       (5)

#define TCCR1B_ICNC1  (7) /* Input Capture Noise Canceler */
#define TCCR1B_ICES1  (6) /* Input Capture Edge Select */
#define TIMSK_ICIE1   (5) /*  Input Capture Interrupt Enable */

#define TIMER_CLOCK_MASK (0b00000111)
/**
 * @brief This Function is used to init the ICU module
 * @param prescaler OPTIONS:
 *                          ICU_PRESCALER_1
 *                          ICU_PRESCALER_8
 *                          ICU_PRESCALER_64
 *                          ICU_PRESCALER_128
 *                          ICU_PRESCALER_1024
 * @note After calling this function timer1 start to count
 *        so call it after configuring the ICU parameters
 * @return None
 */
void ICU_Init(uint8_t prescaler);

/**
 * @brief This function is used to set the capture edge
 *
 * @param edge [ICU_FALLING_EDGE , ICU_RISING_EDGE ]
 * @return error_t
 */
error_t ICU_SelectEdge(uint8_t edge);

/**
 * @brief This function is used to set the ISR value
 *          this function will be called when a capture occurred
 *
 * @param pISR_Fun Pinter to the function
 * @return error_t
 */
error_t ICU_SetCallBackFunc(void (*pISR_Fun)(void));

/**
 * @brief This function is used to read the captured value when the
 *          interrupt occurred
 *
 * @param pValue Pointer to the variable that will hold the captured value
 * @return error_t
 */
error_t ICU_ReadCaptureValue(uint16 *pValue);

/**
 * @brief This Function is used to Disable the ICU module
 * @return None
 */
void ICU_Disable(void);

#endif /* MCAL_ICU_ICU_H_ */
