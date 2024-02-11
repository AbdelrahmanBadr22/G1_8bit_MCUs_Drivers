#include "../../../common/Types.h"
#include "GPIO.h"
#include "../../../hal/LCD/LCD_Interface.h"
#include "../../../hal/Keypad/Keypad_config_only_one.h"
#include "../../../hal/Keypad/Keypad_only_one.h"

#include "Calculator.h"
#include "Linked_Stack.h"

#define STR_RESULT  ("Result = ")
#define STR_SYNTAX_ERROR "Syntax Error "
#define STR_MATH_ERROR "Math Error"

void APP_INIT(lcd_t *pLCD, keypad_t *pkeyPad)
{

	pLCD->kLcdMode =  LCD_4Bit;
	pLCD->kLcdDataPort = kPORTC;
	pLCD->kLcdControlPort = kPORTA;
	pLCD->kRS_PinNum = kPIN0;
	pLCD->kRW_PinNum = kPIN1;
	pLCD->kEN_PinNum = kPIN2;
	pLCD->kLcd_4bitDataPin = LCD_HIGH_NIBBLE;


    keypadPin_t row1 = {kPORTD, kPIN0};
    keypadPin_t row2 = {kPORTD, kPIN1};
    keypadPin_t row3 = {kPORTD, kPIN2};
    keypadPin_t row4 = {kPORTD, kPIN3};
    keypadPin_t col1 = {kPORTD, kPIN4};
    keypadPin_t col2 = {kPORTD, kPIN5};
    keypadPin_t col3 = {kPORTD, kPIN6};
    keypadPin_t col4 = {kPORTD, kPIN7};

    pkeyPad->Keypad_RowArr[0] = row1;
    pkeyPad->Keypad_RowArr[1] = row2;
    pkeyPad->Keypad_RowArr[2] = row3;
    pkeyPad->Keypad_RowArr[3] = row4;
    pkeyPad->Keypad_COLArr[0] = col1;
    pkeyPad->Keypad_COLArr[1] = col2;
    pkeyPad->Keypad_COLArr[2] = col3;
    pkeyPad->Keypad_COLArr[3] = col4;
	LCD_Init(pLCD);
	Keypad_Init(pkeyPad);

}
void Run_Calculator(lcd_t *pLCD, keypad_t *pkeyPad)
{

	Calc_Error_t kErrorState = NoError;
	uint8_t infixExp[EXPRESSION_SIZE]={};
    uint8_t postfixExp[EXPRESSION_SIZE]={};

	uint8_t iterator = 0;
	f32_t result;
	static uint8_t kPressedValue = NOT_PRESSED;

	/* Take The infix expression From the user */
	while (iterator < EXPRESSION_SIZE )
	{
		/* Wait until the keypad is pressed */
		while (kPressedValue == NOT_PRESSED)
		{
			kPressedValue = Keypad_GetPressedButton(pkeyPad);
		}
		/* Case entered value is Number or operator not = or C 'Terminate' */
		if (kPressedValue != '=' && kPressedValue != 'C')
		{
			LCD_SendChar(pLCD, kPressedValue);
			infixExp[iterator++] = kPressedValue;
			kPressedValue = NOT_PRESSED;
		}
		/* Case entered value is  = or C 'Terminate' */
		else
		{
			break;
		}
	}
	/* Print Result */
	if ( kPressedValue == '=' )
	{
		kErrorState = GetPostfixExp(infixExp, postfixExp);
    	kErrorState = EvaluatePostfixExp(postfixExp, &result, kErrorState);
		LCD_SetPosition(pLCD, LCD_ROW_2, LCD_COL_1);
		/* iterator == 0 --> to handle case  that the  user doesn't
			entered eny expression but he entered '='
			so the previous result will appear
		*/
		if ( (kErrorState == NoError || iterator == 0 ) )
		{
			LCD_SendString(pLCD, STR_RESULT);
			LCD_SendFloat(pLCD, result);
		}else if (kErrorState == SyntaxError)
		{
			LCD_SendString(pLCD, STR_SYNTAX_ERROR);
		}else if ( kErrorState == DivideByZero )
		{
			LCD_SendString(pLCD, STR_MATH_ERROR);
		}
	}
	/* After user enter '=' or 'C' wait until he entered
		new value to start again */
	kPressedValue = Keypad_GetPressedButton(pkeyPad);
	while (kPressedValue == NOT_PRESSED)
	{
		kPressedValue = Keypad_GetPressedButton(pkeyPad);
	}
	LCD_ClearScreen(pLCD);

}

