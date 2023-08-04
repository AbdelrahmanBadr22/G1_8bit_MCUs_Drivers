#include "../../common/Types.h"
#include "../../mcal/GPIO/GPIO.h"
#include "Relay.h"

error_t Relay_Init(Relay_t* pRelay)
{
    error_t retErrorState = kNoError;
    if (pRelay != NULL_ptr)
    {
        GPIO_SetPinDirection(pRelay->port, pRelay->pin, kOutput);
    }
    else
    {
        retErrorState = kFunctionParameterError;
    }
    return retErrorState;
}
error_t Relay_TurnOn(Relay_t* pRelay)
{
    error_t retErrorState = kNoError;
    if (pRelay != NULL_ptr)
    {
        GPIO_SetPinValue(pRelay->port, pRelay->pin, kHigh);
    }
    else
    {
        retErrorState = kFunctionParameterError;
    }
    return retErrorState;
}
error_t Relay_TurnOff(Relay_t* pRelay)
{
    error_t retErrorState = kNoError;
    if (pRelay != NULL_ptr)
    {
        GPIO_SetPinValue(pRelay->port, pRelay->pin, kLow);
    }
    else
    {
        retErrorState = kFunctionParameterError;
    }
    return retErrorState;
}
