#include <util/delay.h>
#include "common/Types.h"
#include "common/Utils.h"
#include "mcal/GPIO/GPIO.h"

void Test_SetPinDirection_SetPinValue();
void Test_SetPortDirection_SetPortValue();
void Test_GetPinValue();
void Test_GetPortValue();

int main(void)
{

    while (1)
    {
        Test_SetPinDirection_SetPinValue();
        Test_SetPortDirection_SetPortValue();
        Test_GetPinValue();
        Test_GetPortValue();
    }
}

void Test_SetPinDirection_SetPinValue()
{
    GPIO_SetPinDirection(kPORTA, kPIN0, kOutput);

    GPIO_SetPinValue(kPORTA, kPIN0, kHigh);
    Delay_ms(500);
    GPIO_SetPinValue(kPORTA, kPIN0,  kLow);
    Delay_ms(500);
    
}
void Test_SetPortDirection_SetPortValue()
{
    GPIO_SetPortDirection(kPORTB, 1);

    GPIO_SetPortValue(kPORTB, 1);
    Delay_ms(500);
    GPIO_SetPortValue(kPORTB, 0);
    Delay_ms(500);
}
void Test_GetPinValue()
{
    GPIO_SetPinDirection(kPORTA, kPIN1, kInput);
    GPIO_SetPinDirection(kPORTA, kPIN2, kOutput);
    state_t pinState;
    GPIO_GetPinValue(kPORTA, kPIN1, &pinState);
    if (pinState==kHigh)
    {
        GPIO_SetPinValue(kPORTA, kPIN2, kHigh);
        Delay_ms(500);
        GPIO_SetPinValue(kPORTA, kPIN2, kLow);
        Delay_ms(500);
    }
}
void Test_GetPortValue()
{
    GPIO_SetPortDirection(kPORTC, 0);
    GPIO_SetPinDirection(kPORTA, kPIN3, kOutput);
    uint8_t portState;
    GPIO_GetPortValue(kPORTC, &portState);
   if (portState==0xff)
    {
        GPIO_SetPinValue(kPORTA, kPIN3, kHigh);
        Delay_ms(500);
        GPIO_SetPinValue(kPORTA, kPIN3, kLow);
        Delay_ms(500);
    }
}
