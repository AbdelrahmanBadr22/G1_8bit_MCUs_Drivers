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
/*PIC*/
#define TIMER_MODE        (1)
#define COUNTER_MODE      (2)

#define RAISING_EDGE    (1)
#define FALING_EDGE     (2)

#define DISABLED            (1)
#define ENABLED             (2)

error_t TIMER0_Init(uint8_t kMode, uint8_t kClock);
void TIMER0_SetPreload(uint8_t preloadValue);
void TIMER0_SetCTC(uint8_t kOCR_Value);         //IGNORE-STYLE-CHECK[B004]
error_t TIMER0_SetOCPinMode(uint8_t kOCPinMode);
error_t TIMER0_SetDutyCycle(uint8_t dutyCycle);
error_t TIMER0_SetCallBackFun(uint8_t interruptSource,
                                            void (*pTimer_ISR)(void));


error_t TIMER1_Init(uint8_t kMode, uint8_t kClock);
void TIMER1_SetPreload(uint16 preloadValue );
void TIMER1_SetCTCA(uint16 kOCRA_Value);        //IGNORE-STYLE-CHECK[B004]
void TIMER1_SetCTCB(uint16 kOCRB_Value);        //IGNORE-STYLE-CHECK[B004]
error_t TIMER1_SetOCAPinMode(uint8_t kOCPinMode);
error_t TIMER1_SetOCBPinMode(uint8_t kOCPinMode);
error_t TIMER1_SetDutyCycle(uint8_t dutyCycle);
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
