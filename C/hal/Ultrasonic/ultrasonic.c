#if MCU_TYPE == _AVR
#include <util/delay.h>
#endif
#include "../../common/Types.h"
#include "../../mcal/GPIO/GPIO.h"
#include "../../mcal/TIMER/TIMER_Interface.h"
#include "../../mcal/EXTI/EXTI_Interface.h"
#include "ultrasonic.h"

error_t UltrasonicInit(Ultrasonic_t* pUS, uint8_t kMode, uint8_t kClock, uint8_t kInterruptSource)
{
    error_t retErrorState = kNoError;
    if (pUS != NULL)
    {
        GPIO_SetPinDirection(pUS->port, pUS->triggerPin, kOutput);
        GPIO_SetPinDirection(pUS->port, pUS->echoPin, kInput);
        TIMER1_Init(kMode, kClock);
        EXTI_InterruptEnable(kInterruptSource);
    }
    else
    {
        retErrorState = kNoError;
    }
    return retErrorState;
}
error_t UltrasonicTrigger(Ultrasonic_t * pUS)
{
    error_t retErrorState = kNoError;
    if (pUS != NULL)
    {
        GPIO_SetPinValue(pUS->port, pUS->triggerPin, kHigh);
        #if MCU_TYPE == _AVR
        _delay_us(10);
        #endif
        GPIO_SetPinValue(pUS->port, pUS->triggerPin, kLow);
    }
    else
    {
        retErrorState = kNoError;
    }
    return retErrorState;
}
