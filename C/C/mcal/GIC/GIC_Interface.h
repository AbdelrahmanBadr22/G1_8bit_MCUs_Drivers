/**
 * @file   GIC_Interface.h
 * @author :Mohamed Refat
 * @brief  : This file contain the prototype of the
 *              Global Interrupt Control (GIC)
 * @version:0.1
 * @date   :2023-08-16
 */
#ifndef MCAL_GIC_INTERFACE_H_
#define MCAL_GIC_INTERFACE_H_

#define GLOBAL_INTERRUPT_ENABLE   (1)
#define GLOBAL_INTERRUPT_DISABLE  (0)

//in AVR SREG_I BIT AND IN PIC INTCON_GIE
#define GLOBAL_INTERRUPT_BIT      (7)

/**
 * @brief  : This function is used to enable Global Interrupt
 *
 * @param copyControl : OPTIONS:
 *                          GLOBAL_INTERRUPT_ENABLE
 *                          GLOBAL_INTERRUPT_DISABLE
 *
 * @return error_t = kNoError --> There is no error in function parameter
 *                   kFunctionParameterError -->Error in function parameter
 */
error_t GIC_voidGlobalInterruptControl(uint8_t copyControl);

#endif /* MCAL_GIC_INTERFACE_H_ */
