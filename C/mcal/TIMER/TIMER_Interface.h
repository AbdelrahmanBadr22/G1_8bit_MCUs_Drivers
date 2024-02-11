/*
 * TIMER_Interface.h
 *
 *  Created on: Oct 26, 2023
 *      Author: Mohamed Refat
 */

#ifndef MCAL_TIMER_TIMER_INTERFACE_H_
#define MCAL_TIMER_TIMER_INTERFACE_H_

#define TIMER0 (0)
#define TIMER1 (1)
#define TIMER2 (2)

#define TIMER_NORMAL_MODE (0)
#define TIMER_CTC_MODE    (1) /* Clear Time On Compare Match */
#define TIMER_PWM_MODE    (2)

/* Clock sources for TIMER  0  */
#define TIMER0_OFF                  (0)
#define TIMER0_PRESCALER_1          (1)
#define TIMER0_PRESCALER_8          (2)
#define TIMER0_PRESCALER_64         (3)
#define TIMER0_PRESCALER_128        (4)
#define TIMER0_PRESCALER_1024       (5)
#define TIMER0_EXTERNAL_CLK_FALLING (6)
#define TIMER0_EXTERNAL_CLK_RISING  (7)

/* Clock sources for TIMER 1  */
#define TIMER1_OFF                  (0)
#define TIMER1_PRESCALER_1          (1)
#define TIMER1_PRESCALER_8          (2)
#define TIMER1_PRESCALER_64         (3)
#define TIMER1_PRESCALER_128        (4)
#define TIMER1_PRESCALER_1024       (5)
#define TIMER1_EXTERNAL_CLK_FALLING (6)
#define TIMER1_EXTERNAL_CLK_RISING  (7)


/* Clock sources for TIMER 2  */
#define TIMER2_OFF                  (0)
#define TIMER2_PRESCALER_1          (1)
#define TIMER2_PRESCALER_8          (2)
#define TIMER2_PRESCALER_32         (3)
#define TIMER2_PRESCALER_64         (4)
#define TIMER2_PRESCALER_128        (5)
#define TIMER2_PRESCALER_256        (6)
#define TIMER2_PRESCALER_1024       (7)

/* OCn State n--> [0,1,2] for TIMER 0 , 1 , 2 */
#define TIMER_OC_TURN_OFF (0)
#define TIMER_OC_TOGGLE   (1)
#define TIMER_OC_CLEAR    (2)
#define TIMER_OC_SET      (3)

/* Timer0 interrupt sources */
#define TIMER0_INTERRUPT_OVERFLOW (0)
#define TIMER0_INTERRUPT_CTC      (1)

/* Timer1 interrupt sources */
#define TIMER1_INTERRUPT_OVERFLOW (0)
#define TIMER1_INTERRUPT_CTCA     (1)
#define TIMER1_INTERRUPT_CTCB     (2)
#define TIMER1_INTERRUPT_ICU1     (3)


/* Timer2 interrupt sources */
#define TIMER2_INTERRUPT_OVERFLOW (2)
#define TIMER2_INTERRUPT_CTC      (3)

/* Timer1 PWM Pins */
#define PWM1_OC1A (0)
#define PWM1_OC1B (1)

/* PWM on Timer1 Prescaler */
#define PWM1_PRESCALER_1          (1)
#define PWM1_PRESCALER_8          (8)
#define PWM1_PRESCALER_64         (64)
#define PWM1_PRESCALER_128        (128)
#define PWM1_PRESCALER_1024       (1024)

/* PWM1 Channel Mode */
#define PWM1_INVERTING     (0)
#define PWM1_NON_INVERTING (1)


error_t TIMER0_Init(uint8_t kMode, uint8_t kClock);
void TIMER0_SetPreload(uint8_t preloadValue);
void TIMER0_SetCTC(uint8_t kOCR_Value);         //IGNORE-STYLE-CHECK[B004]
error_t TIMER0_SetOCPinMode(uint8_t kOCPinMode);
error_t TIMER0_SetDutyCycle(uint8_t dutyCycle);
error_t TIMER0_SetCallBackFun(uint8_t interruptSource,
                                            void (*pTimer_ISR)(void));


