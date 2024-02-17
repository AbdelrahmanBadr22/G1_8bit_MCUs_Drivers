#include <util/delay.h>
#include "common/Types.h"
#include "common/Utils.h"
#include "hal/LCD/LCD_Interface.h"
#include "hal/LCD/LCD_CustomChar.h"


void Test_SendString(lcd_t _LCD);
void Test_SendSNumber_SendFloat(lcd_t _LCD);
void Test_SetPosition(lcd_t _LCD);
void Test_ShiftRight_ShiftLeft(lcd_t _LCD);
void Test_CursorEnable_CursorDisable(lcd_t _LCD);
void Test_DisplayOn_DisplayOff(lcd_t _LCD);
void Test_BlinkOn_BlinkOff(lcd_t _LCD);
void Test_CustoCharacter(lcd_t _LCD);


int main()
{
    lcd_t _LCD =
        {LCD_4Bit, kPORTD, kPORTA, kPIN0, kPIN1, kPIN2, LCD_HIGH_NIBBLE };
    LCD_Init(&_LCD);
    while (1)
    {
        Test_SendString(_LCD);
        Test_SendSNumber_SendFloat(_LCD);
        Test_SetPosition(_LCD);
        Test_ShiftRight_ShiftLeft(_LCD);
        Test_CursorEnable_CursorDisable(_LCD);
        Test_DisplayOn_DisplayOff(_LCD);
        Test_BlinkOn_BlinkOff(_LCD);
        Test_CustoCharacter(_LCD);
        
    }
}
void Test_SendString(lcd_t _LCD)
{
    uint8_t str[30]={"MOHAMED REFAT"};
    LCD_SendString(&_LCD, str);
    Delay_ms(2500);
    LCD_ClearScreen(&_LCD);
}
void Test_SendSNumber_SendFloat(lcd_t _LCD)
{
    LCD_SendFloat(&_LCD, 79.9);
    Delay_ms(2500);
    LCD_ClearScreen(&_LCD);
    LCD_SendNumber(&_LCD, 80);
    Delay_ms(2500);
    LCD_ClearScreen(&_LCD);

}
void Test_SetPosition(lcd_t _LCD)
{
    uint8_t str[30]={"MOHAMED REFAT"};
    LCD_SetPosition(&_LCD, LCD_ROW_2, LCD_COL_3);
    LCD_SendString(&_LCD, str);
    Delay_ms(2500);
    LCD_ClearScreen(&_LCD);
}
void Test_ShiftRight_ShiftLeft(lcd_t _LCD)
{
    uint8_t str1[30]={"TEST SHIFT"};
    LCD_SendString(&_LCD, str1);
    LCD_ShiftRight(&_LCD);
    LCD_ShiftRight(&_LCD);
    Delay_ms(2500);
    LCD_ShiftLeft(&_LCD);
    LCD_ShiftLeft(&_LCD);
    Delay_ms(2500);
    LCD_ClearScreen(&_LCD);
    
}
void Test_CursorEnable_CursorDisable(lcd_t _LCD)
{
uint8_t str[30]={"TEST CURSOR"};
    LCD_SendString(&_LCD, str);
    LCD_EnableCursor(&_LCD);
    Delay_ms(2500);
    LCD_DisableCursor(&_LCD);
    Delay_ms(2500);
    LCD_ClearScreen(&_LCD);
    
}
void Test_DisplayOn_DisplayOff(lcd_t _LCD)
{
    uint8_t str[30]={"DISPLAY ON/OFF"};
    LCD_SendString(&_LCD, str);
    Delay_ms(1000);
    LCD_Display_Off(&_LCD);
    Delay_ms(2500);
    LCD_Display_On(&_LCD);
    Delay_ms(2500);
    LCD_ClearScreen(&_LCD);
}
void Test_BlinkOn_BlinkOff(lcd_t _LCD)
{
    uint8_t str[30]={"BLINK ON/OFF"};
    LCD_SendString(&_LCD, str);
    LCD_Blink_On(&_LCD);
    Delay_ms(2500);
    LCD_Blink_Off(&_LCD);
    Delay_ms(2500);
    LCD_DisableCursor(&_LCD);
    LCD_ClearScreen(&_LCD);

}
void Test_CustoCharacter(lcd_t _LCD)
{
    uint8_t heart[8] = {HEART};
    uint8_t skull[8] = {SKULL};

    LCD_SetPosition(&_LCD, LCD_ROW_1, LCD_COL_3);
    uint8_t str[30]={"CUSTOM CHARR"};
    LCD_SendString(&_LCD, str);
    LCD_StoreCustomChar(&_LCD, heart, 5);
    LCD_StoreCustomChar(&_LCD, skull, 0);
    LCD_SendCustomChar(&_LCD, 5, LCD_ROW_2, LCD_COL_8);
    LCD_SendCustomChar(&_LCD, 0, LCD_ROW_2, LCD_COL_9);
    Delay_ms(3000);
    LCD_ClearScreen(&_LCD);
}
