#include "common/Types.h"
#include "common/Utils.h"
#include "common/Config.h"
#include "common/Registes.h"
#include "utils/delay/Delay.h"
#include "mcal/WDT/WDT.h"
#include "mcal/GPIO/GPIO.h"
#include "hal/LED/LED.h"
#include <util/delay.h>
int main()
{
	LED_t led={kPORTB, kPIN0, kLedActiveHigh};
	LED_t led2={kPORTB, kPIN1, kLedActiveHigh};

	LED_Init(&led);
	LED_Init(&led2);
	WDT_SetTimeOut(WDT_1s0);
	WDT_Enable();
	while (1)
	{
		LED_TurnOn(&led);
        _delay_ms(1000);
        WDT_Disable();
		LED_TurnOn(&led2);
		LED_TurnOff(&led);
	}
}
