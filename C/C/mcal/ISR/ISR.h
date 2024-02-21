#ifndef PIC_ISR_H_
#define PIC_ISR_H_
/*bits*/
#define EXTI_INT0 (0)
#define EXTI_INT1 (1)
#define EXTI_INT2 (2)
#define EXTI_RB   (3)

#define ADC_INT   (4)

#if IS_PIC()
uint8_t priorityState=DISABLED;
#endif

error_t ISR_Init(uint8_t kInterruptSource, void (*pFun)(void));

#endif
