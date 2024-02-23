#include "Config.h"
#include "Registes.h"
#include "Types.h"
#include "GPIO.h"
#include "ICU.h"
#include "Ultrasonic.h"
#include "Delay.h"
#include "GIC_Interface.h"
#if IS_AVR()
#include <util/delay.h>
#endif
static uint16 t1 =0, t2=0;
static uint8_t flag = 0, Capflag=0;
//-----------------------------------------------------------------------------
//                           HELPER FUNCTIONS
//-----------------------------------------------------------------------------
static void Ultrasonic_Trigger(Ultrasonic_t * pUltrasonicConfig)
{
    GPIO_SetPinValue(pUltrasonicConfig->port, pUltrasonicConfig->triggerPin, kHigh);//IGNORE-STYLE-CHECK[L004]
    #if IS_AVR()
    _delay_us(10);
    #endif
    GPIO_SetPinValue(pUltrasonicConfig->port, pUltrasonicConfig->triggerPin, kLow);//IGNORE-STYLE-CHECK[L004]
}
void Ultrasonic_ISR()
{
    if (flag == 0)
    {
        ICU_ReadCaptureValue(&t1);
        flag = 1;
        ICU_SelectEdge(ICU_FALLING_EDGE);
    }
    else if (flag == 1)
    {
        ICU_ReadCaptureValue(&t2);
        Capflag=1;
       // ICU_Disable();
        flag =0;
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
        GPIO_SetPinDirection(pUSConfig ->port, pUSConfig ->triggerPin, kOutput);
        GPIO_SetPinDirection(pUSConfig ->port, pUSConfig ->echoPin, kInput);
        ICU_SelectEdge(ICU_RISING_EDGE);
        ICU_SetCallBackFunc(Ultrasonic_ISR);
        GIC_voidGlobalInterruptControl(GLOBAL_INTERRUPT_ENABLE);
    }
    else
    {
        kErrorState = kFunctionParameterError;
    }
    return kErrorState;
}
float  Ultrasonic_GetDistance(Ultrasonic_t * pUSConfig)
{
    ICU_Init(ICU_PRESCALER_1);
    Ultrasonic_Trigger(pUSConfig);
    float distance = 0;
    if (Capflag==1)
    {
    uint16 ticks=t2-t1;
    distance = (ticks*(1.0/8000000));
    distance = distance*34300/2;
    Capflag=0;
    ICU_SelectEdge(ICU_RISING_EDGE);
    }
   // *distance = (uint16)((pulseWidth*100)/58);
    return distance;
}
