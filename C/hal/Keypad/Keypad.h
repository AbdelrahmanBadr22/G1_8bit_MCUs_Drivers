#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "Config.h"

#define NOTPRESSED (0xff)

/**
 * A structure to represent keypadPin
 */
typedef struct keyadPin_t
{
    /*@{*/
    port_t port;/**< the port number */
    pin_t pin;/**< the pin number*/
    /*@}*/
}keypadPin_t;
/**
 * A structure to represent keypad
 */
typedef struct keypad_t
{
    /*@{*/
    /**< array of keypadPin_t represents rows */
    keypadPin_t Keypad_RowArr[Keypad_numberOfRows];
    /**< array of keypadPin_t represents columns */
    keypadPin_t Keypad_COLArr[Keypad_numberOfCols];
    /*@}*/
}keypad_t;
 /**
  * @brief This Function is used to initialize the keypad
  * @param pKeypad pointer to the keypad which is a struct from type keypad_t.
  * @return error_t This Function returns kNoError if the Parameter is correct
  *                 and returns kFunctionParameterError
  *                 if the Parameter isn't correct
  */
error_t Keypad_Init(keypad_t * pKeypad);
/**
 * @brief This Function is used to get which button was pressed in  the keypad
 * @param pKeypad pointer to the keypad which is a struct from type keypad_t.
 * @return uint8_t  return the value which was pressed from the keypad
 */
uint8_t Keypad_GetPressedButton(keypad_t * pKeypad);

#endif
