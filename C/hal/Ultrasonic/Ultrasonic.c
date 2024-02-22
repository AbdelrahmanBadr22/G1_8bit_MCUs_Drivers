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
static uint8_t flag = 0;
//-----------------------------------------------------------------------------
//                           HELPER FUNCTIONS
//-----------------------------------------------------------------------------
static void Ultrasonic_Trigger(Ultrasonic_t * pUltrasonicConfig)
{
    GPIO_SetPinValue(pUltrasonicConfig->port, pUltrasonicConfig->triggerPin, kHigh);//IGNORE-STYLE-CHECK[L004]
    #if IS_AVR()
    _delay_us(1000);
    #endif
    GPIO_SetPinValue(pUltrasonicConfig->port, pUltrasonicConfig->triggerPin, kLow);//IGNORE-STYLE-CHECK[L004]
}
void Ultrasonic_ISR()
{
    if (flag == 0)
    {
        ICU_ReadCaptureValue(&t1);
        flag = 1;
       // GPIO_SetPinValue(kPORTD,kPIN0,0);
        ICU_SelectEdge(ICU_FALLING_EDGE);
    }
    else if (flag == 1)
    {
        ICU_ReadCaptureValue(&t2);
        ICU_Disable();
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
         GIC_voidGlobalInterruptControl(GLOBAL_INTERRUPT_ENABLE);
        ICU_SelectEdge(ICU_RISING_EDGE);
    }
    else
    {
        kErrorState = kFunctionParameterError;
    }
    return kErrorState;
}
float  Ultrasonic_GetDistance(Ultrasonic_t * pUSConfig)
{
    float distance = 0;
    Ultrasonic_Trigger(pUSConfig);
    ICU_SetCallBackFunc(Ultrasonic_ISR);
     ICU_Init(ICU_PRESCALER_64);
      #if IS_AVR()
    _delay_us(1000);
    #endif
    distance = (t2 - t1)*4/125;
    distance = (distance /2)* 343/1000;
   // *distance = (uint16)((pulseWidth*100)/58);
    return distance;
}
