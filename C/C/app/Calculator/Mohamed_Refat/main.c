/**
 * @file main.c
 * @author Mohamed Refat
 * @brief
 * @version 0.1
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <util/delay.h>
#include "../../../common/Types.h"
#include "../../../common/Utils.h"
#include "../../../common/Config.h"
#include "../../mcal/GPIO/GPIO.h"
#include "../../../hal/LCD/LCD_Interface.h"
#include "../../../hal/Keypad/Keypad_config_only_one.h"
#include "../../../hal/Keypad/Keypad_only_one.h"
#include "Calculator.h"

int main()
{
    lcd_t lcd;
    keypad_t keyPad;
	APP_INIT(&lcd, &keyPad);
	while (1)
	{
		Run_Calculator(&lcd, &keyPad);
	}

}
