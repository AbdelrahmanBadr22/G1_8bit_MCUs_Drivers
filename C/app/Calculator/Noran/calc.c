#include "../../../common/Types.h"
#include "../../../common/Utils.h"
#include "../../../common/Config.h"
#include "../../../common/Registes.h"
#include "../../../mcal/GPIO/GPIOPrivate.h"
#include "../../../mcal/GPIO/GPIO.h"
#include "../../../hal/Keypad/Keypad_config_only_one.h"
#include "../../../hal/Keypad/Keypad_only_one.h"
#include "../../../hal/LCD/LCD_Interface.h"
#include "../../../utils/stack/stack_macros.h"
#include "../../../utils/stack/stack.h"
#include "calc.h"
void CalcInit(lcd_t* lcd, keypad_t* keypad, port_t lcdDataPort,
              port_t lcdControlPort, port_t keypadPort)
{
lcd->kLcdMode=LCD_8Bit;
lcd->kLcdDataPort=lcdDataPort;
lcd->kLcdControlPort=lcdControlPort;
lcd->kRS_PinNum=kPIN0;
lcd->kRW_PinNum=kPIN1;
lcd->kEN_PinNum=kPIN2;
keypad->Keypad_RowArr[0].port=kPORTA;
keypad->Keypad_RowArr[1].port=kPORTA;
keypad->Keypad_RowArr[2].port=kPORTA;
keypad->Keypad_RowArr[3].port=kPORTA;
keypad->Keypad_COLArr[0].port=kPORTA;
keypad->Keypad_COLArr[1].port=kPORTA;
keypad->Keypad_COLArr[2].port=kPORTA;
keypad->Keypad_COLArr[3].port=kPORTA;
keypad->Keypad_RowArr[0].pin=kPIN0;
keypad->Keypad_RowArr[1].pin=kPIN1;
keypad->Keypad_RowArr[2].pin=kPIN2;
keypad->Keypad_RowArr[3].pin=kPIN3;
keypad->Keypad_COLArr[0].pin=kPIN4;
keypad->Keypad_COLArr[1].pin=kPIN5;
keypad->Keypad_COLArr[2].pin=kPIN6;
keypad->Keypad_COLArr[3].pin=kPIN7;
LCD_Init(lcd);
Keypad_Init(keypad);
}
uint8_t ISNUM(uint8_t key)
{uint8_t state=OPERATOR;
    if (key>='0'&&key<='9')
    {
        state=NUMBER;
    }
    return state;
}
uint8_t GetPrecedence(uint8_t operator)
{uint8_t state;
    if (operator=='-'||operator=='+')
    {
        state=1;
    }
    else
    {
        state=2;
    }
    return state;
}
sint32_t Operate(sint32_t num1, sint32_t num2, char operator)
{sint32_t result=0;
    switch (operator)
    {
    case '+':
        result=num1+num2;
        break;
    case '-':
        result=num1-num2;
        break;
    case '*':
        result=num1*num2;
        break;
    case '/':
        result=num1/num2;
        break;
    }
    return result;
}
calcerror_t Evaluate(sint32_tStack_t *ar, charStack_t *arr,
                     sint16 size1, sint16 size2)
{calcerror_t error=noError;
while (size2>0)
{char operator=charStack_Pop(arr);
sint32_t num1=sint32_tStack_Pop(ar);
sint32_t num2=sint32_tStack_Pop(ar);
if (operator=='/'&&num1==0)
{
    error =runtimeError;
}
    sint32_t result=Operate(num2, num1, operator);
    sint32_tStack_Push(ar, result);
    size1--;
    size2--;
}
return error;
}
void Clear(charStack_t* operatorStack, sint32_tStack_t* numStack, lcd_t* lcd)
{
    LCD_ClearScreen(lcd);
    operatorStack->size=0;
    operatorStack->top=0;
    numStack->size=0;
    numStack->top=0;
}
