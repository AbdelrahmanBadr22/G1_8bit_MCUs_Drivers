#ifndef RELAY_H
#define RELAY_H

/**
 * @brief Relay_t is a data type to define basic configuration of the relay
 *        port : [kPORTA ... kPORTD] for pic [kPORTA ... kPORTE]
 *        pin  : [kPIN0  ... kPIN7 ]
 */
typedef struct
{
    port_t port; /**< the port number*/
    pin_t pin;   /**< the pin number*/
}Relay_t;
/**
 * @brief  This Function is used to initialize the relay
 * @param pRelay   : pointer to the relay which is a struct from type @Relay_t
 * @return error_t : This Function returns kNoError if the Parameter is correct
 *                   and it returns kFunctioParameterError
 *                   if the Parameter isn't correct
 */
error_t Relay_Init(Relay_t* pRelay);
/**
 * @brief  This Function is used to Turn on the relay
 * @param pRelay   : pointer to the relay which is a struct from type @Relay_t
 * @return error_t : This Function returns kNoError if the Parameter is correct
 *                   and it returns kFunctioParameterError
 *                   if the Parameter isn't correct
 */
error_t Relay_TurnOn(Relay_t* pRelay);
/**
 * @brief  This Function is used to Turn of the relay
 * @param pRelay   : pointer to the relay which is a struct from type @Relay_t
 * @return error_t : This Function returns kNoError if the Parameter is correct
 *                   and it returns kFunctioParameterError
 *                   if the Parameter is't correct
 */
error_t Relay_TurnOff(Relay_t* pRelay);
#endif
