#include "Registes.h"
#include "Types.h"
#include "GPIO.h"
#include "ICU.h"
#include "Ultrasonic.h"
#include "Delay.h"
uint16 pulseWidth = 0;
//-----------------------------------------------------------------------------
//                           HELPER FUNCTIONS
//-----------------------------------------------------------------------------
static void Ultrasonic_Trigger(Ultrasonic_t * pUltrasonicConfig)
{
    GPIO_SetPinValue(pUltrasonicConfig->port, pUltrasonicConfig->triggerPin, kHigh);//IGNORE-STYLE-CHECK[L004]
    Delay_ms(0.01);
    GPIO_SetPinValue(pUltrasonicConfig->port, pUltrasonicConfig->triggerPin, kLow);//IGNORE-STYLE-CHECK[L004]
}
void Ultrasonic_ISR()
{
    static uint16 startTime =0;
    if (ICU_SelectEdge(ICU_RISING_EDGE) == kNoError)
    {
        ICU_ReadCaptureValue(&startTime);
    }
    else
    {
        ICU_ReadCaptureValue(&pulseWidth);
        pulseWidth -=startTime;
    }
}

//-----------------------------------------------------------------------------
//                           ULTRASONIC FUNCTIONS
//-----------------------------------------------------------------------------

error_t Ultrasonic_Init(Ultrasonic_t * pUSConfig)
{
    error_t kErrorState = kNoError;
    if (pUSConfig != NULL)
    {
        ICU_Init(ICU_PRESCALER_64);
        ICU_SetCallBackFunc(Ultrasonic_ISR);
        GPIO_SetPinDirection(pUSConfig ->port, pUSConfig ->triggerPin, kOutput);
        GPIO_SetPinDirection(pUSConfig ->port, pUSConfig ->echoPin, kInput);
    }
    else
    {
        kErrorState = kFunctionParameterError;
    }
    return kErrorState;
}
error_t Ultrasonic_GetDistance(Ultrasonic_t * pUSConfig, uint16 *distance)
{
    error_t kErrorState = kNoError;
    if (pUSConfig != NULL)
    {
        Ultrasonic_Trigger(pUSConfig);
        Delay_ms(100);
        *distance = (uint16)((pulseWidth*100)/58);
    }
    else
    {
        kErrorState = kFunctionParameterError;
    }
    return kErrorState;
}
