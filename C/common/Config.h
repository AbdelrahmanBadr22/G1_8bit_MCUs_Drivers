#ifndef CONFIG_H
#define CONFIG_H

#define _AVR     (1)
#define _PIC     (2)

#define IS_AVR      (MCU_TYPE == _AVR)
#define IS_PIC      (MCU_TYPE == _PIC)
//#define MCU_TYPE  (AVR)

#define CPU_FREQ (8000000LU)

#endif // CONFIG_H_H