Calc_Error_t GetPostfixExp(uint8_t pInfixExp[], uint8_t pPostfixExp[])
{
	Calc_Error_t kErrorState = kNoError;
    Stack_t Calc_stack;                 //IGNORE-STYLE-CHECK[B004]
    int iterator1 = 0;
    int iterator2 = 0;
    LinkedStack_creatStack(&Calc_stack);
    SeparateExp(pInfixExp);

    /**
     * Handle Case if the used enter a sign '+' or '-' before the first number.
     *
     * assume the Expression : "-5+3"
     *  after we call SeparateExp function the expression will be : " - 5 + 3"
     *  so we check index number 1 instead of 0.
     *
     * iterator = 2 --> to skip the first sign at the infix expression
     *  so the expression be like " 5 + 3"
     *
     */
    if (pInfixExp[1] == '+')
    {
    	iterator1 = 2;
    }else if (pInfixExp[1] == '-')
    {
    	kErrorState = _1stNumIsNeg;
    	iterator1 = 2;
    }
    while (pInfixExp[iterator1] != '\0')
    {
    	/* Case value is Number --> add it to the Post fix expression
            also if there is a negative number
        */
        if (  (  pInfixExp[iterator1] == '-' &&
                IsNumber(pInfixExp[iterator1+1]) == kTRUE  )||
        		IsOperator(pInfixExp[iterator1]) == kFALSE )
        {

            pPostfixExp[iterator2++] = pInfixExp[iterator1];
        }
        /* case value is operator  */
        else if ( IsOperator(pInfixExp[iterator1]) == kTRUE)
        {
            if ( LinkedStack_IsEmpty(&Calc_stack)   )
            {
                LinkedStack_Push(&Calc_stack, pInfixExp[iterator1]);

            }
            /**
             *  Case operator is a Low Priority operator [ + , - ]
             *    Pop all the operator from the stack.
             */
            else if ( IsHighPriority((pInfixExp[iterator1])) == kFALSE )
            {
                while ( LinkedStack_IsEmpty(&Calc_stack) == kFALSE)
                {
                    pPostfixExp[iterator2++] =
                                        (uint8_t)LinkedStack_Pop(&Calc_stack);
                }
                LinkedStack_Push(&Calc_stack, pInfixExp[iterator1]);
            }
            /**
             *  Case operator is a High Priority operator [ * , / ]
             *    Pop only high priority operator from the stack.
             */
            else
            {
                while ( LinkedStack_IsEmpty(&Calc_stack) == kFALSE &&
                        IsHighPriority( LinkedStack_GetTop(&Calc_stack) ))
                {
                    pPostfixExp[iterator2++] =
                                        (uint8_t)LinkedStack_Pop(&Calc_stack);
                }
                LinkedStack_Push(&Calc_stack, pInfixExp[iterator1]);
            }
        }
        iterator1++;
    }
    /**
     * Popping all the operators that remain in the stack
     */
    while ( LinkedStack_IsEmpty(&Calc_stack) == kFALSE )
    {
            pPostfixExp[iterator2++] = (uint8_t)LinkedStack_Pop(&Calc_stack);
    }
    return kErrorState;
}

