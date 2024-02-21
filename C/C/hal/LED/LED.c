#include "../../common/Types.h"
#include "../../mcal/GPIO/GPIO.h"
#include "LED.h"

void LED_Init(LED_t* pLED)
{
    if (pLED->activeState == kLedActiveLow)
    {
        LED_TurnOff(pLED);
    }
    GPIO_SetPinDirection(pLED->port, pLED->pin, kOutput);
}
error_t LED_TurnOn(LED_t* pLED)
{
    error_t retErrorState = kNoError;
    if (pLED->activeState == kLedActiveHigh)
    {
        GPIO_SetPinValue(pLED->port, pLED->pin, kHigh);
    }
    else if (pLED->activeState == kLedActiveLow)
    {
        GPIO_SetPinValue(pLED->port, pLED->pin, kLow);
    }
    else
    {
        retErrorState = kFunctionParameterError;
    }
    return retErrorState;
}
error_t LED_TurnOff(LED_t* pLED)
{
    error_t retErrorState = kNoError;
   if (pLED->activeState == kLedActiveHigh)
    {
        GPIO_SetPinValue(pLED->port, pLED->pin, kLow);
    }
    else if (pLED->activeState == kLedActiveLow)
    {
        GPIO_SetPinValue(pLED->port, pLED->pin, kHigh);
    }
    else
    {
        retErrorState = kFunctionParameterError;
    }
    return retErrorState;
}
