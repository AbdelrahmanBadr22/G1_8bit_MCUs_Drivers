/*
 * TIMER_Private.h
 *
 *  Created on: Oct 26, 2023
 *      Author: Mohamed Refat
 */

#ifndef MCAL_TIMER_TIMER_PRIVATE_H_
#define MCAL_TIMER_TIMER_PRIVATE_H_


/* Macros */
#define TCCR0_WGM00  (6) /* Waveform  Generation Mode 0 */
#define TCCR0_WGM01  (3) /* Waveform  Generation Mode 1*/
#define TCCR0_COMM01 (5) /* Compare Match Output Mode */
#define TCCR0_COMM00 (4) /* Compare Match Output Mode */
#define TIMSK_TOIE0  (0) /* Timer0 Overflow Interrupt Enable */
#define TIMSK_OCIE0  (1) /* Output Compare Interrupt Enable */

#define TCCR1A_COM1A1 (7) /* Compare Output Mode for Channel A */
#define TCCR1A_COM1A0 (6) /* Compare Output Mode for Channel A */
#define TCCR1A_COM1B1 (5) /* Compare Output Mode for Channel B */
#define TCCR1A_COM1B0 (4) /* Compare Output Mode for Channel B */
#define TCCR1A_WGM11  (1) /* Waveform Generation Mode */
#define TCCR1A_WGM10  (0) /* Waveform Generation Mode */
#define TCCR1B_WGM13  (4) /* Waveform Generation Mode */
#define TCCR1B_WGM12  (3) /* Waveform Generation Mode */
#define TCCR1B_ICNC1  (7) /* Input Capture Noise Canceler */
#define TCCR1B_ICES1  (6) /* Input Capture Edge Select */
#define TIMSK_TOIE1   (2) /* Timer2 Overflow Interrupt Enable */
#define TIMSK_OCIE1B  (3) /* Output Compare channel B Interrupt Enable */
#define TIMSK_OCIE1A  (4) /* Output Compare channel B Interrupt Enable */
#define TIMSK_ICIE1   (5) /*  Input Capture Interrupt Enable */

#define TCCR2_WGM20  (6) /* Waveform  Generation Mode 0 */
#define TCCR2_WGM21  (3) /* Waveform  Generation Mode 1*/
#define TCCR2_COMM21 (5) /* Compare Match Output Mode */
#define TCCR2_COMM20 (4) /* Compare Match Output Mode */
#define TIMSK_TOIE2  (6) /* Timer0 Overflow Interrupt Enable */
#define TIMSK_OCIE2  (7) /* Output Compare Interrupt Enable */


#define RESOLUTION_8BIT  (255)
#define RESOLUTION_10BIT (1023)

/* MASK */
#define TIMER_CLOCK_MASK (0b00000111)

/*PIC*/
#define TIMER0_TMR0ON       (7)
#define TIMER0_T08BIT       (6)
#define TIMER0_T0CS         (5)
#define TIMER0_T0SE         (4)
#define TIMER0_PSA          (3)
#define TIMER0_T0PS2        (2)
#define TIMER0_T0PS1        (1)
#define TIMER0_T0PS0        (0)

#define INTCON_PEIE         (6)
#define INTCON_TMR0IE       (5)
#define INTCON_TMR0IF       (2)

#define TIMER0_PRESCALER_DIV_BY_2       (0)
#define TIMER0_PRESCALER_DIV_BY_4       (1)
#define TIMER0_PRESCALER_DIV_BY_8       (2)
#define TIMER0_PRESCALER_DIV_BY_16      (3)
#define TIMER0_PRESCALER_DIV_BY_32      (4)
#define TIMER0_PRESCALER_DIV_BY_64      (5)
#define TIMER0_PRESCALER_DIV_BY_128     (6)
#define TIMER0_PRESCALER_DIV_BY_256     (7)

#define TIMER0_PRESCALER_MASK   (0b11111000)

#define TIMER_8BIT          (0)
#define TIMER_16BIT         (1)
#endif /* MCAL_TIMER_TIMER_PRIVATE_H_ */