Calc_Error_t EvaluatePostfixExp(uint8_t pPostfixExp[],
                                f32_t *pResult, Calc_Error_t postfixState)
{
	Calc_Error_t retErrorState  = kNoError;
	Stack_t Calc_stack;     //IGNORE-STYLE-CHECK[B004]
    uint16 iterator1 = 0;
    uint16 iterator2 = 0;
    uint8_t arrNum[6]={};
    bool_t negFlag = kFALSE;
    f32_t operand1 = 0;
    f32_t operand2 = 0;
    f32_t result = 0;
    bool_t negativeOperandFlag = kFALSE;
    /* Handle case if the first number of the expression is Negative */
    if (postfixState == _1stNumIsNeg)
    {
    	negFlag = kTRUE;
    }

    /* Creat the stack  */
    LinkedStack_creatStack(&Calc_stack);

    while ( pPostfixExp[iterator1] != '\0')
    {
        sint32_t kNum = 0;

        /* Case there is a negative number */
        if (pPostfixExp[iterator1] == '-' &&
            IsNumber(pPostfixExp[iterator1+1]) == kTRUE)
        {
            negativeOperandFlag = kTRUE;
            iterator1++;
        }
        if (IsNumber( pPostfixExp[iterator1] ) )
        {
            /**
             * case the number is a  multi digit number
             *  add all the number digit to the arrNum
             */
            while ( IsNumber( pPostfixExp[iterator1] ))
            {
                arrNum[iterator2++] = pPostfixExp[iterator1];
                iterator1++;
            }
            /**
             * convert the number form string form to a decimal'integer' form
             *   by using ConvertStringToInteger() function.
             * Example:
             *  arrNum = "5413"string
             *  after calling the function
             *  kNum = (5413)decimal
             */
            kNum = ConvertStringToInteger(arrNum, iterator2);

            if (negativeOperandFlag == kTRUE )
            {
                kNum *= -1;
                negativeOperandFlag = kFALSE;
            }
            iterator2 = 0;
            LinkedStack_Push(&Calc_stack, kNum);

        }else if ( IsOperator(pPostfixExp[iterator1]))
        {

            operand2 = LinkedStack_Pop(&Calc_stack);
            operand1 = LinkedStack_Pop(&Calc_stack);

            if (negFlag == kTRUE)
            {
            	operand1 *= -1.0;
            	negFlag = kFALSE;
            }
            if (operand2 == 0 && pPostfixExp[iterator1] == '/')
            {
            	retErrorState = DivideByZero;
            	break;
            }
            result = GetResult(operand1, operand2, pPostfixExp[iterator1]);
            LinkedStack_Push(&Calc_stack, result);
            iterator1++;
        }else
        {
            iterator1++;
        }
    }
    if (LinkedStack_GetSize(&Calc_stack) == 1)
    {

    	*pResult = LinkedStack_Pop(&Calc_stack);
    	/*Case if the user enter only one negative number */
    	if ( negFlag == kTRUE)
    	{
    		*pResult *= -1;
    	}

    }else if (retErrorState != DivideByZero )
    {
    	retErrorState  = SyntaxError;
    }
    return retErrorState;


}

bool_t IsOperator(uint8_t character)
{
	bool_t returnState = kFALSE;
	if ( character == '+' || character == '-' ||
		 character == '*' || character == '/'   )
    {
		returnState = kTRUE;
    }
	return returnState;
}
bool_t IsNumber(uint8_t character)
{
	bool_t returnState = kFALSE;
	if ( character >='0' && character <='9')
    {
		returnState = kTRUE;
    }
	return returnState;
}

void SeparateExp(uint8_t pExp[])
{
    int interator1 = 0;
    int interator2 = 0;
    uint8_t TempExp[EXPRESSION_SIZE]={};

    while (pExp[interator1] != '\0')
    {
        TempExp[interator1] = pExp[interator1];
        interator1++;
    }
    interator1 = 0;
    while (TempExp[interator1] != '\0')
    {

        if (IsOperator(TempExp[interator1]) )
        {
            pExp[interator2++] = ' ';
            pExp[interator2++] = TempExp[interator1++];
            pExp[interator2++] = ' ';

            /* Case if there is a negative Number */
            if ( TempExp[interator1] == '-')
            {
                pExp[interator2++] = '-';
                interator1++;
            }

        }else
        {
          pExp[interator2++] = TempExp[interator1++];
        }
    }
}
uint16 ConvertStringToInteger(uint8_t strNum[], uint8_t size)
{
	uint16 integerNum = 0;
	uint16 iterator = 0;
	for (iterator=0 ; iterator<size ; iterator++)
    {
		integerNum *=10;
		integerNum += strNum[iterator]-'0';
    }

	return integerNum;
}
f32_t GetResult(f32_t _1stNum, f32_t _2ndNum, uint8_t operator)
{
	f32_t result = 0;
	switch (operator)
    {
		case '+': result = _1stNum + _2ndNum; break;
		case '-': result = _1stNum - _2ndNum; break;
		case '*': result = _1stNum * _2ndNum; break;
		case '/': result = _1stNum / _2ndNum; break;
    }

	return result;
}

bool_t IsHighPriority(uint8_t operator)
{
	uint8_t highPriorityFlag = kFALSE;
	if ( operator == '*' || operator == '/')
    {
		highPriorityFlag = kTRUE;
    }
	return highPriorityFlag;
}
