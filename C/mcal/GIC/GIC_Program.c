/**
* @file GIC_Program.c
* @author :Mohamed Refat
* @brief :This file contain the implementation of GIC function
* @version:0.1
* @date :2023-08-16
*/
#include "Config.h"
#include "Types.h"
#include "Registes.h"
#include "Utils.h"
#include "GIC_Interface.h"

error_t GIC_voidGlobalInterruptControl(uint8_t copyControl)
{
error_t kErrorState = kNoError;
#if IS_AVR()
#define STATUS_REG (SREG_REG)
#elif IS_PIC()
#define STATUS_REG (INTCON_REG)
#endif// MCU_TYPE

switch (copyControl)
{
case GLOBAL_INTERRUPT_ENABLE :
SET_BIT(STATUS_REG, GLOBAL_INTERRUPT_BIT); break;
case GLOBAL_INTERRUPT_DISABLE :
CLR_BIT(STATUS_REG, GLOBAL_INTERRUPT_BIT); break;
default: kErrorState = kFunctionParameterError; break;
}
return kErrorState;
}
