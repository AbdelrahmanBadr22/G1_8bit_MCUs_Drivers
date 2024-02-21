#include "../../../common/Types.h"
#include "../../../common/Utils.h"
#include "../../../common/Config.h"
#include "../../../common/Registes.h"
#include "../../../mcal/GPIO/GPIO.h"
#include "../../../hal/Keypad/Keypad_config_only_one.h"
#include "../../../hal/Keypad/Keypad_only_one.h"
#include "../../../hal/LCD/LCD_Interface.h"
#include "../../../utils/stack/stack.h"
#include "Calc_private.h"
#include "Calc.h"

error_t Calculator(keypad_t * pKeypad, lcd_t * pLCD)
{
    error_t retErrorState = kNoERROR;
    if (pKeypad != NULL_PTR && pLCD != NULL_PTR)
    {
        uint8_t inputChar;
        uint8_t preInputChar = NOT;
        uint8_t negativeFlag=0;
        f32_t inputNum=0;
        f32_t result;
        f32_tStack_t numStack;
        charStack_t opStack;
        f32_tStack_Init(&numStack);
        charStack_Init(&opStack);
        calc_error_terror= kNoERROR;
        while (1)
        {
            inputChar = Input(pKeypad);
            if (inputChar != NOT_PRESSED)
            {
                Output(pLCD, inputChar);
                if (inputChar >= '0' && inputChar <= '9')
                {
                    inputNum = inputNum *10 +(inputChar - '0');
                    if (negativeFlag == 1)
                    {
                        inputNum *=-1;
                        negativeFlag = 0;
                    }
                }
                else if (inputChar == '.')
                {
                    // later
                }
                else if (inputChar == '=')
                {
                    if (IsOp(preInputChar) == kTRUE)
                    {
                        DisplayERROR(pLCD, kSYNTAX_ERROR);
                    }
                    else
                    {
                        f32_tStack_Push(&numStack, inputNum);
                       error= IsEqual(&opStack, &numStack, &result);
                        if (Error != kNoERROR)
                        {
                            DisplayERROR(pLCD, kMATH_ERROR);
                        }
                        else
                        {
                            DisplayResult(pLCD, result);
                        }
                    }
                }
                else if (inputChar == 'C')
                {
                    LCD_ClearScreen(pLCD);
                    f32_tStack_Clear(&numStack);
                    charStack_Clear(&opStack);
                    inputNum=0;
                    inputChar=NOT;
                    preInputChar=NOT;
                }
                else
                {
                    if ((IsOp(preInputChar) == kTRUE
                              && IsOp(inputChar) == kTRUE)
                        || (preInputChar == NOT))
                    {
                        if (inputChar == '*' || inputChar == '/')
                        {
                            DisplayERROR(pLCD, kSYNTAX_ERROR);
                        }
                        else if (inputChar == '+')
                        {
                        }
                        else if (inputChar == '-')
                        {
                            negativeFlag ^= 1;
                        }
                    }
                    else
                    {
                        f32_tStack_Push(&numStack, inputNum);
                        inputNum=0;
                       error= PushOp(&opStack, &numStack, inputChar);
                        if (Error != kNoERROR)
                        {
                            DisplayERROR(pLCD, kMATH_ERROR);
                        }
                    }
                }
                preInputChar = inputChar;
            }
        }
    }
    else
    {
        retErrorState = kFunctionParameterError;
    }
    return retErrorState;
}
uint8_t Input(keypad_t * pKeypad)
{
    uint8_t input=NOT_PRESSED;
    input = Keypad_GetPressedButton(pKeypad);
    return input;
}
void Output(lcd_t * pLCD, uint8_t outputChar)
{
    if (outputChar != '=')
    {
    LCD_SendChar(pLCD, outputChar);
    }
}
calc_error_t Evaluate(f32_t num1, f32_t num2, uint8_t op, f32_t * result)
{
    calc_error_t retErrorState = kNoERROR;
    if (op == '/' && num2 == 0)
    {
        retErrorState = kMATH_ERROR;
    }
    else
    {
        switch (op)
        {
        case '+': *result = num1 + num2; break;
        case '-': *result = num1 - num2; break;
        case '*': *result = num1 * num2; break;
        case '/': *result = num1 / num2; break;
        }
    }
    return retErrorState;
}
uint8_t Priority(char op)
{
    f32_t retVal=0;
    switch (op)
    {
        case '+':
        case '-': retVal = 1;
        break;
        case '*':
        case '/': retVal = 2;
        break;
    }
    return retVal;
}
calc_error_t PushOp(charStack_t * opStack, f32_tStack_t * numStack, uint8_t op)
{
    f32_t num1, num2, result=0;
    calc_error_t retErrorState = kNoERROR;
    if (charStack_GetSize(opStack) == 0)
    {
        charStack_Push(opStack, op);
    }
    else
    {
        if (Priority(op) > Priority(charStack_GetTop(opStack)))
        {
            charStack_Push(opStack, op);
        }
        else
        {
            while (Priority(op) <= Priority(charStack_GetTop(opStack)))
            {
            num2 = f32_tStack_GetTop(numStack);
            f32_tStack_Pop(numStack);
            num1 = f32_tStack_GetTop(numStack);
            f32_tStack_Pop(numStack);
            retErrorState = Evaluate(num1, num2,
                                     charStack_GetTop(opStack),
                                     &result);
            f32_tStack_Push (numStack, result);
            charStack_Pop(opStack);
            }
            charStack_Push(opStack, op);
        }
    }
    return retErrorState;
}
calc_error_t  IsEqual(charStack_t * opStack,
                      f32_tStack_t * numStack,
                      f32_t * result)
{
    f32_t num1, num2;
    calc_error_t retErrorState = kNoERROR;
    while (charStack_GetSize(opStack) != 0)
    {
        num1=0;
        num2=0;
        num2 = f32_tStack_GetTop(numStack);
        f32_tStack_Pop(numStack);
        num1 = f32_tStack_GetTop(numStack);
        f32_tStack_Pop(numStack);
        retErrorState = Evaluate(num1, num2, charStack_GetTop(opStack), result);
        f32_tStack_Push (numStack, *result);
        charStack_Pop(opStack);
    }
    *result = f32_tStack_GetTop(numStack);
    return retErrorState;
}
void DisplayResult(lcd_t  * pLCD, f32_t result)
{
    LCD_SetPosition(pLCD, LCD_ROW_2, LCD_COL_1);
    LCD_SendChar(pLCD, '=');
    LCD_SendFloat(pLCD, result);
}
bool_t IsOp(uint8_t ch)
{
    bool_t retValue = kFALSE;
    if (ch =='+' || ch =='-' ||
        ch =='*' || ch =='/')
    {
        retValue = kTRUE;
    }
    return retValue;
}
void DisplayERROR(lcd_t  * pLCD, calc_error_t error)
{
    if (error == kSYNTAX_ERROR)
    {
        LCD_SetPosition(pLCD, LCD_ROW_2, LCD_COL_5);
        LCD_SendString(pLCD, "Syntax ERROR");
    }
    else if (error == kMATH_ERROR)
    {
        LCD_SetPosition(pLCD, LCD_ROW_2, LCD_COL_7);
        LCD_SendString(pLCD, "Math ERROR");
    }
}
