#include "../../common/Types.h"
#include "../../mcal/GPIO/GPIO.h"
#include "StepperMotor.h"

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
void Stepper_ClockWise(StepperMotor_t* pStepper, uint8_t type, uint8_t degree)
{
    uint8_t iterator=0;
    if (type==STEPPER_FULLSTEP)
    {
        uint8_t numOfIterations=((degree*256)/45)/4;
        for (iterator=0;iterator<numOfIterations;iterator++)
        {
            ClockWiseFullStep(pStepper);
        }
    }
    else if (type==STEPPER_HALFSTEP)
    {
        uint8_t numOfIterations=((degree*512)/45)/4;
        for (iterator=0;iterator<numOfIterations;iterator++)
        {
            ClockWiseHalfStep(pStepper);
        }
    }
}
void Stepper_AntiClockWise(StepperMotor_t* pStepper,
                           uint8_t type, uint8_t degree)
{
    uint8_t iterator=0;
    if (type==STEPPER_FULLSTEP)
    {
        uint8_t numOfIterations=((degree*256)/45)/4;
        for (iterator=0;iterator<numOfIterations;iterator++)
        {
            AntiClockWiseFullStep(pStepper);
        }
    }
    else if (type==STEPPER_HALFSTEP)
    {
        uint8_t numOfIterations=((degree*512)/45)/4;
        for (iterator=0;iterator<numOfIterations;iterator++)
        {
            AntiClockWiseHalfStep(pStepper);
        }
    }
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
void ClockWiseFullStep(StepperMotor_t * pStepper)
{
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
        //delay
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
        //delay
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
        //delay
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kHigh);

}
void AntiClockWiseFullStep(StepperMotor_t * pStepper)
{
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kHigh);
        //delay
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
        //delay
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
        //delay
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
}
void ClockWiseHalfStep(StepperMotor_t * pStepper)
{
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
        //delay
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
        //delay
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
        //delay
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
        //delay
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
        //delay
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kHigh);
        //delay
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kHigh);
        //delay
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kHigh);
}
void AntiClockWiseHalfStep(StepperMotor_t * pStepper)
{
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kHigh);
        //delay
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kHigh);
        //delay
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kHigh);
        //delay
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
        //delay
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
        //delay
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
        //delay
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
        //delay
        GPIO_SetPinValue(pStepper->port, pStepper->bluePin, kHigh);
        GPIO_SetPinValue(pStepper->port, pStepper->pinkPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->yellowPin, kLow);
        GPIO_SetPinValue(pStepper->port, pStepper->orangePin, kLow);
}
