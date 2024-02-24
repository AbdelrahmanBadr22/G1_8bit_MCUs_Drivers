#ifndef SLEEP_H
#define SLEEP_H

#if IS_AVR()
#define IDLE_MODE                   (1)
#define ADC_NOISE_REDUCTION_MODE    (2)
#define POWER_DOWN_MODE             (3)
#define POWER_SAVE_MODE             (4)
#define STANDBY_MODE                (5)
#define EXTENED_STANDBY_MODE        (6)

#define MCUCR_SE      (7)
#define MCUCR_SM2     (6)
#define MCUCR_SM1     (5)
#define MCUCR_SM0     (4)

#elif IS_PIC()
#define SLEEP_MODE        (1)
#define PRI_RUN_MODE      (2)
#define SEC_RUN_MODE      (3)
#define RC_RUN_MODE       (4)
#define PRI_IDLE_MODE     (5)
#define SEC_IDLE_MODE     (6)
#define RC_IDLE_MODE      (7)

#define OSCCON_IDLEN        (7)
#define OSCCON_SCS1         (1)
#define OSCCON_SCS0         (0)
#endif // MCU TYPE

error_t SLEEP(uint8_t mode);

#endif //SLEEP_H
