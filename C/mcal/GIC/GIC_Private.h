/**
 * @file   GIC_Private.h
 * @author :Mohamed Refat
 * @brief  : This file contain private macros and interfaces
 * @version: 0.1
 * @date   :2023-08-16
 */
#ifndef MCAL_GIC_GIE_PRIVATE_H_
#define MCAL_GIC_GIE_PRIVATE_H_


#define SREG_I (7)
#if MCU_TYPE == _PIC
#define INTCON_GIE    (7)
#endif

#endif /* MCAL_GIC_GIE_PRIVATE_H_ */
