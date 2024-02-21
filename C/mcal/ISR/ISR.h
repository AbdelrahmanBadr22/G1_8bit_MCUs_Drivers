#ifndef PIC_ISR_H_
#define PIC_ISR_H_


#if MCU_TYPE == _PIC
uint8_t priorityState=DISABLED;
#endif

error_t ISR_Init(uint8_t kInterruptSource, void (*pFun)(void));

#endif
