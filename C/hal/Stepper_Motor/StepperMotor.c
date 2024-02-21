#include "Types.h"
#include "GPIO.h"
#include "Delay.h"
#include "StepperMotor.h"

//-----------------------------------------------------------------------------
//                               HELPER FUNCTIONS
//-----------------------------------------------------------------------------
static void ClockWiseFullStep(StepperMotor_t * pStepper)
{
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
        Delay_ms(2);
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
        Delay_ms(2);
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
        Delay_ms(2);
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kHigh);

}
static void AntiClockWiseFullStep(StepperMotor_t * pStepper)
{
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kHigh);
        Delay_ms(2);
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kHigh);
        Delay_ms(2);
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kHigh);
        Delay_ms(2);
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
}
static void ClockWiseHalfStep(StepperMotor_t * pStepper)
{
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
        Delay_ms(2);
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
        Delay_ms(2);
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
        Delay_ms(2);
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
        Delay_ms(2);
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
        Delay_ms(2);
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kHigh);
        Delay_ms(2);
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kHigh);
        Delay_ms(2);
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kHigh);
}
static void AntiClockWiseHalfStep(StepperMotor_t * pStepper)
{
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kHigh);
        Delay_ms(2);
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kHigh);
        Delay_ms(2);
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kHigh);
        Delay_ms(2);
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
        Delay_ms(2);
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
        Delay_ms(2);
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
        Delay_ms(2);
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
        Delay_ms(2);
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
}
//-----------------------------------------------------------------------------
//                      STEPPER MOTOR FUNCTIONS
//-----------------------------------------------------------------------------
error_t Stepper_Init(StepperMotor_t * pStepper)
{
    error_t retErrorState = kNoError;
    if (pStepper != NULL)
    {
        GPIO_SetPinDirection(pStepper->port, pStepper->bluePin, kOutput);
        GPIO_SetPinDirection(pStepper->port, pStepper->pinkPin, kOutput);
        GPIO_SetPinDirection(pStepper->port, pStepper->yellowPin, kOutput);
        GPIO_SetPinDirection(pStepper->port, pStepper->orangePin, kOutput);
    }
    else
    {
        retErrorState = kFunctionParameterError;
    }
    return retErrorState;
}
error_t Stepper_ClockWise(StepperMotor_t* pStepper,
                          uint8_t type, uint8_t degree)
{

    error_t retErrorState = kNoError;
    uint8_t iterator=0;
    if ((type==STEPPER_FULLSTEP) && (pStepper != NULL))
    {
        uint8_t numOfIterations=((degree*256)/45)/4;
        for (iterator=0;iterator<numOfIterations;iterator++)
        {
            ClockWiseFullStep(pStepper);
        }
    }
    else if ((type==STEPPER_HALFSTEP) && (pStepper != NULL))
    {
        uint8_t numOfIterations=((degree*512)/45)/4;
        for (iterator=0;iterator<numOfIterations;iterator++)
        {
            ClockWiseHalfStep(pStepper);
        }
    }
    else
    {
        retErrorState = kFunctionParameterError;
    }
    return retErrorState;
}
error_t Stepper_AntiClockWise(StepperMotor_t* pStepper,
                              uint8_t type, uint8_t degree)
{
    error_t retErrorState = kNoError;
    uint8_t iterator=0;
     if ((type==STEPPER_FULLSTEP) && (pStepper != NULL))
    {
        uint8_t numOfIterations=((degree*256)/45)/4;
        for (iterator=0;iterator<numOfIterations;iterator++)
        {
            AntiClockWiseFullStep(pStepper);
        }
    }
    else if ((type==STEPPER_HALFSTEP) && (pStepper != NULL))
    {
        uint8_t numOfIterations=((degree*512)/45)/4;
        for (iterator=0;iterator<numOfIterations;iterator++)
        {
            AntiClockWiseHalfStep(pStepper);
        }
    }
    else
    {
        retErrorState = kFunctionParameterError;
    }
    return retErrorState;
}
error_t Stepper_Stop(StepperMotor_t * pStepper)
{
    error_t retErrorState = kNoError;
    if (pStepper != NULL)
    {
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
    }
    else
    {
        retErrorState = kFunctionParameterError;
    }
    return retErrorState;
}
