#include "Config.h"
#include "Types.h"
#include "GPIO.h"
#include "Keypad_config_only_one.h"
#include "Keypad_only_one.h"

uint8_t keypadButtons[Keypad_numberOfRows]
                     [Keypad_numberOfCols] = {{'7', '8', '9', '/'},
                                              {'4', '5', '6', '*'},
                                              {'1', '2', '3', '-'},
                                              {'C', '0', '=', '+'}

                                             };
error_t Keypad_Init(keypad_t * pKeypad)
{
    error_t retErrorState = kNoError;
    if (pKeypad != NULL)
    {
        uint8_t i;
        /*--------Set Rows Pin as Pullup Pin-------------*/
         #if MCU_TYPE == _AVR
        for (i = 0; i < Keypad_numberOfRows; i++)
        {
            GPIO_SetPinDirection(pKeypad->Keypad_RowArr[i].port,
                              pKeypad->Keypad_RowArr[i].pin,
                              kInput);

            GPIO_SetPinValue(pKeypad->Keypad_RowArr[i].port,
                             pKeypad->Keypad_RowArr[i].pin,
                             kHigh);

        }
        #elif MCU_TYPE == _PIC
        for (i = 0; i < Keypad_numberOfRows; i++)
        {
            GPIO_SetPinDirection(pKeypad->Keypad_RowArr[i].port,
                              pKeypad->Keypad_RowArr[i].pin, kInput);
        }
        #endif
        /*--------Set Columns Pin as Output Pin---------*/
        for (i = 0; i < Keypad_numberOfCols; i++)
        {
            GPIO_SetPinDirection(pKeypad->Keypad_COLArr[i].port,
                                 pKeypad->Keypad_COLArr[i].pin,
                                 kOutput);
        }
        /*--------Set Columns Pin as High---------------*/
        for (i = 0; i < Keypad_numberOfCols; i++)
        {
            GPIO_SetPinValue(pKeypad->Keypad_COLArr[i].port,
                             pKeypad->Keypad_COLArr[i].pin,
                             kHigh);
        }
        
        
    }else
    {
        retErrorState = kFunctionParameterError;
    }
    return retErrorState;
}
uint8_t Keypad_GetPressedButton(keypad_t * pKeypad)
{
    uint8_t retValueButton = NOT_PRESSED;
    uint8_t rowCount;
    uint8_t colCount;
    state_t buttonValue;
    state_t buttonIsPressed = kLow;
    for (colCount = 0; colCount<Keypad_numberOfCols; colCount++)
    {
        GPIO_SetPinValue(pKeypad->Keypad_COLArr[colCount].port,
                         pKeypad->Keypad_COLArr[colCount].pin,
                         kLow);
        for (rowCount = 0; rowCount < Keypad_numberOfRows; rowCount++)
        {
            GPIO_GetPinValue(pKeypad->Keypad_RowArr[rowCount].port,
                             pKeypad->Keypad_RowArr[rowCount].pin,
                             &buttonValue);
            if (buttonValue == buttonIsPressed)
            {
                retValueButton = keypadButtons[rowCount][colCount];
            while (buttonValue == buttonIsPressed)
            {
                GPIO_GetPinValue(pKeypad->Keypad_RowArr[rowCount].port,
                                 pKeypad->Keypad_RowArr[rowCount].pin,
                                 &buttonValue);
            }
            return retValueButton;
            }
        }
        GPIO_SetPinValue(pKeypad->Keypad_COLArr[colCount].port,
                         pKeypad->Keypad_COLArr[colCount].pin,
                         kHigh);
    }
    return retValueButton;
}
