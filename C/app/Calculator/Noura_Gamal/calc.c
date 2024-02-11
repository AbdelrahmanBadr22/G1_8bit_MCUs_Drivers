#include <util/delay.h>
#include "../../../common/Types.h"
#include "../../../common/Utils.h"
#include "../../../utils/stack/stack.h"
#include "../../../mcal/GPIO/GPIO.h"
#include "../../../hal/Keypad/Keypad_config_only_one.h"
#include "../../../hal/Keypad/Keypad_only_one.h"
#include "../../../hal/LCD/LCD_Interface.h"
#include "calc.h"

sint32_t num =0, num1=0, num2=0, op = 0, flagErr = 0;
char String[] = "Error";

void CalcConf(keypad_t *pKeypad, lcd_t *pLcd)
{
    pKeypad->Keypad_RowArr[0].port = kPORTA;
    pKeypad->Keypad_RowArr[1].port = kPORTA;
    pKeypad->Keypad_RowArr[2].port = kPORTA;
    pKeypad->Keypad_RowArr[3].port = kPORTA;
    pKeypad->Keypad_COLArr[0].port = kPORTA;
    pKeypad->Keypad_COLArr[1].port = kPORTA;
    pKeypad->Keypad_COLArr[2].port = kPORTA;
    pKeypad->Keypad_COLArr[3].port = kPORTA;

    pKeypad->Keypad_RowArr[0].pin =kPIN0;
    pKeypad->Keypad_RowArr[1].pin =kPIN1;
    pKeypad->Keypad_RowArr[2].pin =kPIN2;
    pKeypad->Keypad_RowArr[3].pin =kPIN3;
    pKeypad->Keypad_COLArr[0].pin =kPIN4;
    pKeypad->Keypad_COLArr[1].pin =kPIN5;
    pKeypad->Keypad_COLArr[2].pin =kPIN6;
    pKeypad->Keypad_COLArr[3].pin =kPIN7;

    Keypad_Init(pKeypad);
    pLcd -> kLcdMode = LCD_8Bit;
    pLcd -> kLcdDataPort = kPORTC;
    pLcd -> kLcdControlPort = kPORTD;
    pLcd -> kRS_PinNum = kPIN0;
    pLcd -> kRW_PinNum = kPIN1;
    pLcd -> kEN_PinNum = kPIN2;

    LCD_Init(pLcd);
}
void Calculator(charStack_t *opStack,
                 sint32_tStack_t *numStack, lcd_t *lcd, uint8_t key)
{
    num1=0, num2=0, op = 0;
    if ((key >= '0') && (key <= '9'))
    {
        LCD_SendChar(lcd, key);
        num = (num * 10) + (key -'0');
        //first char is * or - or + or /
        if ((sint32_tStack_GetSize(numStack) == 0)&&
            charStack_GetSize(opStack) == 1)
        {
            if (charStack_GetTop(opStack) == '-')
            {
                charStack_Pop(opStack);
                num  *= -1;
            }
            else if (charStack_GetTop(opStack) == '+')
            {
                charStack_Pop(opStack);
            }
            else if ((charStack_GetTop(opStack) == '*')||
            (charStack_GetTop(opStack) == '/'))
            {
                flagErr =1;
            }
        }
    }
    else if ((key == '+') || (key == '-') || (key == '*') || (key == '/'))
    {
        LCD_SendChar(lcd, key);
        if (num!=0) //don't push 0 number
        {
            sint32_tStack_Push(numStack, num);
        }
        num =0;
        //to test more operators one after the other
        if ((charStack_GetSize(opStack) == 1)&&
            (sint32_tStack_GetSize(numStack)==1))
        {
            if (charStack_GetTop(opStack) == key)
            {
                if ((charStack_GetTop(opStack)!='*')&&
                    (charStack_GetTop(opStack)!='/'))
                {
                    if (key == '-') //5--2 or 5---2
                    {
                        charStack_Pop(opStack);
                        key = '+';
                    }
                    else if (key == '+')    //5+++2 or 5++2
                    {
                        charStack_Pop(opStack);
                    }
                }
                else
                {
                    flagErr = 1;    //5***1
                }
            }
            else if (charStack_GetTop(opStack) != key)
            {
                if ((charStack_GetTop(opStack)!='*')&&
                    (charStack_GetTop(opStack)!='/'))
                {
                    if (key == '-')     //5+-2
                    {
                       charStack_Pop(opStack);
                    }
                    else if (key == '+')    //5-+2
                    {
                        charStack_Pop(opStack);
                        key = '-';
                    }
                }
                else if ((key == '*')||(key =='/')) //5+*2
                {
                    flagErr = 1;
                }
                else if (key == '-' || key == '+')
                {
                    charStack_Push(opStack, key);
                }
            }
        }
        if (charStack_GetSize(opStack) != 0)
        {
            if (IsHigherPriority(charStack_GetTop(opStack)) //5*2+1
                            >= IsHigherPriority(key)
                &&(sint32_tStack_GetSize(numStack)>1))
            {
                num2 = sint32_tStack_Pop(numStack);
                num1 = sint32_tStack_Pop(numStack);
                op = charStack_Pop(opStack);
                if (op == '/' && num2 == 0)
                {
                    flagErr = 1;
                }
                num = Calculate(op, num1, num2);
                sint32_tStack_Push(numStack, num);
                charStack_Push(opStack, key);
            }
            else if (IsHigherPriority(charStack_GetTop(opStack))//5-2-1
                            < IsHigherPriority(key))
            {
                charStack_Push(opStack, key);
            }
            num =0;
        }
        else
        {
            charStack_Push(opStack, key);
        }
    }
    else if (key == '=')
    {
        if (num!=0) //don't push 0 number
        {
            sint32_tStack_Push(numStack, num);
        }
        num=0;
        if ((charStack_GetSize(opStack))>=(sint32_tStack_GetSize(numStack)))
        {
            if ((charStack_GetTop(opStack) == '-')&&
                (sint32_tStack_GetSize(numStack)>1))   //5*-2
            {
                charStack_Pop(opStack);
                num = sint32_tStack_Pop(numStack)*-1;
                sint32_tStack_Push(numStack, num);
            }
            else if ((charStack_GetTop(opStack) == '+')&&
                (sint32_tStack_GetSize(numStack)>1))//5*+2
            {
                charStack_Pop(opStack);
            }
            else
            {
                flagErr = 1;
            }
        }
        num =0;
        if ((charStack_GetTop(opStack)=='/')&&
            (sint32_tStack_GetTop(numStack)==0))//1/0
        {
            flagErr = 1;
        }
        if (flagErr == 1)
        {
            IsError(lcd, opStack, numStack);
        }
        else
        {
            while ((charStack_GetSize(opStack) != 0)
                && (sint32_tStack_GetSize(numStack) != 0))
            {
                num2 = sint32_tStack_Pop(numStack);
                num1 = sint32_tStack_Pop(numStack);
                op = charStack_Pop(opStack);
                if (op == '/' && num2 == 0)
                {
                    flagErr = 1;
                }
                num = Calculate(op, num1, num2);
                sint32_tStack_Push(numStack, num);
            }
            LCD_SetPosition(lcd, LCD_ROW_2, LCD_COL_1);
            LCD_SendNumber(lcd, sint32_tStack_Pop(numStack));
        }
    }
    else if (key == '&')
    {
        LCD_ClearScreen(lcd);
        key = 0;
        num = 0, num1 = 0, num2 = 0;
        flagErr = 0;
        ClearStack(opStack, numStack);
    }
}
uint8_t IsHigherPriority(uint8_t op)
{
    uint8_t flag = 0;
    if ((op == '*' || op == '/'))
    {
        flag =2;
    }
    else if ((op == '+' || op == '-'))
    {
        flag =1;
    }
    return flag;
}
sint32_t Calculate(uint8_t op, sint8_t operand1, sint8_t operand2)
{
    switch (op)
    {
    case '+':return (operand1 + operand2);
    case '-':return (operand1 - operand2);
    case '/':return (operand1 / operand2);
    case '*':return (operand1 * operand2);
    default: return 0;
    }
}
void ClearStack(charStack_t *opStack, sint32_tStack_t *numStack)
{
    opStack ->size = 0;
    opStack ->top = 0;
    numStack ->size = 0;
    numStack ->top = 0;
}
void IsError(lcd_t *lcd, charStack_t *opStack, sint32_tStack_t *numStack)
{
    LCD_SetPosition(lcd, LCD_ROW_2, LCD_COL_1);
    LCD_SendString(lcd, String);
    ClearStack(opStack, numStack);
    return;
}
