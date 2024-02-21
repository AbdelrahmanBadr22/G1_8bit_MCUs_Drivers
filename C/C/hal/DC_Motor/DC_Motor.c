#include "../../common/Types.h"
#include "../../mcal/GPIO/GPIO.h"
#include "DC_Motor.h"


error_t DcMotor_Init(DcMotor_t * pDcMotor)
{
    error_t retErrorState = kNoError;
    if (pDcMotor != NULL)
    {
        GPIO_SetPinDirection(pDcMotor->port, pDcMotor->pin1, kOutput);
        GPIO_SetPinDirection(pDcMotor->port, pDcMotor->pin2, kOutput);
    }
    else
    {
        retErrorState = kFunctionParameterError;
    }
    return retErrorState;
}
error_t DcMotor_ClockWise(DcMotor_t * pDcMotor)
{
    error_t retErrorState = kNoError;
    if (pDcMotor != NULL)
    {
        GPIO_SetPinValue(pDcMotor->port, pDcMotor->pin1, kHigh);
        GPIO_SetPinValue(pDcMotor->port, pDcMotor->pin2, kLow);
    }
    else
    {
        retErrorState = kFunctionParameterError;
    }
    return retErrorState;
}
error_t DcMotor_AntiClockWise(DcMotor_t * pDcMotor)
{
    error_t retErrorState = kNoError;
    if (pDcMotor != NULL)
    {
        GPIO_SetPinValue(pDcMotor->port, pDcMotor->pin1, kLow);
        GPIO_SetPinValue(pDcMotor->port, pDcMotor->pin2, kHigh);
    }
    else
    {
        retErrorState = kFunctionParameterError;
    }
    return retErrorState;
}
error_t DcMotor_Stop(DcMotor_t * pDcMotor)
{
    error_t retErrorState = kNoError;
    if (pDcMotor != NULL)
    {
        GPIO_SetPinValue(pDcMotor->port, pDcMotor->pin1, kLow);
        GPIO_SetPinValue(pDcMotor->port, pDcMotor->pin2, kLow);
    }
    else
    {
        retErrorState = kFunctionParameterError;
    }
    return retErrorState;
}
