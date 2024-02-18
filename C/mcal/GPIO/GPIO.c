#include "../../common/Config.h"
#include "../../common/Types.h"
#include "../../common/Utils.h"
#include "../../common/Registes.h"
#include "GPIOPrivate.h"
#include "GPIO.h"


error_t GPIO_SetPinDirection(port_t portNumber, pin_t pinNumber,
							 direction_t direction)
{
	error_t retErrorState = kNoError;
	/* Make sure that the Port number and Pin number are in the valid range */
	if (portNumber <= GPIO_LAST_REG  && pinNumber <= GPIO_LAST_PIN )
	{
		if (direction == kOutput)
		{
			switch (portNumber)
			{
				case kPORTA : SET_DIR_OUTPUT(GPIOA_DIR_REG, pinNumber); break;
				case kPORTB : SET_DIR_OUTPUT(GPIOB_DIR_REG, pinNumber); break;
				case kPORTC : SET_DIR_OUTPUT(GPIOC_DIR_REG, pinNumber); break;
				case kPORTD : SET_DIR_OUTPUT(GPIOD_DIR_REG, pinNumber); break;
				#if IS_PIC()
				case kPORTE : SET_DIR_OUTPUT(GPIOE_DIR_REG, pinNumber); break;
				#endif
			}
		}
		else if (direction == kInput)
		{
			switch (portNumber)
			{
				case kPORTA : SET_DIR_INPUT(GPIOA_DIR_REG, pinNumber); break;
				case kPORTB : SET_DIR_INPUT(GPIOB_DIR_REG, pinNumber); break;
				case kPORTC : SET_DIR_INPUT(GPIOC_DIR_REG, pinNumber); break;
				case kPORTD : SET_DIR_INPUT(GPIOD_DIR_REG, pinNumber); break;
				#if IS_PIC()
				case kPORTE : SET_DIR_INPUT(GPIOE_DIR_REG, pinNumber); break;
				#endif
			}
		}
		else
		{
			retErrorState = kFunctionParameterError;
		}
	}
	else
	{
		retErrorState = kFunctionParameterError;
	}

	return retErrorState;
}

error_t GPIO_SetPinValue(port_t portNumber, pin_t pinNumber,
						 state_t pintVoltageLevel)
{
	/* Make sure that the Port number and Pin number are in the valid range */
	error_t retErrorState = kNoError;
	if (portNumber <= GPIO_LAST_REG  && pinNumber <= GPIO_LAST_PIN )
	{
		if (pintVoltageLevel ==kHigh)
		{
			switch ( portNumber)
			{
				case kPORTA : SET_BIT(GPIOA_OUT_REG, pinNumber); break;
				case kPORTB : SET_BIT(GPIOB_OUT_REG, pinNumber); break;
				case kPORTC : SET_BIT(GPIOC_OUT_REG, pinNumber); break;
				case kPORTD : SET_BIT(GPIOD_OUT_REG, pinNumber); break;
				#if IS_PIC()
				case kPORTE : SET_BIT(GPIOE_OUT_REG, pinNumber); break;
				#endif
			}
		}
		else if (pintVoltageLevel ==kLow)
		{
			switch (portNumber)
			{
				case kPORTA : CLR_BIT(GPIOA_OUT_REG, pinNumber); break;
				case kPORTB : CLR_BIT(GPIOB_OUT_REG, pinNumber); break;
				case kPORTC : CLR_BIT(GPIOC_OUT_REG, pinNumber); break;
				case kPORTD : CLR_BIT(GPIOD_OUT_REG, pinNumber); break;
				#if IS_PIC()
				case kPORTE : CLR_BIT(GPIOE_OUT_REG, pinNumber); break;
				#endif
			}
		}
		else
		{
			retErrorState = kFunctionParameterError;
		}
	}else
	{
		retErrorState = kFunctionParameterError;
	}
	return retErrorState;
}
error_t GPIO_GetPinValue(port_t portNumber, pin_t pinNumber, state_t * state)
{
 error_t retErrorState = kNoError;
   /* Make sure that the Port number and Pin number are in the valid range */
   if (portNumber <= GPIO_LAST_REG   && pinNumber <= GPIO_LAST_PIN )
   {
    switch (portNumber)
    {
      case kPORTA : *state= GET_BIT(GPIOA_IN_REG, pinNumber); break;
      case kPORTB : *state= GET_BIT(GPIOB_IN_REG, pinNumber); break;
      case kPORTC : *state= GET_BIT(GPIOC_IN_REG, pinNumber); break;
      case kPORTD : *state =GET_BIT(GPIOD_IN_REG, pinNumber); break;
	  #if IS_PIC()
	  case kPORTE : *state =GET_BIT(GPIOE_IN_REG, pinNumber); break;
	  #endif
    }
   }
   else
   {
     retErrorState = kFunctionParameterError;
   }

    return retErrorState;

}
error_t GPIO_SetPortDirection(port_t portNumber, uint8_t direction)
{
 error_t retErrorState = kNoError;
    switch (portNumber)
    {
     case kPORTA : GPIOA_DIR_REG = direction; break;
     case kPORTB : GPIOB_DIR_REG = direction; break;
     case kPORTC : GPIOC_DIR_REG = direction; break;
     case kPORTD : GPIOD_DIR_REG = direction; break;
	 #if IS_PIC()
	 case kPORTE : GPIOE_DIR_REG = direction; break;
	 #endif
	 default:retErrorState = kFunctionParameterError;break;
    }
  return retErrorState;
}

