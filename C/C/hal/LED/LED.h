#ifndef LED_H_
#define LED_H

typedef enum
{
    kLedActiveLow,
    kLedActiveHigh,
}LedState_t;

/**
 * @brief LED_t       : is the data type to define the Buzzer
 *        port        : for avr [kPORTA ... kPORTD], for pic [kPORTA ... kPORTE]
 *        pin         : [kPIN0 ... kPIN7]
 *        activeState : [kLedActiveLow, kLedActiveHigh]
 *
 */
typedef struct
{
    port_t port;            /**< the port number*/
    pin_t pin;              /**< the pin number*/
    LedState_t activeState; /**< the led state*/
}LED_t;
/**
 * @brief This Function is used to initialize the LED
 *
 * @param pBuzzer : pointer to Buzzer which is a struct from type @LED_t
 */
void LED_Init(LED_t* pLED);
/**
 * @brief This Function is used to turn on the LED
 *
 * @param pLED     : pointer to LED which is a struct from type @LED_t
 * @return error_t : This Function returns kNoError if the Parameter is correct
 *                   and returns kFunctionParameterError
 *                   if the Parameter isn't correct
 */
error_t LED_TurnOn(LED_t* pLED);
/**
 * @brief This Function is used to turn off the LED
 *
 * @param pLED     : pointer to LED which is a struct from type @LED_t
 * @return error_t : This Function returns kNoError if the Parameter is correct
 *                   and returns kFunctionParameterError
 *                   if the Parameter isn't correct
 */
error_t LED_TurnOff(LED_t* pLED);
#endif
