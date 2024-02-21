/**
 * @file    EXTI_Interface.h
 * @author : Mohamed Refat
 * @brief  : This file contain the prototype of the
 *              External Interrupts
 * @version:0.1
 * @date   :2023-08-16
 */
#ifndef MCAL_EXTI_EXTI_INTERFACE_H_
#define MCAL_EXTI_EXTI_INTERFACE_H_

#define EXTI_INT0 (0)
#define EXTI_INT1 (1)
#define EXTI_INT2 (2)

#define EXTI_FALLING_EDGE (4)
#define EXTI_RISING_EDGE  (5)
#define EXTI_LOW_LEVEL    (6)
#define EXTI_ON_CHANGE   (7)

#if MCU_TYPE == _PIC
    #define EXTI_HIGH_PRIORITY (8)
    #define EXTI_LOW_PRIORITY (9)
#endif

error_t EXTI_InterruptEnable (uint8_t kInterruptSource);
/**
 * @brief
 *
 * @param kInterruptSource :
 * @return  error_t   :NoError:
 *                          if function  parameter is Correct
 *                    :kFunctionParameterError:
 *                          if function  parameter is wrong
 */
error_t EXTI_InterruptDisable(uint8_t kInterruptSource);
/**
 * @brief : This fuction is used to Disable a specific External interrupt
 *
 * @param kInterruptSource  : copy from EXTI Number   OPTIONS:
 *                             [EXTI_INT0 ,EXTI_INT0 , EXTI_INT0]
 *
 * @param kSenseControl : copy From Sense control. OPTIONS:
 *                             EXTI_FALLING_EDGE   EXTI_RISING_EDGE
 *                             EXTI_LOW_LEVEL      EXTI_ON_CHANGE
 *
 * @note : For EXTI_INT2 the only valid sense control is
 *                          [EXTI_RISING_EDGE , EXTI_FALLING_EDGE ]
 *
 * @return  error_t :NoError:
 *                        if function  parameter is Correct
 *                  :kFunctionParameterError:
 *                          if function  parameter is wrong
 */
error_t EXTI_SetSenseControl(uint8_t kInterruptSource, uint8_t kSenseControl);
/**
 * @brief             : This function is used to set call back function
 *
 * @param kInterruptSource  : copy from EXTI Number   OPTIONS:
 *                             [EXTI_INT0 ,EXTI_INT0 , EXTI_INT0]
 *
 * @param pFun : pFun is a pointer to the function that will be passed to ISR
 * @return  error_t :NoError:
 *                        if function  parameter is Correct
 *                  :kFunctionParameterError:
 *                         if function  parameter is wrong
 */
error_t EXTI_SetCallBackFun(uint8_t kInterruptSource, void (*pFun)(void));
#if MCU_TYPE == _PIC
/**
 * @brief             : This function is used to set priority
 *
 * @param kInterruptSource  : copy from EXTI Number   OPTIONS:
 *                             [EXTI_INT0 ,EXTI_INT0 , EXTI_INT0]
 *
 * @param kInterruptPriority : copy from state of priority OPTIONS:
 *                              [ENABLED ,DISABLED]
 * @param kPriorityLevel : copy from level of priority   OPTIONS:
 *                              [EXTI_HIGH_PRIORITY ,EXTI_LOW_PRIORITY]
 *      NOTE: If Disabled is chosen , Priority level is not considered
 * @return  error_t :NoError:
 *                        if function  parameter is Correct
 *                  :kFunctionParameterError:
 *                         if function  parameter is wrong
 */
error_t EXTI_SetPriority(uint8_t kInterruptSource,
                         uint8_t kInterruptPriority,
                         uint8_t kPriorityLevel);
#endif
#endif /* MCAL_EXTI_EXTI_INTERFACE_H_ */
