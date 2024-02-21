#ifndef BUZZER_H_
#define BUZZER_H

typedef enum
{
    kBuzzerActiveLow,
    kBuzzerActiveHigh
}BuzzerState_t;

/**
 * @brief A structure to represent Buzzer pin
 *
 */
typedef struct
{
    port_t port;                 /**< the port number*/
    pin_t pin;                  /**< the pin number*/
    BuzzerState_t activeState; /**< the Buzzer state*/
}Buzzer_t;
/**
 * @brief This Function is used to initialize the Buzzer
 *
 * @param pBuzzer : pointer to Buzzer which is a struct from type @Buzzer_t
 */
void Buzzer_Init(Buzzer_t* pBuzzer);
/**
 * @brief This Function is used to turn on the Buzzer
 *
 * @param pBuzzer  : pointer to Buzzer which is a struct from type @Buzzer_t
 * @return error_t : This Function returns kNoError if the Parameter is correct
 *                   and returns kFunctionParameterError
 *                   if the Parameter isn't correct
 */
error_t Buzzer_TurnOn(Buzzer_t* pBuzzer);
/**
 * @brief This Function is used to turn off the Buzzer
 *
 * @param pBuzzer  : pointer to Buzzer which is a struct from type @Buzzer_t
 * @return error_t : This Function returns kNoError if the Parameter is correct
 *                   and returns kFunctionParameterError
 *                   if the Parameter isn't correct
 */
error_t Buzzer_TurnOff(Buzzer_t* pBuzzer);
#endif
