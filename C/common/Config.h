#ifndef CONFIG_H
#define CONFIG_H

#define _AVR     (1)
#define _PIC     (2)

//#define MCU_TYPE  (AVR)

#define IS_AVR()        (MCU_TYPE == _AVR)
#define IS_PIC()        (MCU_TYPE == _PIC)

// Define frequency
#ifndef F_CPU
#define F_CPU          (8000000UL)
#endif
#define _XTAL_FREQ     (F_CPU)
#define CPU_FREQ       (F_CPU)

#endif // CONFIG_H_H