error_t GPIO_SetPortValue(port_t portNumber, uint8_t pintVoltageLevel)
{
 error_t retErrorState = kNoError;
   switch (portNumber)
   {
    case kPORTA : GPIOA_OUT_REG = pintVoltageLevel; break;
    case kPORTB : GPIOB_OUT_REG = pintVoltageLevel; break;
    case kPORTC : GPIOC_OUT_REG = pintVoltageLevel; break;
    case kPORTD : GPIOD_OUT_REG = pintVoltageLevel; break;
	#if IS_PIC()
	case kPORTE : GPIOE_OUT_REG = pintVoltageLevel; break;
	#endif
	default: retErrorState=kFunctionParameterError;break;
   }
 return retErrorState;
}

error_t GPIO_GetPortValue(port_t portNumber, uint8_t * state)
{
  error_t retErrorState = kNoError;
    switch (portNumber)
    {
     case kPORTA : *state = GPIOA_IN_REG; break;
     case kPORTB : *state = GPIOB_IN_REG; break;
     case kPORTC : *state = GPIOC_IN_REG; break;
     case kPORTD : *state = GPIOD_IN_REG; break;
	 #if IS_PIC()
	 case kPORTE : *state = GPIOE_IN_REG; break;
	 #endif
	 default:retErrorState = kFunctionParameterError;break;
    }
  return retErrorState;
}

error_t GPIO_SetPinPullup(port_t portNumber, pin_t pinNumber)
{
	error_t retErrorState = kNoError;
	if (portNumber <=GPIO_LAST_REG && pinNumber <= GPIO_LAST_PIN )
	{
		switch ( portNumber)
		{
			case kPORTA : SET_DIR_INPUT(GPIOA_DIR_REG, pinNumber);
						  SET_BIT(GPIOA_OUT_REG, pinNumber);
						  break;
			case kPORTB : SET_DIR_INPUT(GPIOB_DIR_REG, pinNumber);
						  SET_BIT(GPIOB_OUT_REG, pinNumber);
						  break;
			case kPORTC : SET_DIR_INPUT(GPIOC_DIR_REG, pinNumber);
						  SET_BIT(GPIOC_OUT_REG, pinNumber);
						  break;
			case kPORTD : SET_DIR_INPUT(GPIOD_DIR_REG, pinNumber);
						  SET_BIT(GPIOD_OUT_REG, pinNumber);
						  break;
			#if IS_PIC()
			case kPORTE : SET_DIR_INPUT(GPIOE_DIR_REG, pinNumber);
						  SET_BIT(GPIOE_OUT_REG, kHigh);
						  break;
			#endif
		}
	}
	else
	{
		retErrorState = kFunctionParameterError;
	}
	return retErrorState;
}

