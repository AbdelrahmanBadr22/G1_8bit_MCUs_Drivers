#include "../../common/Types.h"
#include "../../mcal/GPIO/GPIO.h"
#include "PIR.h"

error_t PIR_Init(PIR_t* pPIR)
{
    error_t retErrorState = kNoError;
    if (pPIR!=NULL)
    {
      GPIO_SetPinDirection(pPIR->port, pPIR->pin, kInput);
    }
    else
    {
        retErrorState = kFunctionParameterError;
    }
 return retErrorState;
}
error_t PIR_GetVal(PIR_t* pPIR, state_t * state)
{
    error_t retErrorState = kNoError;
    if (pPIR!=NULL)
    {
        GPIO_GetPinValue(pPIR->port, pPIR->pin, state);
    }
    else
    {
        retErrorState = kFunctionParameterError;
    }
    return retErrorState;
}
