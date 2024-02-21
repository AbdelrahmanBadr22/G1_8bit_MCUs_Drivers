#include "../../../common/Types.h"
#include "../../../common/Utils.h"
#include "../../../common/Config.h"
#include "../../../common/Registes.h"
#include "../../../mcal/GPIO/GPIO.h"
#include "../../../hal/Keypad/Keypad_config_only_one.h"
#include "../../../hal/Keypad/Keypad_only_one.h"
#include "../../../hal/LCD/LCD_Interface.h"
#include "Calc.h"

void Keypad_LCD_Cfg(keypad_t * pKeypad, lcd_t * pLCD);
int main()
{
    keypad_t keypad;
    lcd_t lcd;

    Keypad_LCD_Cfg(&keypad, &lcd);
    while (1)
    {
        Calculator(&keypad, &lcd);
    }
    
}
void Keypad_LCD_Cfg(keypad_t * pKeypad, lcd_t * pLCD)
{
    pKeypad->Keypad_RowArr[0].port=kPORTC;
    pKeypad->Keypad_RowArr[1].port=kPORTC;
    pKeypad->Keypad_RowArr[2].port=kPORTC;
    pKeypad->Keypad_RowArr[3].port=kPORTC;

    pKeypad->Keypad_COLArr[0].port=kPORTC;
    pKeypad->Keypad_COLArr[1].port=kPORTC;
    pKeypad->Keypad_COLArr[2].port=kPORTC;
    pKeypad->Keypad_COLArr[3].port=kPORTC;

    pKeypad->Keypad_RowArr[0].pin=kPIN0;
    pKeypad->Keypad_RowArr[1].pin=kPIN1;
    pKeypad->Keypad_RowArr[2].pin=kPIN2;
    pKeypad->Keypad_RowArr[3].pin=kPIN3;

    pKeypad->Keypad_COLArr[0].pin=kPIN4;
    pKeypad->Keypad_COLArr[1].pin=kPIN5;
    pKeypad->Keypad_COLArr[2].pin=kPIN6;
    pKeypad->Keypad_COLArr[3].pin=kPIN7;

    Keypad_Init(pKeypad);

    pLCD->kLcdMode = LCD_8Bit;
    pLCD->kLcdDataPort = kPORTB;
    pLCD->kLcdControlPort = kPORTA;
    pLCD->kRS_PinNum = kPIN0;
    pLCD->kRW_PinNum = kPIN1;
    pLCD->kEN_PinNum = kPIN2;

    LCD_Init(pLCD);
}
