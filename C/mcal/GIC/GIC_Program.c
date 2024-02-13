/**
 * @file   GIC_Program.c
 * @author :Mohamed Refat
 * @brief  :This file contain the implementation of GIC function
 * @version:0.1
 * @date   :2023-08-16
 */
#include "../../common/Config.h"
#include "../../common/Types.h"
#include "../../common/Registes.h"
#include "../../common/Utils.h"
#include "GIC_Private.h"
#include "GIC_Interface.h"

error_t GIC_voidGlobalInterruptControl(uint8_t copyControl)
{
	error_t kErrorState = kNoError;
	#if MCU_TYPE == _AVR
	switch (copyControl)
	{
		case GLOBAL_INTERRUPT_ENABLE  : SET_BIT(SREG_REG, SREG_I); break;
		case GLOBAL_INTERRUPT_DISABLE : CLR_BIT(SREG_REG, SREG_I); break;

		default: kErrorState = kFunctionParameterError;	break;
	}
	#elif MCU_TYPE == _PIC
	switch (copyControl)
	{
		case GLOBAL_INTERRUPT_ENABLE  : SET_BIT(INTCON_REG, INTCON_GIE); break;
		case GLOBAL_INTERRUPT_DISABLE : CLR_BIT(INTCON_REG, INTCON_GIE); break;

		default: kErrorState = kFunctionParameterError;	break;
	}
	#endif
	return kErrorState;
}
