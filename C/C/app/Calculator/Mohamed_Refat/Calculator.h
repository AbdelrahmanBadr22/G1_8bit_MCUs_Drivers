#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#define EXPRESSION_SIZE (50)

typedef enum
{
	NoError,
	SyntaxError,
	DivideByZero,
	_1stNumIsNeg
}Calc_Error_t;


void APP_INIT(lcd_t *pLCD, keypad_t *pkeyPad);
void Run_Calculator(lcd_t *pLCD, keypad_t *pkeyPad);
Calc_Error_t GetPostfixExp(uint8_t *pInfixExp, uint8_t pPostfixExp[]);
Calc_Error_t EvaluatePostfixExp(uint8_t pPostfixExp[], f32_t *pResult,
											 		Calc_Error_t postfixState);
f32_t GetResult(f32_t _1stNum, f32_t _2ndNum, uint8_t operator);
bool_t IsOperator(uint8_t character);
void SeparateExp(uint8_t pExp[]);
bool_t IsNumber(uint8_t character);
uint16 ConvertStringToInteger(uint8_t strNum[], uint8_t size);
bool_t IsHighPriority(uint8_t operator);

#endif /* CALCULATOR_H_ */
