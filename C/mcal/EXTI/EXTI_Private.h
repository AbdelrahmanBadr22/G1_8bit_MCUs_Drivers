/**
 * @file   EXTI_Private.h
 * @author :Mohamed Refat
 * @brief  :This file contain private macros and interfaces
 * @version: 0.1
 * @date   : 2023-08-16
 */
#ifndef MCAL_EXTI_PRIVATE_H_
#define MCAL_EXTI_PRIVATE_H_
    #if MCU_TYPE == _AVR
        #define GICR_INT0     (6)
        #define GICR_INT1     (7)
        #define GICR_INT2     (5)


        #define MCUCR_ISC00   (0)
        #define MCUCR_ISC01   (1)
        #define MCUCR_ISC10   (2)
        #define MCUCR_ISC11   (3)

        #define MCUCSR_ISC2   (6)

    #elif MCU_TYPE == _PIC
        #define INTCON_GIE    (7)
        #define INTCON_GIEH   (7)
        #define INTCON_PEIE   (6)
        #define INTCON_GIEL   (6)
        #define INTCON_INT0IE   (4)
        #define INTCON_INT0IF   (1)

        #define INTCON3_INT1IE   (3)
        #define INTCON3_INT1IF   (0)
        #define INTCON3_INT1IP  (6)

        #define INTCON3_INT2IE   (4)
        #define INTCON3_INT2IF   (1)
        #define INTCON3_INT2IP   (7)

        #define INTCON2_INTEDG0  (6)
        #define INTCON2_INTEDG1  (5)
        #define INTCON2_INTEDG2  (4)


        #define RCON_IPEN        (7)
    #endif
#endif /* MCAL_EXTI_PRIVATE_H_ */