/**
 * @brief        : This Function is used to Init the Timer1
 *
 * @param kMode  : OPTIONS[ TIMER_NORMAL_MODE, TIMER_CTC_MODE, TIMER_PWM_MODE]
 * @param kClock : OPTIONS:
 *                          TIMER0_OFF
 *                          TIMER0_PRESCALER_1
 *                          TIMER0_PRESCALER_8
 *                          TIMER0_PRESCALER_64
 *                          TIMER0_PRESCALER_128
 *                          TIMER0_PRESCALER_1024
 *                          TIMER0_EXTERNAL_CLK_FALLING
 *                          TIMER0_EXTERNAL_CLK_RISING
 *
 * @return error_t : kNoError   --> if function parameter is Correct
 *					kFunctionParameterError --> if function parameter is wrong
 */
error_t TIMER1_Init(uint8_t kMode, uint8_t kClock);
void TIMER1_SetPreload(uint16 preloadValue );
void TIMER1_SetCTCA(uint16 kOCRA_Value);        //IGNORE-STYLE-CHECK[B004]
void TIMER1_SetCTCB(uint16 kOCRB_Value);        //IGNORE-STYLE-CHECK[B004]

/**
 * @brief           : This Function is used to Set OCn[A/B] Pin Mode at overflow
 *
 * @param OCPinMode : OPTIONS:
 *                              TIMER_OC_TURN_OFF
 *                              TIMER_OC_TOGGLE
 *                              TIMER_OC_CLEAR
 *                              TIMER_OC_SET
 * @return error_t
 */
error_t TIMER1_SetOCAPinMode(uint8_t kOCPinMode);
error_t TIMER1_SetOCBPinMode(uint8_t kOCPinMode);

/**
 * @brief          : This Function is used to Set Channel OC1[A/B] Mode
 *
 * @param kChannel : [PWM1_OC1A, PWM1_OC1B]
 * @param kMode    : [PWM1_INVERTING, PWM1_NON_INVERTING]
 * @return error_t
 */
error_t TIMER1_SetPWM_Channel_Mode(uint8_t kChannel, uint8_t kMode);

/**
 * @brief   : This Function is used to Set the frequency of PWM at timer1
 *
 * @param frequency :Value of the frequency (Max allowed freq is CPU_FRQ )
 * @param kPrescaler  : OPTIONS:
 *                              PWM1_PRESCALER_1
 *                              PWM1_PRESCALER_8
 *                              PWM1_PRESCALER_64
 *                              PWM1_PRESCALER_128
 *                              PWM1_PRESCALER_1024
 * @return error_t
 */
error_t TIMER1_SetPWM_Freq(uint32_t frequency, uint32_t kPrescaler);
/**
 * @brief  : This Function is used to Set the frequency of PWM at timer1
 *
 * @param dutyCycle  : Copy Duty Cycle [0 : 100] allowed values
 * @param kChannel   : [PWM1_OC1A, PWM1_OC1B]
 * @return error_t
 */
error_t TIMER1_SetDutyCycle(uint8_t dutyCycle, uint8_t kChannel);

error_t TIMER1_SetCallBackFun(uint8_t interruptSource,
                                            void (*pTimer_ISR)(void));


error_t TIMER2_Init(uint8_t kMode, uint8_t kClock);
void TIMER2_SetPreload(uint8_t preloadValue);
void TIMER2_SetCTC(uint8_t kOCR_Value);          //IGNORE-STYLE-CHECK[B004]
error_t TIMER2_SetOCPinMode(uint8_t kOCPinMode);
error_t TIMER2_SetDutyCycle(uint8_t dutyCycle);
error_t TIMER2_SetCallBackFun(uint8_t interruptSource,
                                            void (*pTimer_ISR)(void));


#endif /* MCAL_TIMER_TIMER_INTERFACE_H_ */
