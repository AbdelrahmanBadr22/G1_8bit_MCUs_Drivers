#ifndef CALC_H_
#define CALC_H_
/**
 * @brief When keyval is number the program
 *        will return this value
 */
#define NUMBER (1)
/**
 * @brief When keyval is operator the program
 *        will return this value
 */
#define OPERATOR (0)

#define OPERATOR_SIZE (30)
#define NUMBER_SIZE (31)
typedef enum
{
  noError,
	runtimeError,
  unvalidoperationError
}calcerror_t;
void CalcInit(lcd_t* lcd, keypad_t* keypad, port_t lcdDataPort,
              port_t lcdControlPort, port_t keypadPort);
 /**
  * @brief This Function is used to detremine
  *        if the keyval is number or operator
  * @param key the key pressed.
  * @return uint8_t This Function returns NUMBER if the Parameter is number
  *                 and returns OPERATOR if it is operator
  */
uint8_t ISNUM(uint8_t key);
 /**
  * @brief This Function is used to detremine  the Precedence of the operator
  * @param operator
  * @return uint8_t This Function returns the Precedence of this operator
  *         compared to the previous operator
  */
uint8_t GetPrecedence(uint8_t operator);
/**
 * @brief This Function is used to evaluate the operation
 * @param num1 the first operand
 * @param num2 the second operand
 * @param operator the operator
 * @return sint32 the result from this operation
 */
sint32_t Operate(sint32_t num1, sint32_t num2, char operator);
calcerror_t Evaluate(sint32_tStack_t *ar, charStack_t *arr,
              sint16 size1, sint16 size2);
/**
 * @brief This Function is used to clear previous operations
 * @param operatorStack stack that contains operators
 * @param numStack stack that contains numbers
 * @param lcd
 */
void Clear(charStack_t* operatorStack, sint32_tStack_t* numStack, lcd_t* lcd);
#endif
