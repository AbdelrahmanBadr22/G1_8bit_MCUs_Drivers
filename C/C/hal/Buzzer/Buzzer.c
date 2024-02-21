#include "../../common/Types.h"
#include "../../mcal/GPIO/GPIO.h"
#include "Buzzer.h"

void Buzzer_Init(Buzzer_t* pBuzzer)
{
    if (pBuzzer->activeState == kBuzzerActiveLow)
    {
        Buzzer_TurnOff(pBuzzer);
    }
    GPIO_SetPinDirection(pBuzzer->port, pBuzzer->pin, kOutput);
}
error_t Buzzer_TurnOn(Buzzer_t* pBuzzer)
{
    error_t retErrorState = kNoError;
    if (pBuzzer->activeState == kBuzzerActiveHigh)
    {
        GPIO_SetPinValue(pBuzzer->port, pBuzzer->pin, kHigh);
    }
    else if (pBuzzer->activeState == kBuzzerActiveLow)
    {
        GPIO_SetPinValue(pBuzzer->port, pBuzzer->pin, kLow);
    }
    else
    {
        retErrorState = kFunctionParameterError;
    }
    return retErrorState;
}
error_t Buzzer_TurnOff(Buzzer_t* pBuzzer)
{
    error_t retErrorState = kNoError;
   if (pBuzzer->activeState == kBuzzerActiveHigh)
    {
        GPIO_SetPinValue(pBuzzer->port, pBuzzer->pin, kLow);
    }
    else if (pBuzzer->activeState == kBuzzerActiveLow)
    {
        GPIO_SetPinValue(pBuzzer->port, pBuzzer->pin, kHigh);
    }
    else
    {
        retErrorState = kFunctionParameterError;
    }
    return retErrorState;
}
