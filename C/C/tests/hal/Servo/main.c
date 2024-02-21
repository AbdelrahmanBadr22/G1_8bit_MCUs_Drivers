#include "common/Types.h"
#include "common/Utils.h"
#include "common/Config.h"
#include "common/Registes.h"
#include "hal/Servo/Servo.h"
#include <util/delay.h>
int main()
{
	Servo_Init(SERVO_OC1B_PIN);

	while (1)
	{
		for (int i = 0; i <= 180 ; i+=10)
		{
			Servo_SetAngle(i, SERVO_OC1B_PIN);
			Delay_ms(500);
		}
		for (int i = 180; i >= 0 ; i-=10)
		{
			Servo_SetAngle(i, SERVO_OC1B_PIN);
			Delay_ms(500);
		}
	}
}