error_t GPIO_SetLowNibbleValue(port_t portNumber, uint8_t value)
{
	error_t kErrorState = kNoError;
	/* This line to make sure that the high nibble in port value will not change */
	value &= 0X0F;
	switch (portNumber)
	{
		case kPORTA : GPIOA_OUT_REG &= 0XF0; GPIOA_OUT_REG |= value;  break;
		case kPORTB : GPIOB_OUT_REG &= 0XF0; GPIOB_OUT_REG |= value;  break;
		case kPORTC : GPIOC_OUT_REG &= 0XF0; GPIOC_OUT_REG |= value;  break;
		case kPORTD : GPIOD_OUT_REG &= 0XF0; GPIOD_OUT_REG |= value;  break;
		// TODO(@ManarAbdelraouf): #99 Support GPIO_SetLowNibbleValue for pic family
		default:      kErrorState = kFunctionParameterError;  break;
	}
	return kErrorState;
}
error_t GPIO_SetHighNibbleValue(port_t portNumber, uint8_t value)
{
	error_t kErrorState = kNoError;
	/* This line to make sure that the Low nibble in port value will not change */
	value &= 0XF0;
	switch (portNumber)
	{
		case kPORTA : GPIOA_OUT_REG &= 0X0F; GPIOA_OUT_REG |= value;  break;
		case kPORTB : GPIOB_OUT_REG &= 0X0F; GPIOB_OUT_REG |= value;  break;
		case kPORTC : GPIOC_OUT_REG &= 0X0F; GPIOC_OUT_REG |= value;  break;
		case kPORTD : GPIOD_OUT_REG &= 0X0F; GPIOD_OUT_REG |= value;  break;
		default:      kErrorState = kFunctionParameterError;  break;
	}
	return kErrorState;
}

error_t GPIO_SetLowNibbleDirection(port_t portNumber, uint8_t direction)
{
	error_t kErrorState = kNoError;
	/* This line to make sure that the high nibble in port value will not change */
	direction &= 0X0F;
	switch (portNumber)
	{
		case kPORTA : GPIOA_DIR_REG &= 0XF0; GPIOA_DIR_REG |= direction;  break;
		case kPORTB : GPIOB_DIR_REG &= 0XF0; GPIOB_DIR_REG |= direction;  break;
		case kPORTC : GPIOC_DIR_REG &= 0XF0; GPIOC_DIR_REG |= direction;  break;
		case kPORTD : GPIOD_DIR_REG &= 0XF0; GPIOD_DIR_REG |= direction;  break;
		default:      kErrorState = kFunctionParameterError;  break;
	}
	return kErrorState;
}
error_t GPIO_SetHighNibbleDirection(port_t portNumber, uint8_t direction)
{
	error_t kErrorState = kNoError;
	/* This line to make sure that the high nibble in port value will not change */
	direction &= 0XF0;
	switch (portNumber)
	{
		case kPORTA : GPIOA_DIR_REG &= 0X0F; GPIOA_DIR_REG |= direction;  break;
		case kPORTB : GPIOB_DIR_REG &= 0X0F; GPIOB_DIR_REG |= direction;  break;
		case kPORTC : GPIOC_DIR_REG &= 0X0F; GPIOC_DIR_REG |= direction;  break;
		case kPORTD : GPIOD_DIR_REG &= 0X0F; GPIOD_DIR_REG |= direction;  break;
		default:      kErrorState = kFunctionParameterError;  break;
	}
	return kErrorState;
}
